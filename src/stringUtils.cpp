#include <stringUtils.hpp>

#include <algorithm>
#include <charconv>

std::vector<std::string> strSplit(const std::string& str, char delim)
{
    std::vector<std::string> result;

    std::string::const_iterator currentIt = str.cbegin();
    for(;;)
    {
        std::string::const_iterator foundIt = std::find(currentIt, str.end(), delim);
        if(foundIt == str.end()) 
        { 
            break;
        }
        else
        {
            if(currentIt != foundIt)
            {
                result.push_back(std::string(currentIt, foundIt));
            }
            currentIt = ++foundIt;
        }
    }
    if(currentIt != str.end())
    {
        result.push_back(std::string(currentIt, str.end()));
    }

    return result;
}

bool strIsEmptyOrWhiteSpace(std::string_view str)
{
    if(str.size() == 0) { return true; }
    auto it = std::find_if(str.begin(), str.end(), [](char ch) { return ch != ' '; });
    return it == str.end();
}