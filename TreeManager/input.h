#pragma once
#include <iostream>
#include <string>
#include "FileLogging.h"

inline bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}

int Input(std::string message, int min, int max, FileLogging& fl)
{
    int number = 0;
    bool correct = false;
    while (!correct)
    {
        std::cout << message;
        std::string input = "";
        std::cin >> input;
        correct = (input[0] == '-' || isDigit(input[0]));
        for (size_t i = 1; i < input.size(); i++)
        {
            correct = isDigit(input[i]);
            if (!correct)
            {
                break;
            }
        }
        if (!correct)
        {
            std::cout << "Некорректная запись числа!\n";
            fl.Logging("Incorrect number entry\n");
        }
        if (correct && input.size() > std::to_string(INT_MAX).size() - 1)
        {
            correct = false;
            std::cout << "Введённое число выходит из допустимого диапазона!\n";
            fl.Logging("The entered number out of range\n");
        }
        if (correct)
        {
            number = stoi(input);
            if (min > number || max < number)
            {
                correct = false;
                std::cout << "Введённое число выходит из допустимого диапазона!\n";
                fl.Logging("The entered number out of range\n");
            }
        }
    }
    return number;
}
