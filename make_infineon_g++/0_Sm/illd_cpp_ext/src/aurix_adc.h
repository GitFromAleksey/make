#if !defined(AURIX_ADC_H_)
#define AURIX_ADC_H_

namespace Aurix
{
    namespace Adc
    {
        constexpr f32 conversionTime(
            u32 analog_clock,
            u32 digital_clock,
            u32 resolution = 12,
            bool postCalibration = true)
        {
            return f32(resolution + 0 + 2 * postCalibration) / analog_clock + 2.F / digital_clock;
        }
    }
}


#endif // AURIX_ADC_H_
