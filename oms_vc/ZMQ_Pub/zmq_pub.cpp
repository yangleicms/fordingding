#include "zmq_pub.h"
#include <functional>


void Zmq_Pub::start_zmq_pub()
{
	mcon = new socket_connection(g_zmq_context);
	mcon->init(m_url.data());
}