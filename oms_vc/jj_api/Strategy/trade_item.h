#pragma once
#ifndef TRADE_ITEM
#define TRADE_ITEM
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include "gmdef.h"

struct BKDR_Hash_Compare
{
	static size_t hash(const char* x)
	{
		unsigned int seed = 131; // the magic number, 31, 131, 1313, 13131, etc.. orz..
		size_t h = 0;
		unsigned char *p = (unsigned char *)x;
		while (*p)
		{
			h = h * seed + (*p++);
		}
		return h;
	}

	static bool equal(const char *x, const char* y)
	{
		return strcmp(x, y) == 0;
	}
};

struct trade_item
{
	int stock_pos = 0;//股票仓位
	int stock_can_sell = 0;//可卖出仓位；
	int wait_long = 0;
	int wait_short = 0;
	uint64_t hash_val = 0;
	char id[32];
	Tick tick;

	std::mutex mlock;
	std::unordered_map<int, Order*> mbook;

	Order* get_order(int id)
	{
		std::lock_guard<std::mutex> g(this->mlock);
		auto it = mbook.find(id);
		if (it == mbook.end())
			return nullptr;
		return it->second;
	}

	void del_order(int id)
	{
		std::lock_guard<std::mutex> g(this->mlock);
		mbook.erase(id);

	}

	void insert(int id, Order*ord)
	{
		std::lock_guard<std::mutex> g(this->mlock);
		mbook[id] = ord;
	}

	std::unordered_map<int, Order*> get_book()
	{
		std::unordered_map<int, Order*> mb;
		std::lock_guard<std::mutex> g(mlock);
		mb = mbook;
		return mb;
	}
};

#endif
