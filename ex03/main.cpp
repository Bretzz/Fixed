/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:29:43 by totommi           #+#    #+#             */
/*   Updated: 2025/05/03 17:59:28 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.h"
#include <iostream>
#include <bits/stdc++.h> 

int	main(int argc, char *argv[])
{
	Point a ( 0.0f, 2.0f );
	Point b ( -1.0f, -1.0f );
	Point c ( 2.0f, 0.0f );
	std::cout << "TRIANGLE: " << a << b << c << std::endl;
	if (argc != 3)
	{
		Point point ( 0.148f, 1.952f );
		std::cout << "POINT: " << point << std::endl;
		bsp(a, b, c, point) ? std::cout << "OK" : std::cout << "KO";
		std::cout << std::endl;
	}
	else
	{
		std::cout << "creating: " << std::atof(argv[1]) << " , " << std::atof(argv[2]) << std::endl;
		std::cout << "! ! ! ISSUES WITH -0.99 ! ! !" << std::endl;
		Point point ( std::atof(argv[1]), std::atof(argv[2]) );
		std::cout << "POINT: " << point << std::endl;
		bsp(a, b, c, point) ? std::cout << "OK" : std::cout << "KO";
		std::cout << std::endl;
	}
	return (0);
}
