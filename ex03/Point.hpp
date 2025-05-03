/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:31:16 by totommi           #+#    #+#             */
/*   Updated: 2025/05/03 14:18:17 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"
# include <iostream>

class Point
{
	private:
		Fixed const	x;
		Fixed const	y;
		// Fixed	z;
	public:
		Point();
		Point( const Point& );
		Point( const float, const float );
		Point( const Fixed&, const float );
		Point( const float, const Fixed& );
		Point( const Fixed&, const Fixed& );
		~Point();

		const Fixed&	getX( void ) const;
		const Fixed&	getY( void ) const;

		__int32_t	getRawX( void ) const;
		__int32_t	getRawY( void ) const;
	
		void	operator=( const Point& );
	
};

std::ostream& operator<<( std::ostream&, const Point& );

#endif