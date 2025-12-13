/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:18:53 by sklaokli          #+#    #+#             */
/*   Updated: 2025/12/13 17:47:56 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"

class Server {
	private :
		int	_listenFd;
		int	_port;

		// Private Methods
		void		setupServer( void );
		int			acceptClient( void );
		void		bindAndListen( void );
		void		handleClient( int clientFd );
		std::string	buildHelloResponse( void ) const;

	public :
		// Constructors
		Server( void );
		Server( const int port );
		Server( const Server &other );
		
		// Operator Overload
		Server	&operator=( const Server &other );

		// Destructor
		~Server( void );

		// Public Method
		void	run( void );
	};

#endif
