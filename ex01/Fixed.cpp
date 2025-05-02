/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:44:58 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/02 12:12:36 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>

/* Returns the value of the decimal digits moved beyond the dot (.)
Exambple '530.0010234', returns '10234' */
static int64_t	getRawDecimals( const Fixed* fixed, int fractionalBits )
{
	const int	fixedBrick = int((1.0f / pow(2, fractionalBits)) * pow(10, fractionalBits / 2));	// taking the '39' out of the 0.0039 of the 2e-8
	int64_t		decimals;
	int			myRawBits;

	myRawBits = fixed->getRawBits();
	if (myRawBits < 0)
		myRawBits = ~myRawBits + 1;
	decimals = 0;
	for (int i = 0; i < fractionalBits; i++) {
		if ((myRawBits >> i) & 1)
			decimals += fixedBrick * pow(2, i);
	}
	return (decimals);
}

/* MEMBER FUNCTIONS */

int	Fixed::getRawBits(void) const
{
	return (this->rawBits);
}

void	Fixed::setRawBits(int32_t const raw)
{
	this->rawBits = raw;
}

int	Fixed::toInt(void) const
{
	if (this->rawBits > 0)
		return (this->rawBits >> this->fractionalBits);
	else
		return ((this->rawBits >> this->fractionalBits) + 1);
}

float	Fixed::toFloat(void) const
{
	return (double(this->rawBits) / double(1 << this->fractionalBits));	//ok, makes sense
}

/* inserts the deciamls into the ostringstream, with the dot (.) ;) */
std::string Fixed::toString(void) const
{
	std::ostringstream	out;
	const int64_t		rawDecimals = getRawDecimals(this, this->fractionalBits);
    out << this->toInt();
	if (rawDecimals != 0)
		out << "." << std::setw(this->fractionalBits / 2)
			<< std::setfill('0') << rawDecimals;
	return (out.str());
}

/* OVERLOADS */

void	Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->rawBits = other.getRawBits();
}

// Teach operator<< how to print a Fixed
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toString();	// my representation which is much cooler ;P
	//out << fixed.toFloat();	// boring way with trailing errors but scientifc notation and harder to break
	return (out);				// operator<< conventionally returns its left operand
}

/* CONSTRUCTORS & DESTRUCTORS */

Fixed::Fixed(void)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	this->rawBits = copy.getRawBits();
}

Fixed::Fixed(const int rawInt)
{
	std::cout << "Int constructor called" << std::endl;
	this->rawBits = rawInt << this->fractionalBits;
}

Fixed::Fixed(const float rawFloat)
{
	std::cout << "Float constructor called" << std::endl;
	this->rawBits = int32_t(rawFloat * double(1 << this->fractionalBits) + (rawFloat >= 0 ? 0.5 : -0.5));	//what is this sorcery?
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}
