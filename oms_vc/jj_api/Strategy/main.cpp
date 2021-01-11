//////////////////////////////////////////////////////////////////////////
//空策略

#include <iostream>
#include <thread>
#include <fstream>
#include "strategy.h"
#include "strategy_common.h"
#include "trade_item.h"
#include "share_memory_util.h"
#include <tbb/concurrent_hash_map.h>
using namespace std;

const int ORDER_PAGE_LEN = 1000000;
int j = -1;
Account m_acc;

class MyStrategy :public Strategy
{
public:
	MyStrategy() {}
	~MyStrategy() {}

	void init_oms()
	{
		int date = get_date_int();
		std::string fn = std::to_string(date) + "_oms";
		bool is_exit = share_memory_util::FileExists(fn);

		long long shm_size = sizeof(slr_rb<Order>) + ORDER_PAGE_LEN * sizeof(Order);
		moms = (slr_rb<Order>*)share_memory_util::get_instance()->LoadPageBuffer(fn, shm_size, true, true);

		if (moms == nullptr)
		{
			std::cout << "oms create fail exit" << std::endl;
			return;
		}

		moms->ring_size = ORDER_PAGE_LEN;

		if (false == is_exit)
		{
			moms->sequence.m_sequence = 0;
		}
	}

	void init_sub()
	{
		cout << "从当前目录读取sub.ini(订阅目录)" << endl;
		ifstream myfile("./sub.ini");
		string temp;
		if (!myfile.is_open())
		{
			cout << "未成功打开./sub.ini" << endl;
			return;
		}
		while (getline(myfile, temp))
		{
			std::cout << "订阅合约:" << temp << std::endl;
			this->subscribe(temp.data(), "tick");
		}
		myfile.close();
	}

	void req_pos()
	{
		DataArray<Position>* pos = get_position(m_acc.account_id);
		int len = pos->count();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				auto Pos = pos->at(i);
				auto hv = BKDR_Hash_Compare::hash(Pos.symbol);
				tbb::concurrent_hash_map<uint64_t, trade_item*>::accessor wa;
				bool res = m_trade_item.find(wa, hv);
				if (res)
				{
					wa->second->stock_pos = Pos.volume;
					wa->second->stock_can_sell = Pos.available;
				}
				else
				{
					auto ptr = new trade_item;

					ptr->hash_val = hv;
					memcpy(ptr->id, Pos.symbol, 32);
					ptr->stock_pos = Pos.volume;
					ptr->stock_can_sell = Pos.available;

					m_trade_item.insert(wa, hv);
					wa->second = ptr;
				}
			}
		}
	}

	//重写on_init事件，进行策略开发
	void on_init()override
	{
		auto acclist = get_accounts();
		if (acclist->count() > 0)
		{
			m_acc = acclist->at(0);
		}
		init_sub();
		init_oms();
		req_pos();

		this->start_work();
		return;
	}

	void on_tick(Tick *tick)override
	{
		Tick t = *tick;
		rb_ptr->push(t);
		//std::cout << t.symbol << " " << t.price << std::endl;

		auto hv = BKDR_Hash_Compare::hash(t.symbol);
		tbb::concurrent_hash_map<uint64_t, trade_item*>::accessor wa;
		bool res = m_trade_item.find(wa, hv);
		if (res)
		{
			wa->second->tick = t;
		}
		else
		{
			auto ptr = new trade_item;

			ptr->hash_val = hv;
			memcpy(ptr->id, t.symbol, 32);
			ptr->tick = t;

			m_trade_item.insert(wa, hv);
			wa->second = ptr;
			if (++j <= 0)
			{
				create_algo_order(ptr, 100);
			}
		}
	}

	//委托变化
	virtual void on_order_status(Order *order)override
	{
		auto hv = BKDR_Hash_Compare::hash(order->symbol);
		tbb::concurrent_hash_map<uint64_t, trade_item*>::accessor wa;
		bool res = m_trade_item.find(wa, hv);
		if (res)
		{

		}
		else
		{

			
		}
	}
	//执行回报
	virtual void on_execution_report(ExecRpt *rpt)override
	{
		//std::cout<<rpt->exec_id<<std::endl;
		auto hv = BKDR_Hash_Compare::hash(rpt->symbol);
		tbb::concurrent_hash_map<uint64_t, trade_item*>::accessor wa;
		bool res = m_trade_item.find(wa, hv);
		if (res)
		{
			if (rpt->side == OrderSide_Buy)
				wa->second->stock_pos += rpt->volume;
			if(rpt->side == OrderSide_Sell)
				wa->second->stock_pos -= rpt->volume;
		}
	}

	Order* get_new_order()
	{
		if (moms != nullptr)
		{
			return &moms->ring[(++moms->sequence.m_sequence)%(moms->ring_size)];
		}

	}

	void create_algo_order(trade_item*item, const int target_pos)
	{
		if (target_pos < 0)
		{
			std::cout << "target_pos should >=0" << std::endl;
			return;
		}

		int tn = target_pos - item->stock_pos;
		if (tn<0 && abs(tn)> item->stock_can_sell)
			tn = -1 *item->stock_can_sell;

		if (tn > 0)
		{
			Order res = this->order_volume(item->id, tn, OrderSide_Buy, OrderType_Limit, PositionEffect_Open, item->tick.quotes[0].ask_price, m_acc.account_id);
			//std::cout << res.symbol << std::endl;
			//std::cout << res.order_id << std::endl;
			auto hv = BKDR_Hash_Compare::hash(res.order_id);
		}
		else
		{
			this->order_volume(item->id, abs(tn), OrderSide_Sell, OrderType_Limit, PositionEffect_Open, item->tick.quotes[0].bid_price, m_acc.account_id);
		}
	}

	void start_work()
	{
		if (mwork.joinable() == false)
		{
			std::thread t(std::bind(&MyStrategy::work, this));
			mwork.swap(t);
		}
	}

	void work()
	{
		long long tm = 0;
		while (1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			++tm;
			if (tm % 30 == 0)
			{
				req_pos();
				continue;
			}
			//这里加入处理zmq接收下单的代码
		}
	}
private:
	tbb::concurrent_hash_map<uint64_t, trade_item*> m_trade_item;
	tbb::concurrent_hash_map<uint64_t, Order*> mbook;
	slr_rb<Order>* moms;
	std::thread mwork;
};

int main(int argc, char *argv[])
{
	//打开ZMQ的pub端口，端口为9095
	Zmq_Pub::get_instance()->start_zmq_pub();
	//打开推送行情的线程
	strategy_common::get_instance()->start();

	//std::thread t1(test_pub);
	//t1.detach();

	MyStrategy s;
	s.set_strategy_id("0beb061e-3702-11eb-8dfa-d09466ed08cd");
	s.set_token("ec4e1c7cf232c40700c50760e7de410c23cd9153");
	s.set_mode(MODE_LIVE);

	s.run();
	cout << "`press any key to exit!`" << endl;
	getchar();
	return 0;
}