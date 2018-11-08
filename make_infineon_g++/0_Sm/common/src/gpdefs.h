/*!
 * \file
 * General Purpose DEFinitionS - ����� ����������� ������ ����������.
 */

#if !defined(GPDEFS_H)
#   define GPDEFS_H


/*!
 * \brief ����������� ������� ������������ �������
 *        � ��������� �������� �����������.
 * \param a ��������� �� ������
 */
#define SIZEOFARRAY(a) (sizeof(a) / sizeof(a[0]))

/*!
 * \brief ����������� ������������ ����� ������ ��� ������������ ������.
 * \param s ��������� �� �����
 */
#define STRMAXLEN(s) (SIZEOFARRAY(s) - 1)

/*!
 * \brief ��������� �������� ��������� ���� �� ������� (�������������� �����).
 * \param ptr ����� �������
 * \param i ������ ��������
 * \param type �������� ���
 * \return ������ �� �������
 */
#define GET_REF(ptr, i, type) (((type *)(ptr))[i])

//---------------------------------------------------------------------------
// ����������
//---------------------------------------------------------------------------

/*!
 * \brief ������������ �� ���� �����.
 * \param x ����� 1
 * \param y ����� 2
 * \return max{x, y}
 */
#define _MAX(x, y) ((x) > (y) ? (x) : (y))

/*!
 * \brief ����������� �� ���� �����.
 * \param x ����� 1
 * \param y ����� 2
 * \return min{x, y}
 */
#define _MIN(x, y) ((x) < (y) ? (x) : (y))

/*!
 * \brief M����� �����.
 * \param x �����
 * \return |x|
 */
#define _ABS(x) ((x) >= (0) ? (x) : (-(x)))

/*!
 * \brief ���� �����.
 * \param x �����
 * \return sign(x)
 */
#define _SIGN(x) ((x) >= 0 ? 1 : -1)

/*!
 * \brief ������ ������ ����� �� �������������� ��������� ���������.
 * \param x �������� �����
 * \param x_max ������������ ��������
 * \return ���������� �������, ���� ������ ����� �� ��������� ���������
 */
#define BELOW(x, x_max) ((x) >= 0 ? (x) < (x_max) : -(x) < (x_max))

/*!
 * \brief ������ ������ ����� �� ����� �� ���������.
 * \param x �������� �����
 * \param x_min ����������� ��������
 * \return ���������� �������, ���� ������ ����� ��������� ��������
 */
#define ABOVE(x, x_min) ((x) >= 0 ? (x) > (x_min) : -(x) > (x_min))

/*!
 * \brief ���������� ����� �� ���������� ������.
 * \param x �����
 * \param type ��� ������������ �����
 * \return ����������� �����
 */
#define ROUND(x, type) ((type)((x) >= 0 ? (x) + 0.5 : (x) - 0.5))

/*!
 * \brief ���������� ����� �� ���������� �� ����������� � +inf ������.
 * \param x �����
 * \param type ��� ������������ �����
 * \return ����������� �����
 */
#define ROUNDUP(x, type) \
    ((type)(((x) - (type)(x)) != 0 ? ((type)(x) + 1) : ((type)(x))))

/*!
 * \brief ���������� ����� �� ���������� �� ����������� � -inf ������.
 * \param x �����
 * \param type ��� ������������ �����
 * \return ����������� �����
 */
#define ROUNDDOWN(x, type) \
    ((type)(((x) - (type)(x)) != 0 ? ((type)(x) - 1) : ((type)(x))))

/*!
 * \brief ������������ ����������� ���� �����.
 * \param cell1 ������ 1
 * \param cell2 ������ 2
 * \param temp ��������������� ������
 */
#define XCHNG(cell1, cell2, temp) temp = cell1, cell1 = cell2, cell2 = temp

/*!
 * \brief �������������� float � Q-������.
 * \param val �������� �������� � ��������� ������
 * \param n Q-������
 * \param T ��� ����������
 * \return ����� � Q-������e

    �������� �� ������������ �� ������������.
 */
#define QVALUE(val, n, T) ROUND(double(val) * (1U << (n)), T)

//---------------------------------------------------------------------------
// ������� ��������
//---------------------------------------------------------------------------

/*!
 * \brief ���������� ������� ����� ���� �� ��� ������.
 * \param num ����� ����
 */
#define M0(num) (~(1u << (num)))

/*!
 * \brief ���������� ��������� ����� ���� �� ��� ������.
 * \param num ����� ����
 */
#define M1(num) (1u << (num))

/*!
 * \brief ����� �������� ����.
 * \param len ����� ����
 * \param shift ����� ���� �������������� �������� ���� (LSB) ������
 * \param type ��� ������ ������
 */
#define BITFIELD(len, shift, type) (((((type)1) << (len)) - 1) << (shift))

/*!
 * \brief ����� �������� ����.
 * \param len ����� ����
 * \param shift ����� ���� �������������� �������� ���� (LSB) ������
 */
#define BITFIELD32(len, shift) (((1UL << (len)) - 1) << (shift))

/*!
 * \brief ����� �������� ����.
 * \param msb_num ����� �������� ("������") ���� ����
 * \param lsb_num ����� �������� ("�������") ���� ����
 * \attention ������� �������� ���������� �� ������������.
 */
#define BITFRAME(msb_num, lsb_num, type) \
    BITFIELD(_ABS((msb_num) - (lsb_num)) + 1, _MIN(msb_num, lsb_num), type)

/*!
 * \brief ��������� ����� ������ �� �����.
 * \param cell ������
 * \param mask ������� �����
 */
#define SET_BIT(cell, mask) (cell) |= (mask)

/*!
 * \brief ����� ����� ������ �� �����.
 * \param cell ������
 * \param mask ������� �����
 */
#define CLR_BIT(cell, mask) (cell) &= ~(mask)

/*!
 * \brief �������� ����� ������ �� �����.
 * \param cell ������
 * \param mask ������� �����
 */
#define CMPL_BIT(cell, mask) (cell) ^= (mask)

/*!
 * \brief ��������� �������� �������� ���� ������.
 * \param cell ������
 * \param value �������� ��� ������ � ����
 * \param len ����� ����
 * \param pos ������� ����
 * \param type ��� ������
 */
#define SET_FIELD(cell, value, len, pos, type) \
    (cell) = (cell) & ~BITFIELD(len, pos, type) | ((value) << (pos))

#endif  // GPDEFS_H
