//////////////////////////////////////////////////////////////////////////
//空策略

#include <iostream>
#include <thread>
#include <fstream>
#include "strategy.h"
#include "strategy_common.h"
#include "trade_item.h"
#include <tbb/concurrent_hash_map.h>
using namespace std;


void test_pub()
{
	Tick t;
	strcpy_s(t.symbol, "600036.SH");
	t.created_at = 123456.7891;
	t.open = 23.765;
	t.price = 24.12345;
	t.high = 25;
	t.low = 23;
	t.cum_amount = 779874932;
	t.cum_position = 876590;
	t.cum_volume = 54321;
	t.last_amount = 12345;
	t.last_volume = 15;
	t.trade_type = 250;
	for (int i = 0; i < 10; ++i)
	{
		t.quotes[i].ask_price = 25 + (i + 1) * 0.001;
		t.quotes[i].bid_price = 25 - (i - 1) *0.001;
		t.quotes[i].ask_volume = 100 + i;
		t.quotes[i].bid_volume = 100 + i;
	}

	char buf[1024];
	int len;
	swap_tick_to_string(t, buf, len);
	while (1)
	{
		Sleep(2000);
		//Zmq_Pub::get_instance()->publish(buf, len);
		rb_ptr->push(t);
	}
}

class MyStrategy :public Strategy
{
public:
	MyStrategy() {}
	~MyStrategy() {}

	//重写on_init事件，进行策略开发
	void on_init()
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



		return;
	}

	void on_tick(Tick *tick)override
	{
		Tick t = *tick;
		rb_ptr->push(t);
		std::cout << t.symbol << " " << t.price << std::endl;

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
			this->order_volume(item->id, tn, OrderSide_Buy, OrderType_Limit, PositionEffect_Open, item->tick.quotes[0].ask_price);
		}
		else
		{
			this->order_volume(item->id, abs(tn), OrderSide_Sell, OrderType_Limit, PositionEffect_Open, item->tick.quotes[0].bid_price);
		}
	}

private:
	tbb::concurrent_hash_map<uint64_t, trade_item*> m_trade_item;
	tbb::concurrent_hash_map<uint64_t, Order*> mbook;
};

int main(int argc, char *argv[])
{
	//打开ZMQ的pub端口，端口为9095
	Zmq_Pub::get_instance()->start_zmq_pub();
	//打开推送行情的线程
	strategy_common::get_instance()->start();

	std::thread t1(test_pub);
	t1.detach();

	MyStrategy s;
	s.set_strategy_id("0beb061e-3702-11eb-8dfa-d09466ed08cd");
	s.set_token("ec4e1c7cf232c40700c50760e7de410c23cd9153");
	s.set_mode(MODE_LIVE);

	s.run();
	cout << "`press any key to exit!`" << endl;
	getchar();
	return 0;
}