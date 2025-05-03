
#include "Fixed.hpp"

/* Later replaced 'this->fractionalBits / 2'
with an arbitrary value of significant decimal digits wanted. */
Fixed::Fixed(const float rawFloat)
{
	const int64_t	fixedBrick = int64_t(1.0f / pow(2, this->fractionalBits) * pow(10, this->fractionalBits / 2));
	float			myRawFloat = rawFloat;

	/* normalizing negative numbers and storing the sigh for later */
	char sign = myRawFloat < 0 ? -1 : 1;
	myRawFloat *= sign;
	/* taking out the decimals: '1234' out oof '205.1234' */
	int64_t	decimals = (myRawFloat - (int)myRawFloat) * pow(10, this->fractionalBits / 2);
	// std::cout << "copying " << (int)myRawFloat << "." << decimals << std::endl;
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
	this->rawBits *= sign;
}