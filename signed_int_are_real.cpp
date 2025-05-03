/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_int_are_real.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:07:27 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/03 15:35:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <strings.h>
#include <math.h>

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
	std::cout << std::endl;
}

int	main(void)
{
	int32_t	test = 42;
	std::cout << "42      : "; printRawBits(test, 32);
	std::cout << "-42     : "; printRawBits(-test, 32);
	std::cout << "-42 -1  : "; printRawBits(-test - 1, 32);
	
	std::cout << "LIMITS" << std::endl;

	int32_t	max = 2147483647;
	int32_t	min = 2147483648;
	int32_t	full = (2147483648 * 2) - 1;
	
	std::cout << "max     : "; printRawBits(max, 32);
	std::cout << "signed  : " << (int)max << std::endl << "unsigned: " << (unsigned int)max << std::endl;
	std::cout << "min     : "; printRawBits(min, 32);
	std::cout << "signed  : " << (int)min << std::endl << "unsigned: " << (unsigned int)min << std::endl;
	std::cout << "full    : "; printRawBits(full, 32);
	std::cout << "signed  : " << (int)full << std::endl << "unsigned: " << (unsigned int)full << std::endl;


}
