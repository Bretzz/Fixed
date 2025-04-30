/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:44:58 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/01 00:04:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <math.h>

//in general: number = (sign ? -1:1) * 2^(exponent) * 1.(mantissa bits)
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

void	printRawBits(int raw_bits)
{
	char bits[32] = { 0 };

	for (int i = 0; i < 32; i++) {
		if ((raw_bits >> i) & 1)
			bits[31 - i] = '1';
		else
			bits[31 - i] = '0';
	}
	for (int i = 0; i < 32; i++) {
		std::cout << bits[i];
	}
	std::cout << std::endl;
}

/* MEMBER FUNCTIONS */

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->raw_bits);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->raw_bits = raw;
}

int	Fixed::toInt(void) const
{
	return (this->raw_bits >> this->fractional_bits);
}

float	Fixed::toFloat(void) const
{
	float	my_float;

	printRawBits(this->raw_bits);
	printRawBits((this->raw_bits >> this->fractional_bits));
	printRawBits((this->raw_bits << (31 - this->fractional_bits)) >> (31 - this->fractional_bits));
	std::cout << ((this->raw_bits << (31 - this->fractional_bits)) >> (31 - this->fractional_bits)) << std::endl;
	my_float = (this->raw_bits >> this->fractional_bits) + (1.0f / ((this->raw_bits << (31 - this->fractional_bits)) >> (31 - this->fractional_bits)));
	return (my_float);
}

/* OVERLOADS */

void	Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->raw_bits = other.getRawBits();
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
    out << fixed.toFloat();		// print our color's name to whatever output stream out
    return out;					// operator<< conventionally returns its left operand
}

// std::ostream& Fixed::operator<<(std::ostream& out)
// {
// 	out << this->raw_bits << "." << (this->raw_bits << 8) << std::endl;
// 	return (out);
// }

/* CONSTRUCTORS & DESTRUCTORS */

Fixed::Fixed(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	this->raw_bits = copy.getRawBits();
}

Fixed::Fixed(const int raw)
{
	std::cout << "Int constructor called" << std::endl;
	this->raw_bits = raw << this->fractional_bits;
}

Fixed::Fixed(const float raw)
{
	float	my_raw;
	std::cout << "Float constructor called" << std::endl;
	my_raw = (raw * -1);
	std::cout << "   raw: " << raw << std::endl;
	std::cout << "my_raw: " << my_raw << std::endl;
	printRawFloat((void *)&raw);
	printRawFloat((void *)&my_raw);
	// for (int i = 0; i < 8; i++) {
	// 	if ((char)(raw >> 1) + )
	// }
	// int	i;

	// i = 0;
	// while (i < 8 && (raw * pow(2, i)) - (int)(raw * pow(2, i)) > FLOAT_EPSILON) {
	// 	std::cout << "diff=" << (raw * pow(2, i)) - (int)(raw * pow(2, i)) << std::endl;
	// 	i++;
	// }
	// std::cout << "shift found: " << i << std::endl;
	this->raw_bits = (int)(raw) << this->fractional_bits | 128;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}
