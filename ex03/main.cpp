/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:29:43 by totommi           #+#    #+#             */
/*   Updated: 2025/05/02 18:55:16 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.h"
#include <iostream>

int	main(void)
{
	Point a ( 0.0f, 2.0f );
	Point b ( 0.0f, 0.0f );
	Point c ( 2.0f, 0.0f );

	std::cout << a << b << c << std::endl;

	if (bsp(a, b, c, Point ( 0.1f, 0.5f )))
		std::cout << "OK" << std::endl;
	else
		std::cout << "KO" << std::endl;

	return (0);
}
