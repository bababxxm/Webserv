/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:31:40 by sklaokli          #+#    #+#             */
/*   Updated: 2025/12/06 17:17:23 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <cstdlib>
# include <iostream>

# include "Config.hpp"
# include "Poller.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Server.hpp"

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
