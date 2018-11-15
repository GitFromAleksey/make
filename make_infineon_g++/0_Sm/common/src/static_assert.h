#if !defined(STATIC_ASSERT_H)
#   define STATIC_ASSERT_H

#   include "types.h"


template<bool> struct StaticAssert;
template<> struct StaticAssert<true> {};

#   define STATIC_ASSERT(expr) \
        WARN_OFF__UNUSED_VAR \
        StaticAssert<(expr) != 0> JOIN(staticAssert_, __LINE__)

#endif  // STATIC_ASSERT_H
