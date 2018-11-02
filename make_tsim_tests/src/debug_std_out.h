/*
 * debug_std_out.h
 *
 *  Created on: 18 окт. 2018 г.
 *      Author: user1
 */

#ifndef SRC_DEBUG_STD_OUT_H_
#define SRC_DEBUG_STD_OUT_H_

#include <iostream>
#include <string>
#include "types.h"

using namespace std;

void debugPrintText(const string text)
{
    cout << text << endl;
}

template <class T>
void debugPrintDecVal(const T &val)
{
    cout << val << endl;
}

template <class T>
void debugPrintHexVal(const T &val)
{
    cout << " " << std::hex << val << endl;
}

template <class T>
void debugPrintTextHexValue(const string text, const T &val)
{
    cout << text << " 0x"<< std::hex << val << endl;
}

template <class T>
void debugPrintTextDecValue(const string text, const T &val)
{
    cout << text << val << endl;
}

#endif /* SRC_DEBUG_STD_OUT_H_ */
