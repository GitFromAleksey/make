/*!
 * \file
 * General Purpose DEFinitionS - набор определений общего назначения.
 */

#if !defined(GPDEFS_H)
#   define GPDEFS_H


/*!
 * \brief Определение размера статического массива
 *        в атомарных единицах контроллера.
 * \param a указатель на массив
 */
#define SIZEOFARRAY(a) (sizeof(a) / sizeof(a[0]))

/*!
 * \brief Определение максимальной длины строки для статического буфера.
 * \param s указатель на буфер
 */
#define STRMAXLEN(s) (SIZEOFARRAY(s) - 1)

/*!
 * \brief Выделение элемента заданного типа из массива (многобайтового числа).
 * \param ptr адрес массива
 * \param i индекс элемента
 * \param type заданный тип
 * \return ссылка на элемент
 */
#define GET_REF(ptr, i, type) (((type *)(ptr))[i])

//---------------------------------------------------------------------------
// Математика
//---------------------------------------------------------------------------

/*!
 * \brief Максимальное из двух чисел.
 * \param x число 1
 * \param y число 2
 * \return max{x, y}
 */
#define _MAX(x, y) ((x) > (y) ? (x) : (y))

/*!
 * \brief Минимальное из двух чисел.
 * \param x число 1
 * \param y число 2
 * \return min{x, y}
 */
#define _MIN(x, y) ((x) < (y) ? (x) : (y))

/*!
 * \brief Mодуль числа.
 * \param x число
 * \return |x|
 */
#define _ABS(x) ((x) >= (0) ? (x) : (-(x)))

/*!
 * \brief Знак числа.
 * \param x число
 * \return sign(x)
 */
#define _SIGN(x) ((x) >= 0 ? 1 : -1)

/*!
 * \brief Анализ модуля числа на принадлежность заданному диапазону.
 * \param x исходное число
 * \param x_max максимальное значение
 * \return логическая единица, если модуль числа не превышает максимума
 */
#define BELOW(x, x_max) ((x) >= 0 ? (x) < (x_max) : -(x) < (x_max))

/*!
 * \brief Анализ модуля числа на выход из диапазона.
 * \param x исходное число
 * \param x_min минимальное значение
 * \return логическая единица, если модуль числа превышает минимума
 */
#define ABOVE(x, x_min) ((x) >= 0 ? (x) > (x_min) : -(x) > (x_min))

/*!
 * \brief Округление числа до ближайшего целого.
 * \param x число
 * \param type тип округленного числа
 * \return округленное число
 */
#define ROUND(x, type) ((type)((x) >= 0 ? (x) + 0.5 : (x) - 0.5))

/*!
 * \brief Округление числа до ближайшего по направлению к +inf целого.
 * \param x число
 * \param type тип округленного числа
 * \return округленное число
 */
#define ROUNDUP(x, type) \
    ((type)(((x) - (type)(x)) != 0 ? ((type)(x) + 1) : ((type)(x))))

/*!
 * \brief Округление числа до ближайшего по направлению к -inf целого.
 * \param x число
 * \param type тип округленного числа
 * \return округленное число
 */
#define ROUNDDOWN(x, type) \
    ((type)(((x) - (type)(x)) != 0 ? ((type)(x) - 1) : ((type)(x))))

/*!
 * \brief Перестановка содержимого двух ячеек.
 * \param cell1 ячейка 1
 * \param cell2 ячейка 2
 * \param temp вспомогательная ячейка
 */
#define XCHNG(cell1, cell2, temp) temp = cell1, cell1 = cell2, cell2 = temp

/*!
 * \brief Преобразование float в Q-формат.
 * \param val исходное значение с плавающей точкой
 * \param n Q-формат
 * \param T тип результата
 * \return число в Q-форматe

    Проверки на переполнение не производится.
 */
#define QVALUE(val, n, T) ROUND(double(val) * (1U << (n)), T)

//---------------------------------------------------------------------------
// Битовые операции
//---------------------------------------------------------------------------

/*!
 * \brief Вычисление нулевой маски бита по его номеру.
 * \param num номер бита
 */
#define M0(num) (~(1u << (num)))

/*!
 * \brief Вычисление единичной маски бита по его номеру.
 * \param num номер бита
 */
#define M1(num) (1u << (num))

/*!
 * \brief Маска битового поля.
 * \param len длина поля
 * \param shift сдвиг поля относительного младшего бита (LSB) ячейки
 * \param type тип данных ячейки
 */
#define BITFIELD(len, shift, type) (((((type)1) << (len)) - 1) << (shift))

/*!
 * \brief Маска битового поля.
 * \param len длина поля
 * \param shift сдвиг поля относительного младшего бита (LSB) ячейки
 */
#define BITFIELD32(len, shift) (((1UL << (len)) - 1) << (shift))

/*!
 * \brief Маска битового поля.
 * \param msb_num номер старшего ("левого") бита поля
 * \param lsb_num номер младшего ("правого") бита поля
 * \attention Порядок передачи аргументов не принципиален.
 */
#define BITFRAME(msb_num, lsb_num, type) \
    BITFIELD(_ABS((msb_num) - (lsb_num)) + 1, _MIN(msb_num, lsb_num), type)

/*!
 * \brief Установка битов ячейки по маске.
 * \param cell ячейка
 * \param mask битовая маска
 */
#define SET_BIT(cell, mask) (cell) |= (mask)

/*!
 * \brief Сброс битов ячейки по маске.
 * \param cell ячейка
 * \param mask битовая маска
 */
#define CLR_BIT(cell, mask) (cell) &= ~(mask)

/*!
 * \brief Инверсия битов ячейки по маске.
 * \param cell ячейка
 * \param mask битовая маска
 */
#define CMPL_BIT(cell, mask) (cell) ^= (mask)

/*!
 * \brief Установка значения битового поля ячейки.
 * \param cell ячейка
 * \param value значение для записи в поле
 * \param len длина поля
 * \param pos позиция поля
 * \param type тип ячейки
 */
#define SET_FIELD(cell, value, len, pos, type) \
    (cell) = (cell) & ~BITFIELD(len, pos, type) | ((value) << (pos))

#endif  // GPDEFS_H
