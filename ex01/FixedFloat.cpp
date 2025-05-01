/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FixedFloat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:02:06 by totommi           #+#    #+#             */
/*   Updated: 2025/05/02 00:49:37 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <iomanip>
#include <math.h>

/* MEMBER FUNCTIONS */

float	Fixed::toFloat(void) const
{
	// float	myFloat;

	// // adding the integer part of the Fixed point number
	// myFloat = this->rawBits >> this->fractionalBits;
	// for (int i = 0; i < this->fractionalBits; i++) {
	// 	if ((this->rawBits >> i) & 1)
	// 	{
	// 		// adding the decimal part, stored in negative powers (2e-i)
	// 		myFloat += 1.0f / pow(2, ((this->fractionalBits - i)));
	// 	}
	// }
	// return (myFloat);
	return double(this->rawBits) / double(1 << this->fractionalBits);	//ok what?
}

/* CONSTRUCTORS & DESTRUCTORS */


/* My baby :') */
Fixed::Fixed(const float rawFloat)
{
	std::cout << "Float constructor called" << std::endl;
	// const int64_t	fixedBrick = int64_t(1.0f / pow(2, this->fractionalBits) * pow(10, this->fractionalBits / 2));
	// float			myRawFloat = rawFloat;

	// /* normalizing negative numbers and storing the sigh for later */
	// char sign = myRawFloat < 0 ? -1 : 1;
	// myRawFloat *= sign;
	// /* taking out the decimals: '1234' out oof '205.1234' */
	// int64_t	decimals = (myRawFloat - (int)myRawFloat) * pow(10, this->fractionalBits / 2);
	// /* adding the integer part */
	// this->rawBits = (int32_t)(myRawFloat) << this->fractionalBits;
	// /*	
	//  *	For each one of the fractional bits, if it's contained in decimal
	//  *	we subtract it's represented 'value' from 'decimals' and add it to 'rawBits'
	// */
	// for (int i = 0; i < this->fractionalBits; i++) {
	// 	const float	fixedFract = fixedBrick * pow(2, this->fractionalBits - (i + 1));
	// 	if (decimals > fixedFract)
	// 	{
	// 		decimals -= fixedFract;
	// 		this->rawBits += pow(2, this->fractionalBits - (i + 1));
	// 	}
	// }
	// /*
	//  *	better rounding possible thanks to the decimals
	//  *	being stored in integers and not really small floats
	// */
	// if (decimals > (fixedBrick / 2))	// im the goat
	// 	this->rawBits += 1;
	// /* signing the bits with integer arithmetic */
	// this->rawBits *= sign;
	this->rawBits = int32_t(rawFloat * double(1 << this->fractionalBits) + (rawBits >= 0 ? 0.5 : -0.5));	//what is this sorcery?
}
//-42.419996128968 -42.419996128968
