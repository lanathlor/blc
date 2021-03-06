#ifdef __WIN32__
	#include <winsock2.h>
#elif __linux__
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#else
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#endif
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include "blc/Server.hpp"
#include "blc/errorHandle.hpp"

#ifdef __WIN32__
	#define socklen_t int
#endif

blc::network::Server::Server(unsigned int maxClient, unsigned int port, bool block, int mode, int type) :	_openedClient(0),
														_port(port),
														_stop(false),
														_kill(false),
														_wait(false),
														_handle(nullptr),
														_maxClient(maxClient),
														_block(block),
														_mode(mode),
														_type(type)
{
	if (block){
		if ((this->_sock = ::socket(this->_type, this->_mode, 0)) == -1)
			throw blc::error::exception(strerror(errno));
	} else {
		if ((this->_sock = ::socket(this->_type, this->_mode | SOCK_NONBLOCK, 0)) == -1)
			throw blc::error::exception(strerror(errno));
	}
	this->_addr.sin_family = this->_type;
	this->_addr.sin_port = htons(port);
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(this->_sock, (const struct sockaddr *)&this->_addr, sizeof(struct sockaddr_in)) == -1)
		throw blc::error::exception(strerror(errno));
	this->listen();
}

blc::network::Server::~Server()
{
}

void blc::network::Server::setMaxClient(unsigned int maxClient)
{
	this->_maxClient = maxClient;
}

unsigned int blc::network::Server::getMaxClient() const
{
	return (this->_maxClient);
}

unsigned int blc::network::Server::getOpenedClient() const
{
	return (this->_openedClient);
}

int blc::network::Server::getSock() const
{
	return (this->_sock);
}

int blc::network::Server::getPort() const
{
	return (this->_port);
}

void blc::network::Server::listen()
{
	::listen(this->_sock, this->_maxClient);
}

void blc::network::Server::handle(std::function<void(int, struct sockaddr, void *)> handle)
{
	this->_mutex.lock();
	this->_handle = handle;
	this->_mutex.unlock();
}

void blc::network::Server::stop()
{
	this->_mutex.lock();
	this->_stop = true;
	this->_mutex.unlock();
}

void blc::network::Server::resume()
{
	this->_mutex.lock();
	this->_stop = false;
	this->_mutex.unlock();
}

void blc::network::Server::wait(unsigned int wait)
{
	this->_mutex.lock();
	this->_wait = wait;
	this->_mutex.unlock();
}

void blc::network::Server::kill()
{
	this->_mutex.lock();
	this->_kill = true;
	this->_mutex.unlock();
}

int blc::network::Server::accept(struct sockaddr *client)
{
	socklen_t size = sizeof(struct sockaddr);

	return (::accept(this->getSock(), client, (socklen_t *)&size));
}

void blc::network::Server::close()
{
	::close(this->getSock());
}
