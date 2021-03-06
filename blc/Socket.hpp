#pragma once

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

#include <string>
#include <functional>
#include "blc/nonCopyable.hpp"
#include "blc/stream.hpp"

#ifndef SOCKET
	#define SOCKET int
#endif

#define UDP SOCK_DGRAM
#define TCP SOCK_STREAM

namespace blc {
	namespace network {
		/// wrap-up the unix socket
		class Socket : private symbole::nonCopyable, public stream {
		public:
			Socket(); /**< construct without address nor port socket empty. can't be opened unless the socket adress and port are fills.*/ ///< construct an empty socket.
			Socket(std::string address, int port, bool block = true, int mode = TCP, int type = AF_INET); ///< construct a set object
			~Socket();
			std::string	getAddress() const; ///< return the adress
			int		getPort() const; ///< return the port
			bool		getBlock() const; ///< return the type of the socket (blocking/non-blocking)
			int		getMode() const; ///< return the current mode of the socket
			int		getType() const; ///< return the current type (domain) of the socket
			void		setAddress(const std::string &str); ///< set the adress. needed when empty-created
			void		setPort(int port); ///< set the port. needed when empty-created \param[in] port prepare a connection to this port
			void		setBlock(bool mode); ///< set the type of the socket. default : blocking
			void		setMode(int mode); ///< set the mode of the socket. default : SOCK_STREAM
			void		setType(int type); ///< set the type of the socket. default : AF_INET
			void		write(const std::string &str) const; ///< write a string throught the socket
			std::string	read() const; ///< read a string from the socket
			std::string	read(int n) const; ///< read a string from the socket
			void		open(); ///< open the socket. need to be set with an address and a port.
			void		close(); ///< close the socket
			bool		isOpen() const; ///< check if the socket is already open
			bool		isClosed() const; ///< check if the socket is already close
			bool		readable() const; ///< check if the socket is readable.
			bool		writable() const; ///< check if the socket is writable.
			bool 		waitRead(unsigned int usec) const; ///< wait usec µsec for the socket to be readable.
			bool 		waitWrite(unsigned int usec) const; ///< wait usec µsec for the socket to be writable.
			Socket		&operator<<(const std::string &str); ///< call write with the str string.
			Socket		&operator>>(std::string &str); ///< call read and write the response in the string str.
		protected:
			SOCKET		_socket;
			std::string	_address;
			int		_port;
			bool		_block;
			int		_mode;
			int		_type;
			bool		_opened;
		};
	}
}

std::ostream &operator<<(std::ostream &ostream, blc::network::Socket &socket);