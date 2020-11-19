/*
** EPITECH PROJECT, 2020
** IQ
** File description:
** IQ.cpp
*/

#include "IQ.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <time.h>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

int parseFourthArg(char **args, Datas &datas)
{
    std::string s1(args[3]);

    for (size_t i = 0; i < s1.length(); i++) {
        if (s1[i] < '0' || s1[i] > '9')
            return MY_ERROR;
    }
    datas.IQ1 = std::stoi(s1);
    if (datas.IQ1 < 0 || datas.IQ1 > 200)
        return MY_ERROR;
    return MY_SUCCESS;
}

int parseFifthArgs(char **args, Datas &datas)
{
    std::string s2(args[4]);

    for (size_t i = 0; i < s2.length(); i++) {
        if (s2[i] < '0' || s2[i] > '9')
            return MY_ERROR;
    }
    datas.IQ2 = std::stoi(s2);
    if (datas.IQ2 < 0 || datas.IQ2 > 200)
        return MY_ERROR;
    if (datas.IQ2 < datas.IQ1)
        return MY_ERROR;
    return MY_SUCCESS;
}

int parseArgs(char **args, Datas &datas)
{
    std::string s1(args[1]);
    std::string s2(args[2]);

    for (size_t i = 0; i < s1.length(); i++) {
        if (s1[i] < '0' || s1[i] > '9')
            return MY_ERROR;
    }
    for (size_t i = 0; i < s2.length(); i++) {
        if (s2[i] < '0' || s2[i] > '9')
            return MY_ERROR;
    }
    datas.u = std::stoi(s1);
    datas.s = std::stoi(s2);
    if (datas.u < 0 || datas.u > 200)
        return MY_ERROR;
    if (datas.s <= 0 || datas.s > 200)
        return MY_ERROR;
    return MY_SUCCESS;
}

void density(Datas &datas)
{
    double result = 0.0;
    for (int i = 0; i <= 200; i++) {
        result = (1 / (float(datas.s) * sqrt(2 * M_PI))) * exp(-0.5 * pow((float(i) - float(datas.u)) / float(datas.s), 2));
        datas.list.push_back(result);
    }
}

int display(Datas &datas)
{
    std::cout << std::fixed << std::setprecision(5);
    for (size_t i = 0; i < datas.list.size() && i <= 200; i++) {
        if (datas.list[i] < 0)
            return MY_ERROR;
        std::cout << i << " " << datas.list[i] << std::endl;
    }
    return MY_SUCCESS;
}

double computeN(Datas &datas, const double &i)
{
    return (1 / (float(datas.s) * sqrt(2 * M_PI))) * exp(-0.5 * pow((float(i) - float(datas.u)) / float(datas.s), 2));
}

int inferior(Datas &datas)
{
    double n = 0;
    for (double i = 0; i < datas.IQ1; i += 0.01) {
        n += computeN(datas, i);
    }
    std::cout << std::fixed << std::setprecision(1) << n << "% of people have an IQ inferior to " << datas.IQ1 << std::endl;
    return MY_SUCCESS;
}

int between(Datas &datas)
{
    double n = 0;
    for (double i = datas.IQ1; i < datas.IQ2; i+= 0.01) {
        n += computeN(datas, i);
    }
    std::cout << std::fixed << std::setprecision(1) << n << "% of people have an IQ between " << datas.IQ1 << " and " << datas.IQ2 << std::endl;
    return MY_SUCCESS;
}

int iq(int ac, char **args)
{
    int result = MY_SUCCESS;
    Datas datas;

    if (ac == 2) {
        std::string arg(args[1]);
        if (arg == "-h")
            dispHelp();
        else
            return MY_ERROR;
    }
    else if (ac >= 3 && ac <= 5) {
        if (parseArgs(args, datas) == MY_ERROR)
            return MY_ERROR;
        if (ac == 3) {
            density(datas);
            return display(datas);
        }
        else if (ac == 4 && parseFourthArg(args, datas) == MY_SUCCESS) {
            return inferior(datas);
        }
        else if (ac == 5 && parseFourthArg(args, datas) == MY_SUCCESS && parseFifthArgs(args, datas) == MY_SUCCESS) {
            return between(datas);
        }
        else {
            return MY_ERROR;
        }
    }
    else
        result = MY_ERROR;
    return result;
}