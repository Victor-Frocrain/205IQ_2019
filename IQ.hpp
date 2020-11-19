/*
** EPITECH PROJECT, 2020
** IQ
** File description:
** IQ.hpp
*/

#include <vector>

#ifndef IQ_HPP_
#define IQ_HPP_

#define MY_ERROR 84
#define MY_SUCCESS 0

int iq(int ac, char **args);

class Datas {
    public:
    int u;
    int s;
    int IQ1;
    int IQ2;
    std::vector<double> list;
};

#endif /* IQ_HPP_ */
