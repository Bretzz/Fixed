/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_is_real.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:39:46 by totommi           #+#    #+#             */
/*   Updated: 2025/05/03 16:01:40 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string.h>
#include <math.h>

static void	printRawFloat(void *raw_float)
{
	int	raw_bits;
	char bits[32] = { 0 };

	raw_bits = *(int *)raw_float;
	for (int i = 0; i < 32; i++) {
		if ((raw_bits >> i) & 1)
			bits[31 - i] = '1';
		else
			bits[31 - i] = '0';
	}
	for (int i = 0; i < 32; i++) {
		if (i == 0)
			std::cout << "[";
		std::cout << bits[i];
		if (i == 0)
			std::cout << "]";
		if (i == 8)
			std::cout << ".";
	}
	std::cout << std::endl;
}

static void	printRawBits(int raw_bits, size_t n)
{
	char bits[n];

	bzero(bits, n);
	for (int i = 0; i < n; i++) {
		if ((raw_bits >> i) & 1)
			bits[(n - 1) - i] = '1';
		else
			bits[(n - 1) - i] = '0';
	}
	for (int i = 0; i < n; i++) {
		std::cout << bits[i];
	}
	//std::cout << std::endl;
}

static char getExp(void *raw_float)
{
	return (*((int *)raw_float) >> 23);
}

static int getMantissa(void *raw_float)
{
	return (*((int *)raw_float) << 9);
}

static float mantissaToFloat(int mantissa)
{
	//mantissa >>= 9;
	// for (int i = 0; i < 23; i++) {
	// 	if ((mantissa >> i) & 1)
	// 		std::cout << "1";
	// 	else
	// 		std::cout << "0";
	// }
	// std::cout << std::endl;

	float	my_man = 1.0f;
	for(int i = 0; i < 23; i++) {
		if ((mantissa >> i) & 1)
			my_man += 1.0f / pow(2, (23 - i));		
	}
	return (my_man);
}

//01000010001010011010111000010100 https://www.h-schmidt.net/FloatConverter/IEEE754.html
//01000010001010011010111000010100 my-own
// 01010000111010110010100

int	main(void)
{
	const float		raw = 0.123f;
	char			exp;
	int				mantissa;

	std::cout << "raw float: "; printRawFloat((void *)&raw);
	exp = getExp((void *)&raw);
	std::cout << "exp      : "; printRawBits((int)exp, 32); std::cout << " = " << (unsigned int)exp << std::endl;
	mantissa = getMantissa((void *)&raw) >> 9;
	//printRawBits((int)(mantissa), 32); std::cout << std::endl;
	bzero((char *)(&mantissa) + 3, 1); mantissa -= pow(2, 23);
	//printRawBits((int)(mantissa), 32); std::cout << std::endl;
	std::cout << "mantissa : "; printRawBits((int)(mantissa), 32); std::cout << " = " << (unsigned int)((mantissa)) << std::endl;
	std::cout << "exp=" << (int)exp - 127 << ", mantissa=" << mantissaToFloat(mantissa) << std::endl;
	float my_float = pow(2, exp - 127) * mantissaToFloat(mantissa);
	std::cout << "my_float= 2^" << (int)exp - 127 << " * " << mantissaToFloat(mantissa) << " = " << my_float << std::endl;
	return (0);
}
