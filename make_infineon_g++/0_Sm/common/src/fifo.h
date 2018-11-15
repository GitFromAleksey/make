#if !defined(FIFO_H)
#   define FIFO_H

#   include <types.h>

//#############################################################################

template < class OBJECT, u16 SIZE >
class Fifo
{
public:
    S_C_U16 size = SIZE;
    //-----------------------------------------------------------------------
    void reset(const OBJECT &obj)
    {
        if (size == 2)
        {
            array[0] = obj;
            array[1] = obj;
        }
        else if (size == 3)
        {
            array[0] = obj;
            array[1] = obj;
            array[2] = obj;
        }
        else
        {
            for (u32 i = 0; i < size; i++)
            {
                array[i] = obj;
            }
        }
    }
    //-----------------------------------------------------------------------
    void move()
    {
        if (size == 2)
        {
            array[1] = array[0];
        }
        else if (size == 3)
        {
            array[2] = array[1];
            array[1] = array[0];
        }
        else
        {
            for (u32 i = size - 1; i > 0; i--)
            {
                array[i] = array[i - 1];
            }
        }
    }
    //-----------------------------------------------------------------------
    void push(const OBJECT &obj)
    {
        move();
        array[0] = obj;
    }
    //-----------------------------------------------------------------------
    const OBJECT &operator [](cu8 i) const {return array[i];}
    //-----------------------------------------------------------------------
protected:
    OBJECT array[SIZE];
};
//#############################################################################

#endif  // FIFO_H
