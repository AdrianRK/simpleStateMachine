/*
 * logger.hpp
 *
 *  Created on: Apr 4, 2017
 *      Author: devteam
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>

template<typename T>
void print(std::ostream &out, const T &t)
{
	out << t << "\n";
}

template <typename T, typename ...arg>
void print(std::ostream &out, const T&t, const arg &...args)
{
	out << t;
	print(out, args...);
}

#define PRINT_INFO(arg...) print(std::cout, "INFO:|",__FUNCTION__,"|",__LINE__, "|:", arg);
#define PRINT_WARNING(arg...) print(std::cout, "WARNING:|",__FUNCTION__,"|",__LINE__, "|:", arg);
#define PRINT_ERROR(arg...) print(std::cerr, "ERROR:|",__FUNCTION__,"|",__LINE__, "|:", arg);


#endif /* LOGGER_HPP_ */
