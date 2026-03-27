#include "isogram.h"
#include <locale>
#include <string>
#include <stdio.h>
#include <iostream>
#include <unordered_set>


bool is_isogram(std::string const& word)
{
    // Функция is_isogram получает на вход строку word
    // Возвращает true, если строка является изограммой,
    // и false, если не явялется
    // Код пишите здесь
    std::unordered_set<char> word_set;  
    for (char i : word)
    {
        if (std::isalpha(i))
        {
            if (word_set.count(std::toupper(i)) > 0)
                return false;
            word_set.insert(std::toupper(i));
        }
    }
    return true;
}