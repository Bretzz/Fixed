/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:44:58 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/03 14:51:22 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>

/* CONSTRUCTORS & DESTRUCTORS */

Fixed::Fixed(void)
{
	this->rawBits = 0;
}

Fixed::Fixed(const Fixed &copy)
{
	this->rawBits = copy.getRawBits();
}

Fixed::Fixed(const int rawInt)
{
	this->rawBits = rawInt << this->fractionalBits;
}

/*
 *	STANDARD CONVERION:
 *	this->rawBits = int32_t(rawFloat * double(1 << this->fractionalBits) + (rawFloat >= 0 ? 0.5 : -0.5));
 *	A bit less load on the CPU but worse precision.
*/
/* My baby :') */
Fixed::Fixed(const float rawFloat)
{
	const int64_t	fixedBrick = int64_t(1.0f / pow(2, this->fractionalBits) * pow(10, DIGITS/* this->fractionalBits / 2 */));
	float			myRawFloat = rawFloat;

	/* normalizing negative numbers and storing the sign for later */
	char sign = myRawFloat < 0 ? -1 : 1;
	myRawFloat *= sign;
	/* taking out the decimals: '1234' out oof '205.1234' */
	int64_t	decimals = (myRawFloat - (int)myRawFloat) * pow(10, DIGITS/* this->fractionalBits / 2 */);
	/* adding the integer part */
	this->rawBits = (int32_t)(myRawFloat) << this->fractionalBits;
	/*	
	 *	For each one of the fractional bits, if it's contained in decimal
	 *	we subtract it's represented 'value' from 'decimals' and add it to 'rawBits'
	*/
	for (int i = 0; i < this->fractionalBits; i++) {
		const float	fixedFract = fixedBrick * pow(2, this->fractionalBits - (i + 1));
		if (decimals > fixedFract)
		{
			decimals -= fixedFract;
			this->rawBits += pow(2, this->fractionalBits - (i + 1));
		}
	}
	/*
	 *	better rounding possible thanks to the decimals
	 *	being stored in integers and not really small floats
	*/
	if (decimals > (fixedBrick / 2))	// im the goat
		this->rawBits += 1;
	/* signing the bits with integer arithmetic */
	if (decimals == 0 && sign < 0)
		this->rawBits = ~this->rawBits + 1 - (1 << this->fractionalBits);
	else
		this->rawBits *= sign;
}

Fixed::~Fixed(void) { /* Nothing to see here */}

/* Returns the value of the decimal digits moved beyond the dot (.)
Exambple '530.0010234', returns '10234' */
static int64_t	getRawDecimals( const Fixed* fixed, int fractionalBits )
{
	const int	fixedBrick = int((1.0f / pow(2, fractionalBits)) * pow(10, fractionalBits / 2));	// taking the '39' out of the 0.0039 of the 2e-8
	int64_t		decimals;
	int32_t			myRawBits;

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

int32_t	Fixed::getRawBits(void) const
{
	return (this->rawBits);
}

void	Fixed::setRawBits(int32_t const raw)
{
	this->rawBits = raw;
}

//Type conversions
int	Fixed::toInt(void) const
{
	if (this->rawBits >= 0)
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

//Min/Max
Fixed&	Fixed::min(Fixed& first, Fixed& second)
{
	return (first.getRawBits() <= second.getRawBits() ? first : second);
}

const Fixed&	Fixed::min( const Fixed& first, const Fixed& second)
{
	return (first.getRawBits() <= second.getRawBits() ? first : second);
}

Fixed&	Fixed::max(Fixed& first, Fixed& second)
{
	return (first.getRawBits() >= second.getRawBits() ? first : second);
}

const Fixed&	Fixed::max( const Fixed& first, const Fixed& second)
{
	return (first.getRawBits() >= second.getRawBits() ? first : second);
}

Fixed	Fixed::epsilon( void )
{
	Fixed	epsilon;
	epsilon.setRawBits(1);
	return (epsilon);
}

/* OVERLOADS */

// Assignment operators
void	Fixed::operator=(const Fixed& other)
{
	this->rawBits = other.getRawBits();
}

// Comparison operators
bool	Fixed::operator>(const Fixed& other) const
{
	return (this->rawBits > other.getRawBits() ? true : false);
}

bool	Fixed::operator<(const Fixed& other) const
{
	return (this->rawBits < other.getRawBits() ? true : false);
}

bool	Fixed::operator>=(const Fixed& other) const
{
	return (this->rawBits >= other.getRawBits() ? true : false);
}

bool	Fixed::operator<=(const Fixed& other) const
{
	return (this->rawBits <= other.getRawBits() ? true : false);
}

bool	Fixed::operator==(const Fixed& other) const
{
	return (this->rawBits == other.getRawBits() ? true : false);
}

bool	Fixed::operator!=(const Fixed& other) const
{
	return (this->rawBits != other.getRawBits() ? true : false);
}

// Arithmetic operators
Fixed	Fixed::operator+(const Fixed& other) const
{
	Fixed	summy;
	summy.setRawBits(this->rawBits + other.getRawBits());
	return (summy);
}

Fixed	Fixed::operator-(const Fixed& other) const
{
	Fixed	diffy;
	diffy.setRawBits(this->rawBits - other.getRawBits());
	return (diffy);
}

Fixed	Fixed::operator-(void) const
{
	Fixed	neggy;
	neggy.setRawBits(-this->rawBits);
	return (neggy);
}

Fixed	Fixed::operator*(const Fixed& other) const
{
	Fixed	multy;
	multy.setRawBits((int64_t(this->rawBits) * int64_t(other.getRawBits())) >> this->fractionalBits);
	return (multy);
}

Fixed	Fixed::operator/(const Fixed& other) const
{
	Fixed	divvy;
	divvy.setRawBits((int64_t(this->rawBits) << this->fractionalBits) / int64_t(other.getRawBits()));
	return (divvy);
}

// Increment / Decrement
Fixed&	Fixed::operator++(void)
{
	++this->rawBits;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed temp(*this);

    ++this->rawBits;
    return (temp);
}

Fixed&	Fixed::operator--(void)
{
	--this->rawBits;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed temp(*this);

    --this->rawBits;
    return (temp);
}

// Different type's arithmetics
Fixed	Fixed::operator+(const int other) const
{
	Fixed	summy;
	summy.setRawBits(this->rawBits + (other << this->fractionalBits));
	return (summy);
}

Fixed	Fixed::operator+(const float other) const
{
	Fixed	summy ( other );
	summy.setRawBits(summy.getRawBits() + this->rawBits);
	return (summy);
}

Fixed	Fixed::operator-(const int other) const
{
	Fixed	diffy;
	diffy.setRawBits(this->rawBits - (other << this->fractionalBits));
	return (diffy);
}

Fixed	Fixed::operator-(const float other) const
{
	Fixed	diffy ( other );
	diffy.setRawBits(diffy.getRawBits() - this->rawBits);
	return (diffy);
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
