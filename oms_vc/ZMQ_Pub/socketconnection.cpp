#include "socketconnection.h"

socket_connection::socket_connection(zmq::context_t& context) : m_context(context)
{
	m_socket_pub = new zmq::socket_t(context, ZMQ_PUB);
}
socket_connection::~socket_connection()
{
	m_socket_pub->close();
	delete m_socket_pub;
	m_socket_pub = nullptr;
}
void socket_connection::init(const char* strPub)
{
	if (strPub == nullptr || strlen(strPub) < 1)
	{
		printf("socket_connection::init fail because the strPub is null!\n");
		return;
	}
	m_socket_pub->bind(strPub);
}

