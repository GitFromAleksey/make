#if !defined(ADC_H)
#   define ADC_H

#   include <types.h>


template < u8 BITS, typename RESULT_TYPE >
struct Adc
{
    struct Result
    {
        struct Right
        {
            S_C(RESULT_TYPE) max =
                (RESULT_TYPE(1) << (BITS - 1) - 1)
                + (RESULT_TYPE(1) << (BITS - 1));

            S_INLINE RESULT_TYPE get
            (
                double input,
                double vref,
                double r1 = 1,
                double r2 = 1
            )
            {
                input *= r2 / (r1 + r2);

                if (input <= 0) return 0;
                if (input >= vref) return max;

                return RESULT_TYPE(input / vref * max + 0.5);
            }
        };
        //-------------------------------------------------------------------
        struct Left
        {
            S_C_U8 shift = 8 * sizeof(RESULT_TYPE) - BITS;
            S_C(RESULT_TYPE) max = Right::max << shift;

            S_INLINE RESULT_TYPE get
            (
                double input,
                double vref,
                double r1 = 1,
                double r2 = 1
            )
            {
                return Right::get(input, vref, r1, r2) << shift;
            }
        };
    };
};
//---------------------------------------------------------------------------
#endif  // ADC_H
