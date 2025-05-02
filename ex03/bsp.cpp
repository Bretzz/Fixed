/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:33:59 by totommi           #+#    #+#             */
/*   Updated: 2025/05/03 00:35:14 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.h"
// # include "Fixed.hpp"
// # include "Point.hpp"

static Fixed	absF(Fixed fixed)
{
	return (fixed.getRawBits() > 0 ? fixed : -fixed);
}

// using Fixed::epsilon() as limiter for precision (duh?)
static bool shrink(Fixed *Lim, const Fixed& pointCoord)
{
	Fixed const	half = (Lim[0] + Lim[1]) / Fixed ( 2 );

	std::cout << "shrink [" << Lim[0] << "," << Lim[1] << "] -> ";

	if (Fixed::max(pointCoord, half) == half)
		Lim[1] = half;
	else
		Lim[0] = half;
	std::cout << "[" << Lim[0] << "," << Lim[1] << "]" << std::endl;
	return (absF(Lim[0] - Lim[1]) <= Fixed::epsilon() ? true : false);
}

static bool	canIntersect(Point const& a, Point const& b, Fixed& axis)
{
	if (axis == a.getX() || axis == b.getX())
		return (true);
	if (a.getX() == b.getX())
		return (axis == a.getX() ? true : false);
	if (Fixed::max(axis, Fixed::max(a.getX(), b.getX())) == axis)
		return (false);
	if (Fixed::min(axis, Fixed::min(a.getX(), b.getX())) == axis)
		return (false);
	return (true);
}

/* Axis = x-axis */
static Fixed segmentAxisIntersection(Point const& a, Point const& b, Fixed& axis)
{
	if (a.getX() == b.getX())
		return (Fixed(axis));
	if (a.getY() == b.getY())
		return (Fixed (a.getY()));
	Fixed	yInters = (((axis - a.getX()) * (b.getY() - a.getY())) / (b.getX() - a.getX())) + a.getY();
	return (yInters);
}

static Fixed	lesserEvil(Fixed *newLims, int *gotcha)
{
	int	i;

	i = 0;
	while (gotcha[i] == 0)
		i++;
	Fixed	lesser = newLims[i];
	for (int j = i + 1; j < 6; j++) {
		if (gotcha[j] && newLims[j] < lesser)
			lesser = newLims[j];
	}
	return (lesser);
}

static Fixed	greaterEvil(Fixed *newLims, int *gotcha)
{
	int	i;

	i = 0;
	while (gotcha[i] == 0)
		i++;
	Fixed	greater = newLims[i];
	for (int j = i + 1; j < 6; j++) {
		if (gotcha[j] && newLims[j] > greater)
			greater = newLims[j];
	}
	return (greater);
}

static bool stillInside(Fixed *xLim, Fixed *yLim,
	Point const& a, Point const& b, Point const& c, Point const point)
{
	Fixed	newLims[6];
	Fixed	reaLims[2];
	int		gotcha[6] = { 0 };

	// point inside limits?
	if ((Fixed::max(xLim[1], point.getX()) == point.getX() && xLim[1] != point.getX())
		|| (Fixed::min(xLim[0], point.getX()) == point.getX() && xLim[0] != point.getX()))
		return (std::cout << "X strike" << std::endl, false);
	if ((Fixed::max(yLim[1], point.getY()) == point.getY() && yLim[1] != point.getY())
		|| (Fixed::min(yLim[0], point.getY()) == point.getY() && yLim[0] != point.getY()))
		return (std::cout << "Y strike" << std::endl, false);

	//triangle inside limits?
	if (canIntersect(a, b, xLim[0]) && (gotcha[0] = 1))
	{
		newLims[0] = segmentAxisIntersection(a, b, xLim[0]);
		std::cout << "intersection between x=" << xLim[0] << " and " << a << "-" << b << " is " << newLims[0] << std::endl; 
	}
	if (canIntersect(a, c, xLim[0]) && (gotcha[1] = 1))
	{
		newLims[1] = segmentAxisIntersection(a, c, xLim[0]);
		std::cout << "intersection between x=" << xLim[0] << " and " << a << "-" << c << " is " << newLims[1] << std::endl;
	}
	if (canIntersect(b, c, xLim[0]) && (gotcha[2] = 1))
	{
		newLims[2] = segmentAxisIntersection(b, c, xLim[0]);
		std::cout << "intersection between x=" << xLim[0] << " and " << b << "-" << c << " is " << newLims[2] << std::endl;
	}
	if (canIntersect(a, b, xLim[1]) && (gotcha[3] = 1))
	{
		newLims[3] = segmentAxisIntersection(a, b, xLim[1]);
		std::cout << "intersection between x=" << xLim[1] << " and " << a << "-" << b << " is " << newLims[3] << std::endl;
	}
	if (canIntersect(a, c, xLim[1]) && (gotcha[4] = 1))
	{
		newLims[4] = segmentAxisIntersection(a, c, xLim[1]);
		std::cout << "intersection between x=" << xLim[1] << " and " << a << "-" << c << " is " << newLims[4] << std::endl;
	}
	if (canIntersect(b, c, xLim[1]) && (gotcha[5] = 1))
	{
		newLims[5] = segmentAxisIntersection(b, c, xLim[1]);
		std::cout << "intersection between x=" << xLim[1] << " and " << b << "-" << c << " is " << newLims[5] << std::endl;
	}
	reaLims[0] = lesserEvil(newLims, gotcha);
	reaLims[1] = greaterEvil(newLims, gotcha);
	std::cout << "Forced Lims: [" << reaLims[0] << "," << reaLims[1] << "] against yLim[" << yLim[0] << "," << yLim[1] << "]" << std::endl;
	if ((reaLims[0] >= yLim[0] && reaLims[0] <= yLim[1])
		|| (reaLims[0] <= yLim[0] && reaLims[1] >= yLim[0])
		|| (reaLims[1] >= yLim[0] && reaLims[1] <= yLim[1])
		|| (reaLims[1] >= yLim[1] && reaLims[0] <= yLim[1]))
		return (true);
	return (false);
}

static bool	recursiveShrink(Fixed *xLim, Fixed *yLim,
	Point const a, Point const b, Point const c, Point const point,
	int cycle)
{
	bool srk;
	if (!stillInside(xLim, yLim, a, b, c, point))
		return (false);
	(cycle % 2) ? srk = shrink(xLim, point.getX()) : srk = shrink(yLim, point.getY());
	return (srk ? true : recursiveShrink(xLim, yLim, a, b, c, point, ++cycle));
}

static bool onTheLine(Point const a, Point const b, Point const point)
{
	if (a.getX() == b.getX())
		return (a.getX() == point.getX() ? true : false);
	if (a.getY() == b.getY())
		return (a.getY() == point.getY() ? true : false);
	if (point.getY() == (((point.getX() - a.getX()) * (b.getY() - a.getY()))
		/ (b.getX() - a.getX())) + a.getY())
		return (true);
	return (false);
}

/* exit condition: 
 *  TRUE : diff < epsilon
 *  FLASE: out oof boundaries
*/
bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	xLim[2];
	Fixed	yLim[2];

	if (onTheLine(a, b, point)
		|| onTheLine(a, c, point)
		|| onTheLine(b, c, point))
		return (std::cout << "Line strike" << std::endl, false);
	std::cout << "line check passed" << std::endl;
	xLim[0] = Fixed::min(Fixed::min(a.getX(), b.getX()), c.getX());
	xLim[1] = Fixed::max(Fixed::max(a.getX(), b.getX()), c.getX());

	yLim[0] = Fixed::min(Fixed::min(a.getY(), b.getY()), c.getY());
	yLim[1] = Fixed::max(Fixed::max(a.getY(), b.getY()), c.getY());

	std::cout << "xLim[" << xLim[0] << "," << xLim[1] << "]" << std::endl;
	std::cout << "yLim[" << yLim[0] << "," << yLim[1] << "]" << std::endl;

	bool res = recursiveShrink(xLim, yLim, a, b, c, point, 0);
	
	std::cout << "after shrink towards " << point << std::endl;

	std::cout << "xLim[" << xLim[0] << "," << xLim[1] << "]" << std::endl;
	std::cout << "yLim[" << yLim[0] << "," << yLim[1] << "]" << std::endl;

	return (res ? true : false);
}