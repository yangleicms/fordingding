//
// Created by YangLei on 2020-01-23.
//

#ifndef __LOCK_FREE_RINGBUFFER_H__
#define __LOCK_FREE_RINGBUFFER_H__

#include <cstdint>
#include <atomic>

#ifdef __linux__
#define CAS(v,old_v,new_v) __sync_bool_compare_and_swap (v,old_v,new_v)
#define cell_mb() asm volatile("mfence" : : : "memory");
#else
#include <winsock2.h>
#include <windows.h>
#define cell_mb()
#if defined(_WIN64) || ((_WIN32_WINNT >= 0x0502) && defined(_WINBASE_) && !defined(_MANAGED))
#define CAS(des, old_v, new_v) InterlockedCompareExchange((uint64_t *)des,new_v, old_v) == old_v
#else
#define CAS(des, old_v, new_v) _InterlockedCompareExchange((unsigned long *)des,new_v, old_v) == old_v
#endif
#endif

template<typename T>
class slr_rb
{
public:
	static slr_rb<T> * create(int tnum)
	{
		long long blen = sizeof(slr_rb<T>) + tnum * sizeof(T);
		slr_rb<T> * ptr = (slr_rb<T>*)malloc(blen);
		ptr->ring_size = tnum;
		ptr->sequence.m_sequence = 0;
		return ptr;
	}

	void push(T data)
	{
		ring[++sequence.m_sequence] = data;
	}

	struct seq
	{
		volatile uint64_t m_sequence;
		int64_t appending[7];
	}sequence;

	int64_t ring_size;
	int64_t index_mode;
	int64_t appending[6];
	T ring[0];
};
#endif
