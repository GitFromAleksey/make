#if !defined(INT2STR_H)
#   define INT2STR_H

#   include "types.h"

//#############################################################################

inline char hexDigit(u8 n) {return n < 10 ? n + '0' : n - 10 + 'A';}
inline char *digToStr(u8 v, char *p) {*p++ = '0' + v; *p = 0; return p;}
inline char *boolToStr(bool v, char *p) {return digToStr(v, p);}

//#############################################################################

inline char *hexlify(u8 n, char *hex)
{
    *hex++ = hexDigit(n >> 4);
    *hex++ = hexDigit(n & 0x0F);
    return hex;
}
//#############################################################################

inline char *hexlify(u32 n, char *hex)
{
    for (u32 i = 0; i < 4; i++)
    {
        hex = hexlify(u8(n), hex);
        n >>= 8;
    }
    return hex;
}
//#############################################################################

template <typename T>
char *hexlify(T *src, u32 len, char *hex)
{
    for (u32 i = 0; i < len; i++) {hex = hexlify(*src++, hex);}
    *hex = 0;
    return hex;
}
//#############################################################################

char *uintToStr(u32 n, char *str, u8 radix = 10, u8 width = 0);
char *intToStr(s32 n, char *str, u8 radix = 10, u8 width = 0);

char *ui64ToStr(u64 n, char *str, u8 radix = 10, u8 width = 0);

char *uintToStr(u32 n, s8 q, char *str, u8 radix = 10, u8 precision = 0);
char *intToStr(s32 n, s8 q, char *str, u8 radix = 10, u8 precision = 0);

inline char *floatToStr(f32 x, char *s, s8 q = 15, u8 rad = 10, u8 prec = 4)
{
    return intToStr(s32(x * (1L << q)), q, s, rad, prec);
}

bool strToNum(char *str, u32 *out, u8 radix);

//#############################################################################

#endif  // INT2STR_H
