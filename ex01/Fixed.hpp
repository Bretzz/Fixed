/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:39:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/04/30 23:35:33 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# define FLOAT_EPSILON 	1.1929093e-7

#include <iostream>

/* width = 32, binary point = 24 */
class Fixed
{
	private:
		int					raw_bits;
		static const int	fractional_bits = 8;
	public:
		Fixed();
		Fixed( const Fixed& );
		Fixed( const int );
		Fixed( const float );

		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		//void	printRawBits( void );
		float	toFloat( void ) const;
		int		toInt( void ) const;

		void	operator=( const Fixed& );
		//std::ostream& operator<<( std::ostream&, const Fixed& );
		
		~Fixed();
		
};
std::ostream& operator<<( std::ostream&, const Fixed& );
	
#endif