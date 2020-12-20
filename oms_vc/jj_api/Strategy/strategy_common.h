#pragma once
#ifndef STRATEGY_COMMON_H
#define STRATEGY_COMMON_H
#include "zmq_pub.h"
#include "slr_rb.h"
#include "gmdef.h"
#include <ctime>

static slr_rb<Tick> *rb_ptr;

static void swap_tick_to_string(Tick&t,char*buf,int &len)
{
	memset(buf, 0, 1024);
	int len1 = snprintf(buf, 1024, "%s|%.4lf|%.4f|%.4f|%.4f|%.4f|%.4lf|%.4lf|%lld|%.4lf|%d|%d|", 
		t.symbol,t.created_at,t.price,t.open,t.high,t.low,t.cum_volume,t.cum_amount,t.cum_position,
		t.last_amount,t.last_volume,t.trade_type);
	int len2 = snprintf(buf + len1, 1024 - len1, "%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld|%.4f|%lld",
		t.quotes[0].bid_price, t.quotes[0].bid_volume, t.quotes[0].ask_price, t.quotes[0].ask_volume,
		t.quotes[1].bid_price, t.quotes[1].bid_volume, t.quotes[1].ask_price, t.quotes[1].ask_volume,
		t.quotes[2].bid_price, t.quotes[2].bid_volume, t.quotes[2].ask_price, t.quotes[2].ask_volume,
		t.quotes[3].bid_price, t.quotes[3].bid_volume, t.quotes[3].ask_price, t.quotes[3].ask_volume,
		t.quotes[4].bid_price, t.quotes[4].bid_volume, t.quotes[4].ask_price, t.quotes[4].ask_volume,
		t.quotes[5].bid_price, t.quotes[5].bid_volume, t.quotes[5].ask_price, t.quotes[5].ask_volume,
		t.quotes[6].bid_price, t.quotes[6].bid_volume, t.quotes[6].ask_price, t.quotes[6].ask_volume,
		t.quotes[7].bid_price, t.quotes[7].bid_volume, t.quotes[7].ask_price, t.quotes[7].ask_volume,
		t.quotes[8].bid_price, t.quotes[8].bid_volume, t.quotes[8].ask_price, t.quotes[8].ask_volume,
		t.quotes[9].bid_price, t.quotes[9].bid_volume, t.quotes[9].ask_price, t.quotes[9].ask_volume
	);
	len = len1 + len2;
}

static void test_pub()
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

static int get_date_int()
{
	time_t now = time(0);

	tm *ltm = localtime(&now);

	// ��� tm �ṹ�ĸ�����ɲ���
	int year = 1900 + ltm->tm_year ;
	int month = 1 + ltm->tm_mon ;
	int day = ltm->tm_mday;
	return 10000 * year + month * 100 + day;
}


class strategy_common
{
public:
	inline static strategy_common * get_instance()
	{
		static strategy_common util;
		return &util;
	}

	void start()
	{
		if (mbwork == true)
			return;

		std::thread work(std::bind(&strategy_common::work, this));
		m_work.swap(work);
		
		rb_ptr = slr_rb<Tick>::create(1024);
	}


private:
	void work()
	{
		char buf[1024];
		int len = 0;
		while (1)
		{
			Sleep(50);
			uint64_t tmp = rb_ptr->sequence.m_sequence;
			if (tmp <= mindex)
			{
				mindex = tmp;
				continue;
			}
			for (uint64_t i = mindex + 1; i <= tmp; ++i)
			{
				swap_tick_to_string(rb_ptr->ring[i%rb_ptr->ring_size],buf,len);
				Zmq_Pub::get_instance()->publish(buf, len);
			}
			mindex = tmp;
		}
	}

	volatile bool mbwork = false;
	std::thread m_work;
	volatile uint64_t mindex = 0;
};


#endif
