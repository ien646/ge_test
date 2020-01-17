#pragma once

#include <charconv>
#include <optional>
#include <string>
#include <vector>

std::vector<std::string> strSplit(const std::string& str, char delim);
bool strIsEmptyOrWhiteSpace(std::string_view str);

template<typename T>
std::optional<T> strToNumeric(const std::string& str)
{
    static_assert(
        std::is_floating_point_v<T> || std::is_integral_v<T>,
        "Only integral or floating-point types are supported!"
    );

    char* end;
    auto cstr = str.c_str();
    long double val = strtold(cstr, &end);

    if(val == 0.0 && end == cstr)
    {
        return std::nullopt;
    }
    return static_cast<T>(val);
}