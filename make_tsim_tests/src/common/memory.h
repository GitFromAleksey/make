#if !defined(MEMORY_H_)
#   define MEMORY_H_

#   include "types.h"


namespace Memory
{
    INLINE_TMPL(typename TGT_TYPE, typename SRC_TYPE)
    TGT_TYPE *copy(TGT_TYPE *target, SRC_TYPE *source, u32 size)
    {
        while (size--)
        {
            *target++ = *source++;
        }
        return target;
    }
    //=========================================================================
    INLINE_TMPL(typename TYPE)
    TYPE *set(TYPE *target, TYPE value, u32 size)
    {
        while (size--)
        {
            *target++ = value;
        }
        return target;
    }
    //=========================================================================
    INLINE_TMPL(class TYPE, typename VALUE)
    TYPE *set(TYPE *target, VALUE value)
    {
        u32 size = sizeof(TYPE) / sizeof(VALUE);
        VALUE *ptr = (VALUE *)target;
        while (size--)
        {
            *ptr++ = value;
        }
        return (TYPE *)ptr;
    }
    //=========================================================================
    INLINE_TMPL(typename TYPE)
    bool compare(const TYPE *s1, const TYPE *s2, u32 size)
    {
        while (size--)
        {
            if (*s1++ != *s2++) return false;
        }
        return true;
    }
    //=========================================================================
    INLINE_TMPL(typename TYPE)
    bool compare(const TYPE *s1, TYPE s2, u32 size)
    {
        while (size--)
        {
            if (*s1++ != s2) return false;
        }
        return true;
    }
    //=========================================================================
    INLINE_TMPL(typename TYPE)
    TYPE checksum(const TYPE *data, u32 size)
    {
        TYPE sum = 0;
        while (size--)
        {
            sum += *data++;
        }
        return sum;
    }
    //=========================================================================
    template <typename T>
    void reverse(T *src, u32 size)
    {
        T *head = src;
        T *tail = src + size - 1;
        while (head < tail)
        {
            T x = *head;
            *head++ = *tail;
            *tail-- = x;
        }
    }
    //=========================================================================
    template <typename T>
    T *reverse(T *tgt, T *src, u32 size)
    {
        T *head = tgt;
        T *tail = src + size - 1;
        while (size--)
        {
            *head++ = *tail--;
        }
        return head;
    }
    //=========================================================================
    template
    <
        typename P_OutputType = s16,
        typename P_StoredType = s8,
        u8 p_shift = 0
    >
    struct PackedData_Basic
    {
        typedef P_StoredType StoredType;
        typedef P_OutputType OutputType;
        //------------------------------------------------>
        S_C_U8 shift = p_shift;
        //------------------------------------------------>
        void init(StoredType *_p) {ptr = _p;}
        //------------------------------------------------>
        StoredType *start() {return ptr;}
        //------------------------------------------------>
        template <typename IndexType> OutputType operator [](IndexType i)
        {
            return OutputType(ptr[i]) << shift;
        }
        //------------------------------------------------>
    protected:
        StoredType *ptr;
    };
    //########################################################################
    template
    <
        typename P_OutputType = s16,
        typename P_StoredType = s8,
        typename P_LengthType = s32,
        u8 p_shift = 0
    >
    struct PackedData:
        public PackedData_Basic<P_OutputType, P_StoredType, p_shift>
    {
        typedef P_LengthType LengthType;
        //------------------------------------------------>
        void init(P_StoredType *_p, LengthType _len)
        {
            this->ptr = _p;
            len = _len;
        }
        //------------------------------------------------>
        P_StoredType *end() {return this->ptr + len;}
        //------------------------------------------------>
        LengthType length() {return len;}
        //------------------------------------------------>
    protected:
        LengthType len;
    };
    //#######################################################################
    // Сортированный по возрастанию массив.
    template
    <
        typename P_OutputType = s16,
        typename P_StoredType = s8,
        typename P_LengthType = s32,
        u8 p_shift = 0
    >
    struct PackedData_AscendingSorted:
        public PackedData<P_OutputType, P_StoredType, P_LengthType, p_shift>
    {
        // Получение индекса для аргумента,
        // потенциально выходящего за границы диапазона.
        INLINE s32 getOuterIndex(P_OutputType x)
        {
            s32 i = 0;
            if (x <= this->operator[](i))
            {
                return i;
            }

            i = this->len - 1;
            if (x >= this->operator[](i))
            {
                return i;
            }

            return -1;
        }
        //------------------------------------------------>
        // Поиск ближайшего снизу индекса.
        INLINE s32 findIndex(P_OutputType x)
        {
            s32 il = 0;
            s32 ir = this->len - 1;
            s32 i = il;
            while (il < ir - 1)
            {
                i = (il + ir) / 2;
                if (x < this->operator[](i))
                {
                    ir = i;
                }
                else
                {
                    il = i;
                }
            }
            return il;
        }
    };
    //#######################################################################
    // Циклический буфер.
    class CyclicBuffer
    {
    public:
        void init(u8 *buf_, u32 bufSize_)
        {
            head = tail = buf = buf_;
            last = buf_ + bufSize_ - 1;
            bufSize = bufSize_;
        }
        //------------------------------------------------>
        u32 bytesAvailable()
        {
            return tail - head + (tail >= head ? 0 : bufSize);
        }
        //------------------------------------------------>
        u32 pop(u8 *data, u32 maxSize)
        {
            u32 n = 0;
            while (n != maxSize && head != tail)
            {
                n++;
                *data++ = *head;
                if (head < last)
                {
                    head++;
                }
                else
                {
                    head = buf;
                }
            }
            return n;
        }
        //------------------------------------------------>
        void push(u8 *data, u32 size)
        {
            for (u32 i = 0; i < size; i++)
            {
                *tail = data[i];
                if (tail < last)
                {
                    tail++;
                }
                else
                {
                    tail = buf;
                }
            }
        }
        //------------------------------------------------>
        void setTailIndex(u32 i) {tail = buf + i;}
        //------------------------------------------------>
        void flush() {head = tail;}
        //------------------------------------------------>
    private:
        u8 *buf;
        u32 bufSize;
        u8 *last;
        u8 *head;  // первая занятая ячейка
        u8 *tail;  // первая свободная ячейка
    };
}
//#############################################################################

#endif  // MEMORY_H_
