/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:52:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/03 14:40:27 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int main( void ) {
	Fixed a;
	Fixed const b( 10 );
	Fixed const c( 42.42f );
	Fixed const d( b );

	a = Fixed( 1234.4321f );

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	
	return 0;
}

// static void	printRawBits(int raw_bits)
// {
// 	char bits[32] = { 0 };

// 	for (int i = 0; i < 32; i++) {
// 		if ((raw_bits >> i) & 1)
// 			bits[31 - i] = '1';
// 		else
// 			bits[31 - i] = '0';
// 	}
// 	for (int i = 0; i < 32; i++) {
// 		if (i == 32 - 8)
// 			std::cout << ".";
// 		std::cout << bits[i];
// 	}
// 	std::cout << std::endl;
// }

// int main( void ) {
// 	Fixed a;
// 	Fixed const b( 127 );
// 	Fixed const c( -42.42f );
// 	Fixed const d( 31.7f );
// 	Fixed e ( -31.7f );

// 	a = Fixed( 1234.4321f );
	
// 	e.setRawBits( ~2147483647 + 1 );
	
// 	std::cout << e.toFloat() << ": ";
// 	printRawBits(e.getRawBits());
// 	std::cout << "          ";
// 	printRawBits(e.toInt());
// 	std::cout << "          = " << e.toInt() << std::endl;

// 	std::cout << d.toFloat() << " : ";
// 	printRawBits(d.getRawBits());
// 	std::cout << "          ";
// 	printRawBits(d.toInt());
// 	std::cout << "          = " << d.toInt() << std::endl;
// 	e.setRawBits(127 << 16);

// 	std::cout << "a is " << a << " | " << a.toFloat() << std::endl;
// 	std::cout << "b is " << b << " | " << b.toFloat() << std::endl;
// 	std::cout << "c is " << c << " | " << c.toFloat() << std::endl;
// 	std::cout << "d is " << d << " | " << d.toFloat() << std::endl;
// 	std::cout << "e is " << e << " | " << e.toFloat() << std::endl;
// 	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
// 	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
// 	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
// 	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
// 	std::cout << "e is " << e.toInt() << " as integer" << std::endl;
	
// 	return 0;
// }