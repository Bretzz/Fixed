#include "Fixed.hpp"

Fixed::Fixed(const float rawFloat)
{
	this->rawBits = int32_t(rawFloat * double(1 << this->fractionalBits) + (rawFloat >= 0 ? 0.5 : -0.5));	//what is this sorcery?
}