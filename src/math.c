#include <types.h>

u64 __udivdi3(u64 dividend, u64 divisor)
{
	u64 quotient  = 0;
	u64 remainder = 0;
	
	if(divisor == 0) return 0;
	
	if(dividend < divisor) return dividend;
	
	for(int bit = 63; bit >= 0; bit--)
	{
		remainder <<= 1;
		
		u64 current_bit = (dividend >> bit) & 1;
		remainder |= current_bit;
		
		if (remainder >= divisor) {
    		remainder -= divisor;
    		quotient |= (1ULL << bit);
		}
	}
	
	return quotient;
}
