#ifndef ZMQ_PUB_H
#define ZMQ_PUB_H

#ifdef _WIN32
#ifndef _WIN32_LEAN_AND_MEAN_
#define _WIN32_LEAN_AND_MEAN_
#endif
#include <winsock2.h>
#endif

#include "socketconnection.h"
#include <unordered_set>
#include <thread>
#include <istream>
#include <fstream>
#include <string>
#include <mutex>
static zmq::context_t  g_zmq_context(4);

class Zmq_Pub
{
public:
	inline static Zmq_Pub * get_instance()
	{
		static Zmq_Pub util;
		return &util;
	}

	void start_zmq_pub();
	void publish(const char* msg, int sz)
	{
		mcon->publish(msg, sz);
	}
private:
	

	std::string m_url = "tcp://*:9095";
	socket_connection *mcon = nullptr;
};

#endif
