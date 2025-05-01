/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:39:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/02 00:25:09 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>

/* NOTE: leave at least one bit for the integer part (pls),
also not recommended to go beyond 16 fractional_bits  */
class Fixed
{
	private:
		/*
		 *	Bytes where the Fixed Point (FP) number is stored.
		 *	The arithmetics for FP numbers is inherited from the Integers,
		 *	so we store the bits in an Integer variable (int32_t for consistency).
		*/
		int32_t				rawBits;
		/*
		 *	The Fractional Bits are the bits dedicated to store the decimal part of the fixed point number.
		 *	The fractionalBits (fB) variable indicates how many bits are Fractional Bits,
		 *	note that the Fractional Bits are the one at the rightmost part of the int32_t's bytes.
		 *	Example: fB=8, iiiiiiii iiiiiiii iiiiiiii ffffffff, where 'i' is for integer bits and 'f' for fractional bits.
		 *	For this reason the overflow totally skrews the Fixed Point notation.
		*/
		static const int	fractionalBits = 8;	// don't go beyond 31
	public:
		Fixed();
		Fixed( const Fixed& );
		Fixed( const int );
		Fixed( const float );

		int			getRawBits( void ) const;	// const tells us that this funnction can be used also on 'const Fixed' variables
		void		setRawBits( int32_t const raw );
		int			toInt( void ) const;
		float		toFloat( void ) const;
		std::string toString( void ) const;

		void	operator=( const Fixed& );
		
		~Fixed();
};

std::ostream& operator<<( std::ostream&, const Fixed& );
	
#endif