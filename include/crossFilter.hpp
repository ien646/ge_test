#pragma once

#include "column.hpp"
#include "csvReader.hpp"
#include "traits.hpp"

#include <any>
#include <type_traits>
#include <unordered_map>

struct filter
{
    virtual bool passesFilter(std::any val) = 0;
};

template<typename T>
struct crossFilterRange : filter
{
    static_assert(std::is_default_constructible_v<T>, "crossFilterRange type must be default constructible!");
    static_assert(
        isRangeComparable<T>() || std::is_arithmetic_v<T>, 
        "crossFilterRange type must be an arithmetic type or implement operators '<','>='"
    );

    T first, last;

    crossFilterRange(T vfirst, T vlast)
        : first(vfirst)
        , last(vlast)
    { }

    crossFilterRange(const crossFilterRange& cpSrc)
        : first(cpSrc.first)
        , last(cpSrc.last)
    { }

    virtual bool passesFilter(std::any val) override
    {
        T castedVal;
        try
        {
            castedVal = std::any_cast<T>(val);
        }
        catch(const std::bad_any_cast& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        
        return castedVal >= first && castedVal < last;
    }
};

struct filterInstance
{
    std::vector<size_t> targetColumns;
    std::unique_ptr<filter> filter;
};

class crossFilter
{
private:
    std::vector<filterInstance> _filters;

public:
    void addFilter(filterInstance&&);

    std::vector<size_t> getFilteredRows(const std::vector<csvColumn>& cols);
};