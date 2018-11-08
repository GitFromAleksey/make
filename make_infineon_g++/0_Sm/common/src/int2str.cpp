#include "int2str.h"

//#############################################################################

template <typename Num>
inline char *uintToStr_T(Num n, char *str, u8 radix, u8 width)
{
    char *res;

    if (radix > 1)
    {
        char *str_p = str;
        //.....................................................................
        // получаем цифры числа в обратной последовательности
        Num n0;
        do
        {
            // минимизируем количество операций делени€ за один цикл
            n0 = n;
            n /= radix;
            *str_p++ = hexDigit(n0 - radix * n);
        }
        while (n != 0);
        //.....................................................................
        // заполн€ем ведущими нул€ми
        s32 len = str_p - str;
        while (len++ < width)
        {
            *str_p++ = '0';
        }
        //.....................................................................
        // оформл€ем конец строки
        res = str_p;
        *str_p-- = 0;
        //.....................................................................
        // преобразуем в пр€мую последовательность цифр
        do
        {
            char b = *str;
            *str++ = *str_p;
            *str_p-- = b;
        }
        while (str_p >= str);
    }
    else
    {
        res = str;
    }

    return res;
}
//#############################################################################

char *uintToStr(u32 n, char *str, u8 radix, u8 width)
{
    return uintToStr_T(n, str, radix, width);
}
//#############################################################################

char *intToStr(s32 n, char *str, u8 radix, u8 width)
{
    if (n < 0)
    {
        n = -n;
        *str++ = '-';
    }

    return uintToStr(u32(n), str, radix, width);
}
//#############################################################################

char *ui64ToStr(u64 n, char *str, u8 radix, u8 width)
{
    return uintToStr_T(n, str, radix, width);
}
//#############################################################################

char *uintToStr(u32 n, s8 q, char *str, u8 radix, u8 precision)
{
    u32 n_round = q == 0 ? 0 : 1UL << (q - 1);

    if (precision == 0)
    {
        n += n_round;
    }

    str = uintToStr(n >> q, str, radix);

    if (precision != 0)
    {
        u32 maxFr = radix;
        u32 i = precision;
        while (--i) maxFr *= radix;

        u64 frBin = n & ((1UL << q) - 1);
        u32 frDec = (frBin * maxFr + 0 * n_round) >> q;
        char *frStr = str + precision;
        do
        {
            *frStr-- = frDec % radix + 0x30;
            frDec /= radix;
        }
        while (frStr > str);

        *str++ = '.';
        str += precision;
        *str = 0;
    }

// неправильна€ дробна€ часть (плавают разр€ды при ведущих нулевых цифрах!)
//	u32 m = 1;
//
//	for (u32 p = 0; p < precision; p++)
//	{
//		m *= radix;
//	}
//
//	// выделение нужного количества знаков после точки и округление
//	u64 nm = u64(n) * m + (q > 0 ? 1UL << (q - 1) : 0) >> q;
//
//	u32 ni = nm / m;
//	u32 nf = u32(nm) - ni * m;  // старшие 32 бит не вли€ют
//
//	str = uintToStr(ni, str, radix);
//
//	if (q > 0 && precision > 0)
//	{
//		*str++ = '.';
//		str = uintToStr(nf, str, radix);
//	}

    return str;
}
//#############################################################################

char *intToStr(s32 n, s8 q, char *str, u8 radix, u8 precision)
{
    if (n < 0)
    {
        n = -n;
        *str++ = '-';
    }

    return uintToStr(u32(n), q, str, radix, precision);
}
//#############################################################################

bool strToNum(char *str, u32 *out, u8 radix)
{
    if (radix <= 1) return false;

    u32 res = 0;
    u32 b;

    while (*str != 0)
    {
        b = *str++;

        if (b >= 'a')
        {
            b = b - 'a' + 10;
        }
        else if (b >= 'A')
        {
            b = b - 'A' + 10;
        }
        else if (b >= '0')
        {
            b -= '0';
        }
        else
        {
            return false;
        }

        if (b >= radix) return false;

        res = res * radix + b;
    }

    *out = res;

    return true;
}
//#############################################################################
