#if !defined(STR_H)
#   define STR_H

#   include <types.h>

//#############################################################################

inline u32 strlen(const char *str)
{
    u32 length = 0;
    while (*str++) length++;
    return length;
}
//#############################################################################

inline u32 strlen(const char *str, u32 maxlen)
{
    u32 length = 0;
    while (length < maxlen && *str++) length++;
    return length;
}
//#############################################################################

inline char *strcpy(char *target, const char *source)
{
    while (*source)
    {
        *target++ = *source++;
    }
    *target = 0;
    return target;
}
//#############################################################################

#endif  // STR_H
