#if !defined(TYPES_H_)
#   define TYPES_H_

//#############################################################################

#   define JOIN_0(X, Y) X##Y
#   define JOIN(X, Y) JOIN_0(X, Y)

//#############################################################################

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef signed long long int s64;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;

typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef const u8 cu8;
typedef const u16 cu16;
typedef const u32 cu32;
typedef const u64 cu64;

typedef const s8 cs8;
typedef const s16 cs16;
typedef const s32 cs32;
typedef const s64 cs64;

typedef unsigned int uint;

typedef float f32;
typedef double f64;

typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef const f32 cf32;
typedef const f64 cf64;

#   define S_C(TYPE) static const TYPE
#   define S_C_S8  S_C(s8)
#   define S_C_S16 S_C(s16)
#   define S_C_S32 S_C(s32)
#   define S_C_S64 S_C(s64)
#   define S_C_U8  S_C(u8)
#   define S_C_U16 S_C(u16)
#   define S_C_U32 S_C(u32)
#   define S_C_U64 S_C(u64)

#   define S_C_F32 S_C(f32)
#   define S_C_F64 S_C(f64)

#   define U8_MAX  ((u8)0xFF)
#   define S8_MAX  ((s8)0x7F)
#   define S8_MIN  ((s8)0x80)

#   define U16_MAX ((u16)0xFFFF)
#   define S16_MAX ((s16)0x7FFF)
#   define S16_MIN ((s16)0x8000)

#   define U32_MAX ((u32)0xFFFFFFFF)
#   define S32_MAX ((s32)0x7FFFFFFF)
#   define S32_MIN ((s32)0x80000000)

#   define U64_MAX ((u64)0xFFFFFFFFFFFFFFFF)
#   define S64_MAX ((s64)0x7FFFFFFFFFFFFFFF)
#   define S64_MIN ((s64)0x8000000000000000)

//#############################################################################

#   if defined(__GNUC__)
#       define OFFSET_IN_STRUCT(s, name) offsetof(s, name)
#   else
#       define OFFSET_IN_STRUCT(s, name) u32(&((s *)0)->name)
#   endif

//#############################################################################

// Определение длины списка аргументов
#   define __ARG_N( \
        _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
        _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
        _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
        _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
        _61, _62, _63, _64, N, ...) N
#   define __RSEQ_N \
         64, 63, 62, 61, 60, \
         59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
         49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
         39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
         29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
         19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
          9,  8,  7,  6,  5,  4,  3,  2,  1,  0
#   define __ARG_NUM(...) __ARG_N(__VA_ARGS__)
#   define ARG_NUM(...)  __ARG_NUM(__VA_ARGS__, __RSEQ_N)

//#############################################################################

//! Тип указателя на функцию-обработчик прерывания.
typedef void (*Handler)();

//#############################################################################

#   if defined(__GNUC__)
#       define INLINE inline __attribute__ ((always_inline))
#       define NO_INLINE __attribute__ ((noinline))
#       define S_INLINE static INLINE
#       define S_NO_INLINE static NO_INLINE
#       define INLINE_TMPL(...) template <__VA_ARGS__> INLINE
#       define WARN_OFF__UNUSED_VAR
#   elif defined(__ICCARM__)
#       define INLINE    _Pragma("inline = forced")
#       define NO_INLINE _Pragma("diag_suppress = Pe940") \
                         _Pragma("optimize = no_inline")
#       define S_INLINE INLINE static
#       define S_NO_INLINE NO_INLINE static
#       define INLINE_TMPL(...) INLINE template <__VA_ARGS__>
// IAR Warning[Pe177]: variable ___ was declared but never referenced
#       define WARN_OFF__UNUSED_VAR _Pragma("diag_suppress = Pe177")
#   endif
#       define S_INLINE_TMPL(...) INLINE_TMPL(__VA_ARGS__) static
//#############################################################################

#   ifndef __cplusplus

typedef enum {false = 0, true = 1} bool;

#       ifndef FALSE
#          define FALSE false
#       endif

#       ifndef TRUE
#          define TRUE true
#       endif

#       ifndef NULL
#          define NULL ((void *)0)
#       endif

#   else  // __cplusplus

#       ifndef NULL
#           define NULL 0
#       endif

#       define S_C_B S_C(bool)
//#############################################################################

template <typename T>
struct TypeInfo
{
    S_C_U16 bytes = sizeof(T);
    S_C_U16 bits = bytes * 8;
    S_C_B isSigned = T(-1) < 0;
    S_C_B isFloat = ((T)0.1) != 0;
    S_C(T) max = isSigned ?
        ((T(1) << (bits - 2)) - 1) + (T(1) << (bits - 2)) : T(-1);
    S_C(T) min = isSigned ? -max - 1 : 0;
};
//#############################################################################

template <u8 p_len, u8 p_sh, typename P_Type = u32>
struct BitField
{
    typedef P_Type Type;
    S_C_U8 len = p_len;
    S_C_U8 sh = p_sh;
    S_C_S16 msb = s16(len) + sh - 1;
    S_C_U8 lsb = sh;
    S_C(Type) max = len >= TypeInfo<Type>::bits ?
                        TypeInfo<Type>::max : (Type(1) << len) - 1;
    S_C(Type) mask1 = max << sh;
};
//#############################################################################

template <u8, typename> struct EmptyValues {};

template <u8 p_sh = 0, typename P_Type = u32>
struct BoolStates
{
    typedef P_Type Type;
    S_C(Type) off = 0 << p_sh;
    S_C(Type) on  = 1 << p_sh;
    S_C(Type) no  = off;
    S_C(Type) yes = on;
};
//#############################################################################

template
<
    u8 p_len, u8 p_sh, typename P_Type,
    template <u8, typename> class P_Values = EmptyValues
>
struct EnumBitField:
    public BitField<p_len, p_sh, P_Type>,
    public P_Values<0, P_Type>
{
    typedef P_Values<BitField<p_len, p_sh, P_Type>::sh, P_Type> Mask1;
};
//#############################################################################

typedef BitField<0, 0, u32> HeadBitField;
typedef BitField<1, 0, u32> FirstBitField;
template <class BF> struct _PrevBF {S_C_S16 msb = BF::sh - 1;};

#       define BIT_FIELD_STRUCT(Name, len, T, Values, NamePrev) \
            typedef EnumBitField<len, NamePrev::msb + 1, T, Values> Name; \
            struct \
            { \
                T         : Name::sh; \
                T f_##Name : len; \
            }

        #define BIT_FIELD_GROUP_STRUCT(Name, T, First, Last) \
            BIT_FIELD_STRUCT( \
                Name, Last::msb - First::sh + 1, \
                T, EmptyValues, _PrevBF<First>)

#       define BOOL_BIT_FIELD_STRUCT(N, T, NP) \
            BIT_FIELD_STRUCT(N, 1, T, BoolStates, NP)

#       define BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1) \
            BOOL_BIT_FIELD_STRUCT(N1, T, NP)
#       define BOOL_BIT_FIELD_STRUCTS_2(T, NP, N1, N2) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_1(T, N1, N2)
#       define BOOL_BIT_FIELD_STRUCTS_3(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_2(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_4(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_3(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_5(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_4(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_6(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_5(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_7(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_6(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_8(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_7(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_9(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_8(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_10(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_9(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_11(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_10(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_12(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_11(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_13(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_12(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_14(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_13(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_15(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_14(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_16(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_15(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_17(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_16(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_18(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_17(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_19(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_18(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_20(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_19(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_21(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_20(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_22(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_21(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_23(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_22(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_24(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_23(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_25(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_24(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_26(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_25(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_27(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_26(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_28(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_27(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_29(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_28(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_30(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_29(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_31(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_30(T, N1, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS_32(T, NP, N1, ...) \
            BOOL_BIT_FIELD_STRUCTS_1(T, NP, N1); \
            BOOL_BIT_FIELD_STRUCTS_31(T, N1, __VA_ARGS__)

#       define _BOOL_BF_STRUCTS_0(N, ...) \
            BOOL_BIT_FIELD_STRUCTS_##N(__VA_ARGS__)
#       define _BOOL_BF_STRUCTS(N, ...) \
            _BOOL_BF_STRUCTS_0(N, __VA_ARGS__)
#       define BOOL_BIT_FIELD_STRUCTS(T, NP, ...) \
            _BOOL_BF_STRUCTS(ARG_NUM(__VA_ARGS__), T, NP, __VA_ARGS__)

//#############################################################################

union SynchData
{
    u32 all;
    u16 ch[2];
    //-----------------------------------------------------------------------
    void set(const SynchData &src) {all = src.all;}
    void reset(u32 v = 0) {all = v;}
    void write(u16 ch0, u16 ch1) {all = ch0 | (u32(ch1) << 16);}
    u32 operator [](cu8 i) {return ch[i];}
};
//#############################################################################

#   endif  // __cplusplus

#   if defined(__DEBUG__)
#      define DEBUG_LINE(x) x
#      define DEBUG_PUBLIC(n) public
#   else
#      define DEBUG_LINE(x)
#      define DEBUG_PUBLIC(n) n
#   endif

//#############################################################################

#endif  // TYPES_H_
