#if !defined(ARRAY_H_)
#define ARRAY_H_

#include <cstddef>
#include <algorithm>

namespace cmn
{
    template < class T, std::size_t N >
    class array
    {
    public:
        T elems[N];    // fixed-size array of elements of type T
    public:
        // type definitions
        typedef T value_type;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef T& reference;
        typedef const T& const_reference;
        typedef std::size_t size_type;

        // iterator support
        iterator begin()
        {
            return elems;
        }
        const_iterator begin() const
        {
            return elems;
        }
        const_iterator cbegin() const
        {
            return elems;
        }

        iterator end()
        {
            return elems + N;
        }
        const_iterator end() const
        {
            return elems + N;
        }
        const_iterator cend() const
        {
            return elems + N;
        }

        // operator[]
        reference operator[](size_type i)
        {
            return elems[i];
        }

        const_reference operator[](size_type i) const
        {
            return elems[i];
        }

        // front() and back()
        reference front()
        {
            return elems[0];
        }

        const_reference front() const
        {
            return elems[0];
        }

        reference back()
        {
            return elems[N - 1];
        }

        const_reference back() const
        {
            return elems[N - 1];
        }

        // size is constant
        static size_type size()
        {
            return N;
        }
        static const size_type csize = N;

        // direct access to data (read-only)
        const T* data() const
        {
            return elems;
        }
        T* data()
        {
            return elems;
        }

        // use array as C array (direct read/write access to data)
        T* c_array()
        {
            return elems;
        }

        // assignment with type conversion
        template < typename T2 >
        array< T, N >& operator=(const array< T2, N >& rhs)
        {
            std::copy(rhs.begin(), rhs.end(), begin());
            return *this;
        }

        template < typename T2 >
        array< T, N >& operator=(const char (&rhs)[N])
        {
            std::copy(&rhs[0], &rhs[N], begin());
            return *this;
        }

        // assign one value to all elements
        void fill(const T& value)
        {
            std::fill_n(begin(), size(), value);
        }

    };

    // comparisons
    template < class T, std::size_t N >
    bool operator==(const array< T, N >& x, const array< T, N >& y)
    {
        return std::equal(x.begin(), x.end(), y.begin());
    }

    template < class T, std::size_t N >
    bool operator!=(const array< T, N >& x, const array< T, N >& y)
    {
        return !(x == y);
    }

    template < class T, std::size_t N >
    bool operator>(const array< T, N >& x, const array< T, N >& y)
    {
        return y < x;
    }

    template < class T, std::size_t N >
    bool operator<=(const array< T, N >& x, const array< T, N >& y)
    {
        return !(y < x);
    }

    template < class T, std::size_t N >
    bool operator>=(const array< T, N >& x, const array< T, N >& y)
    {
        return !(x < y);
    }

    template < typename T, std::size_t N >
    T(&get_c_array(cmn::array< T, N >& arg))[N]
        {
            return arg.elems;
        }

    template < typename T, std::size_t N >
    const T(&get_c_array(const cmn::array< T, N >& arg))[N]
        {
            return arg.elems;
        }

    template <class T, std::size_t N>
    class ArrayIterator
    {
        typedef cmn::array<T, N> ct;
        typedef typename ct::iterator iterator;
        typedef typename ct::const_iterator const_iterator;
        const ct *c;
        const_iterator e;
        const_iterator i;
    public:
        inline ArrayIterator()
        {
        }
        inline ArrayIterator(const ct &container, std::size_t len): c(0)
        {
            init(container, len);
        }
        inline void init(const ct &container, std::size_t len)
        {
            c = &container;
            e = c->cbegin() + len;
            i = c->cbegin();
        }
        inline void toFront() { i = c->begin(); }
        inline void toBack() { i = e; }
        inline bool hasNext() const { return i < e; }
        inline const T &next() { return *i++; }
        inline const T &peekNext() const { return *i; }
        inline std::size_t stepsToFront() const
        {
            return std::distance(c->cbegin(), i);
        }
        inline std::size_t stepsToBack() const
        {
            return std::distance(i, e);
        }
        inline std::size_t length() const
        {
            return std::distance(c->cbegin(), e);
        }
        inline bool isValid() const { return i <= e; }
    };

    template <class T, std::size_t N>
    class MutableArrayIterator
    {
        typedef cmn::array<T, N> ct;
        typedef typename ct::iterator iterator;
        ct *c;
        iterator e;
        iterator i;
    public:
        inline MutableArrayIterator()
        {
        }

        inline MutableArrayIterator(const ct &container, std::size_t len): c(&container)
        {
            init(container, len);
        }

        inline void init(ct &container, std::size_t len)
        {
            c = &container;
            e = c->begin() + len;
            i = c->begin();
        }
        inline void toFront() { i = c->begin(); }
        inline void toBack() { i = e; }
        inline bool hasNext() const { return i < e; }
        inline T &next() { return *i++; }
        inline T &peekNext() const { return *i; }
        inline std::size_t stepsToFront() const
        {
            return std::distance(c->begin(), i);
        }
        inline std::size_t stepsToBack() const
        {
            return std::distance(i, e);
        }
        inline std::size_t length() const
        {
            return std::distance(c->begin(), e);
        }
        inline void fillNext(T v)
        {
            while(hasNext())
            {
                next() = v;
            }
        }
        inline bool isValid() const { return i <= e; }
    };
                    struct size_t
                    {
                    };

}
#endif // ARRAY_H_
