#pragma once

#include <string>
#include <type_traits>
#include <vector>

#include "traits.hpp"

template<typename T>
struct column
{
    using valueType = T;

    std::vector<valueType> cells;
    size_t size()
    {
        return cells.size();
    }
};

template<typename T>
struct rangeFilterableColumn : column<T>
{
    static_assert(std::is_default_constructible_v<T>, "Column type must be default constructible!");
    static_assert(
        isRangeComparable<T>() || std::is_arithmetic_v<T>, 
        "Column type must be an arithmetic type or implement operators '<','>='"
    );    

    std::vector<size_t> getRangeFilteredIndexes(T firstIncl, T lastExcl)
    {
        std::vector<size_t> result;
        for(size_t i = 0; i < column<T>::cells.size(); ++i)
        {
            valueType& cell = column<T>::cells[i];
            if(cell >= firstIncl && cell < lastExcl)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};