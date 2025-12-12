/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:31:36 by sklaokli          #+#    #+#             */
/*   Updated: 2025/12/06 17:28:01 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

Webserv::Webserv( void ) {}

Webserv::Webserv( const std::string& configFile ) : _configFile( configFile ) {}

Webserv::Webserv( const Webserv& other ) : _configFile( other._configFile ) {}

Webserv::~Webserv( void ) {}

Webserv&	Webserv::operator=( const Webserv& other ) {
	if ( this != &other ) {
		_configFile = other._configFile;
	}
	return ( *this );
}

void	Webserv::run( void ) {
	
}

void	Webserv::close( void ) {
	
}
