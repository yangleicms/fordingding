#ifndef _SOCKET_CONNECTION_V2_H_
#define _SOCKET_CONNECTION_V2_H_
#pragma once
//#include "common.h"
#ifdef _WIN32
#ifndef _WIN32_LEAN_AND_MEAN_
#define _WIN32_LEAN_AND_MEAN_
#endif
#include <winsock2.h>
#endif

#include "zmq.hpp"

#include <iostream>
#include <istream>
#include <fstream>

using namespace zmq;

class socket_connection
{
public:
	socket_connection(zmq::context_t& context);
	~socket_connection();
public:
	void init(const char* strPub);
	void publish(const char* msg, int sz)
	{
		try
		{
			zmq::message_t msgbody(sz);
			std::memcpy(msgbody.data(), msg, sz);
			m_socket_pub->send(msgbody);
		}
		catch (std::exception& e)
		{
			std::cout << "serializeAndSend exception: " << e.what() << std::endl;
		}
	}
protected:
	zmq::socket_t* m_socket_pub;
	zmq::context_t& m_context;
	int ser_num = 0;
};

#endif //_SOCKET_CONNECTION_V2_H_


