/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:31:40 by sklaokli          #+#    #+#             */
/*   Updated: 2025/12/13 17:48:49 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// C++ & C Standard Library
# include <ctime>
# include <cstdio>
# include <string>
# include <cerrno>
# include <cctype>
# include <cstdlib>
# include <cstring>
# include <iostream>

// POSIX / UNIX System Calls
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

// Networking
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>

// Process Control
# include <signal.h>
# include <sys/wait.h> 

// Multiplexing
# include <poll.h>
# include <sys/epoll.h>
# include <sys/select.h>

// STL
# include <map>
# include <list>
# include <vector>
# include <iterator>
# include <algorithm>

# include "Config.hpp"
# include "Poller.hpp"
# include "Server.hpp"
# include "Request.hpp"
# include "Response.hpp"

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"

class Webserv {

	private:

		std::string		_configFile;

	public:

		Webserv( void );
		Webserv( const std::string& configFile );
		Webserv( const Webserv& other );
		~Webserv( void );

		Webserv&	operator=( const Webserv& other );
		void		run( void );
		void		close( void );

};

#endif
