//
//  GDRandom.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-11-01.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GDRandom.h"
#include <time.h>
#include <limits.h>


GDRandom::GDRandom()
{
    //Initialize members
	m_Seed = 1;
    m_Index = CMATH_N + 1;
}

unsigned int GDRandom::random(unsigned int n)
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0, CMATH_MATRIX_A};

    //Safety check, ensure n is not zero, if it is return zero
	if(n == 0)
    {
		return 0;
    }

    //mag01[x] = x * MATRIX_A  for x = 0,1

    if(m_Index >= CMATH_N)
    {
        //generate N words at one time
        int kk;

        //
        if (m_Index == CMATH_N + 1)   //if setSeed() has not been called
        {
            setSeed(4357); //a default initial seed is used
        }

        for (kk = 0; kk < CMATH_N - CMATH_M; kk++)
        {
            y = (m_Mt[kk] & CMATH_UPPER_MASK) | (m_Mt[kk+1] & CMATH_LOWER_MASK);
            m_Mt[kk] = m_Mt[kk+CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        
        for(; kk < CMATH_N - 1; kk++)
        {
            y = (m_Mt[kk] & CMATH_UPPER_MASK) | (m_Mt[kk+1] & CMATH_LOWER_MASK);
            m_Mt[kk] = m_Mt[kk+ (CMATH_M - CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (m_Mt[CMATH_N-1] & CMATH_UPPER_MASK) | (m_Mt[0] & CMATH_LOWER_MASK);
        m_Mt[CMATH_N-1] = m_Mt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        m_Index = 0;
    }
  
    y = m_Mt[m_Index++];
    y ^= CMATH_TEMPERING_SHIFT_U(y);
    y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
    y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
    y ^= CMATH_TEMPERING_SHIFT_L(y);

    return (y % n);
}

float GDRandom::random()
{
	float r = (float)random(INT_MAX);
	float divisor = (float)INT_MAX;
	return (r / divisor);
}

void GDRandom::setSeed(unsigned int n)
{
	// Setting initial seeds to mt[N] using the generator Line 25 of Table 1 in
	// [KNUTH 1981, The Art of Computer Programming Vol. 2 (2nd Ed.), pp102]
	m_Mt[0]= n & 0xffffffff;
	for (m_Index = 1; m_Index < CMATH_N; m_Index++)
    {
		m_Mt[m_Index] = (69069 * m_Mt[m_Index-1]) & 0xffffffff;
    }

	m_Seed = n;
}

unsigned int GDRandom::getSeed()
{
	return m_Seed;
}

unsigned int GDRandom::randomizeSeed()
{
	setSeed((unsigned int)time(NULL));
    return getSeed();
}
