/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:35:02 by totommi           #+#    #+#             */
/*   Updated: 2025/05/02 18:06:02 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>
#include <iomanip>

/* CONSTRUCTORS & DDESTRUCTORS */

Point::Point(void) { /* Nothing to see here */ }

Point::Point(const Point& other)
	: x(other.getX()), y(other.getY()) { /* Nothing to see here */ }

Point::Point(const float floatX, const float floatY)
	: x(floatX), y(floatY) { /* Nothing to see here */ }

Point::Point(const float floatX, const Fixed& fixedY)
	: x(floatX), y(fixedY) { /* Nothing to see here */ }

Point::Point(const Fixed& fixedX, const float floatY)
	: x(fixedX), y(floatY) { /* Nothing to see here */ }

Point::Point(const Fixed& fixedX, const Fixed& fixedY)
	: x(fixedX), y(fixedY) { /* Nothing to see here */ }

Point::~Point(void) { /* Nothing to see here */ }

/* MEMBER FUNCTIONS */

const Fixed&	Point::getX( void ) const
{
	return(this->x);
}

const Fixed&	Point::getY( void ) const
{
	return(this->y);
}

int32_t	Point::getRawX(void) const
{
	return (this->x.getRawBits());
}

int32_t	Point::getRawY(void) const
{
	return (this->y.getRawBits());
}

/* OPERATORS OVERLOAD */

void	Point::operator=(const Point& other)
{
	(void)other;
	std::cerr << "This class can’t be reassigned once constructed." << std::endl;
	// this->x.setRawBits(other.getRawX());
	// this->y.setRawBits(other.getRawY());
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
	out << "(" << point.getX() << "," << point.getY() << ")";
	return (out);
}
