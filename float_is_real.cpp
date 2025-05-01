/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_is_real.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:39:46 by totommi           #+#    #+#             */
/*   Updated: 2025/05/01 01:49:53 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string.h>
#include <math.h>

void	printRawFloat(void *raw_float)
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

void	printRawBits(int raw_bits, size_t n)
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
	std::cout << std::endl;
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
	mantissa >>= 9;
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
	float	raw = 573.123f;
	unsigned char	exp;
	int		mantissa;

	printRawFloat((void *)&raw);
	exp = getExp((void *)&raw) - 127;
	printRawBits((int)exp, sizeof(char) * 8);
	mantissa = getMantissa((void *)&raw);
	printRawBits((int)mantissa, sizeof(int) * 8);
	std::cout << "exp=" << (int)exp << ", mantissa=" << mantissaToFloat(mantissa) << std::endl;
	float my_float = pow(2, exp) * mantissaToFloat(mantissa);
	std::cout << "my_float=" << my_float << std::endl;
	return (0);
}
