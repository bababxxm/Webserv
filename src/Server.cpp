#include "Server.hpp"

Server::Server( void ) : _listenFd(-1), _port(8080) {}

Server::Server( const int port ) : _listenFd(-1), _port(port) {}

Server::Server( const Server &other ) : _listenFd(other._listenFd), _port(other._port) {}

Server	&Server::operator=( const Server &other )
{
	if (this != &other)
	{
		this->_listenFd = other._listenFd;
		this->_port = other._port;
	}
	return (*this);
}

Server::~Server( void )
{
	if (_listenFd >= 0)
		close(_listenFd);
}

void	Server::setupServer( void )
{
	int					opt;

	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenFd < 0)
		throw std::runtime_error(std::string(RED "Socket Error" RESET ": ") + std::strerror(errno));
	opt = 1;
	if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error(std::string(RED "Setsockopt Error" RESET ": ") + std::strerror(errno));
	
	bindAndListen();
}

void	Server::bindAndListen( void )
{
	struct sockaddr_in	addr;
	
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(_port);
	if (bind(_listenFd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error(std::string(RED "Listen Error" RESET ": ") + std::strerror(errno));

	if (listen(_listenFd, 10) < 0)
		throw std::runtime_error(std::string(RED "Listen Error" RESET ": ") + std::strerror(errno));
	std::cout << "Server listening on port " << _port << std::endl;
}

int	Server::acceptClient( void )
{
	struct sockaddr_in	clientAddr;
	socklen_t			clientLen;
	int					clientFd;

	clientLen = sizeof(clientAddr);
	if ((clientFd = accept(_listenFd, (struct sockaddr *)&clientAddr, &clientLen)) < 0)
	{
		std::cerr << RED "Accept Error" RESET ": " << + std::strerror(errno) << std::endl;
		return (-1);
	}
	return (clientFd);
}

void	Server::handleClient( int clientFd )
{
	std::string	response;
	const char	*data;
	char		buffer[4096];
	ssize_t		total;
	ssize_t		toSend;
	ssize_t		n;

	n = recv(clientFd, buffer,  sizeof(buffer) - 1, 0);
	if (n < 0)
	{
		std::cerr << RED "Recv Error" RESET ": " << + std::strerror(errno) << std::endl;
		return  ;
	}
	buffer[n] = '\0';

	std::cout << "----- REQUEST BEGIN -----\n";
    std::cout << buffer << "\n";
    std::cout << "----- REQUEST END -----\n";

	response = buildHelloResponse();
	data = response.c_str();
	total = 0;
	toSend = (ssize_t)response.size();
	while (total < toSend)
	{
		n = send(clientFd, data + total, toSend - total, 0);
		if (n <= 0)
		{
			std::cerr << RED "Send Error" RESET ": " << + std::strerror(errno) << std::endl;
			break ;
		}
		total += n;
	}
}

std::string Server::buildHelloResponse( void ) const
{
    std::string body = "Hello, world!";
    std::string res;
    char lenBuf[32];

    std::sprintf(lenBuf, "%lu", (unsigned long)body.size());

    res  = "HTTP/1.1 200 OK\r\n";
    res += "Content-Type: text/plain\r\n";
    res += "Content-Length: ";
    res += lenBuf;
    res += "\r\n";
    res += "Connection: close\r\n";
    res += "\r\n";
    res += body;

    return (res);
}

void	Server::run( void )
{
	while (true)
	{
		int	clientFd = acceptClient();

		if (clientFd < 0)
			continue ;
		std::cout << "New client connected" << std::endl;
		handleClient(clientFd);
		close(clientFd);
		std::cout << "Client disconnected" << std::endl;
	}
}
