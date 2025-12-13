/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:35:13 by sklaokli          #+#    #+#             */
/*   Updated: 2025/12/13 17:46:20 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "Poller.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include "Webserv.hpp"

// int main( int argc, char **argv ) {
// 	if ( argc != 2 ) {
// 		std::cerr << "Usage: ./webserv <config_file>" << std::endl;
// 		return ( EXIT_FAILURE );
// 	}
// 	std::cout << argv << std::endl;
// 	return ( EXIT_SUCCESS );
// }


// TEST Server
int main( void )
{
	try
	{
		Server	s(8080);
		s.run();
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}