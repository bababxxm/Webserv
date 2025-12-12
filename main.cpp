/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:35:13 by sklaokli          #+#    #+#             */
/*   Updated: 2025/12/12 23:27:01 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "Poller.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include "Webserv.hpp"

int main( int argc, char **argv ) {
	if ( argc != 2 ) {
		std::cerr << "Usage: ./webserv <config_file>" << std::endl;
		return ( EXIT_FAILURE );
	}
	std::cout << argv << std::endl;
	return ( EXIT_SUCCESS );
}
