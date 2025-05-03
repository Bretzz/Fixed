/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:39:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/03 21:49:49 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>
# include <math.h>

# define DECIMALS 8 /* how deep in the float you wanna go to get decimals. */
/* Example: fractionalBits is set to 8, the smallest rapresentable number is 2e-8, eg. 0.00390625.
You could settle with 0.0039, or you could take the whole 0.00390625, the calculation will get
a bit slower (dunno how to measure it... but itsn't much) while interacting
with floating point numbers (constructor and operations). */

/* NOTE: leave at least one bit for the integer part (pls),
also not recommended to go beyond 16 fractional_bits  */
/* DEV: maybe '==' more generous? */
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
		// Constructors and Destructor(s)
		Fixed();
		Fixed( const Fixed& );
		Fixed( const int );
		Fixed( const float );
		~Fixed();

		// Getters and setters for raw bits
		int32_t		getRawBits( void ) const;	// const tells us that this funnction can be used also on 'const Fixed' variables
		void		setRawBits( int32_t const raw );

		// Conversion functions
		int			toInt( void ) const;
		float		toFloat( void ) const;
		std::string toString( void ) const;
		
		// Assignment operators
		void	operator=( const Fixed& );
		/*	
		 *	Future Patch:
		 *	void	operator+=( const Fixed& );
		 *	void	operator-=( const Fixed& );
		 *	void	operator*=( const Fixed& );
		 *	void	operator/=( const Fixed& );
		*/

		// Comparison operators
		bool operator>( const Fixed& ) const;
		bool operator<( const Fixed& ) const;
		bool operator>=( const Fixed& ) const;
		bool operator<=( const Fixed& ) const;
		bool operator==( const Fixed& ) const;
		bool operator!=( const Fixed& ) const;

		// Arithmetic operators
		Fixed operator+( const Fixed& ) const;
		Fixed operator-( const Fixed& ) const;
		Fixed operator-( void ) const;	// Negate Unary
		Fixed operator*( const Fixed& ) const;
		Fixed operator/( const Fixed& ) const;

		// Increment / Decrement
		Fixed& operator++();		// pre-increment
		Fixed operator++(int);		// post-increment
		Fixed& operator--();		// pre-decrement
		Fixed operator--(int);		// post-decrement

		// Arithmetics with different types
		Fixed operator+( const int ) const;
		Fixed operator+( const float ) const;
		Fixed operator-( const int ) const;
		Fixed operator-( const float ) const;
		/*
		 *	Future Patch:
		 *	Fixed operator*(const int ) const;
		 *	Fixed operator*(const float ) const;
		 *	Fixed operator/(const int ) const;
		 *	Fixed operator/(const float ) const;
		*/

		// static member function can be called even without an object of the class being created
		static Fixed&		min( Fixed&, Fixed& );
		static const Fixed&	min( const Fixed&, const Fixed& );
		static Fixed&		max( Fixed&, Fixed& );
		static const Fixed&	max( const Fixed&, const Fixed& );

		// Smallest rapresentable Fixed number.
		static Fixed		epsilon( void );
};

// ostream overload
std::ostream& operator<<( std::ostream&, const Fixed& );
	
#endif