#include <csvReader.hpp>

#include <algorithm>
#include <charconv>

#include <stringUtils.hpp>

csvReader::csvReader(const std::string& filename)
    : _ifs(filename)
{ 
    if(!_ifs)
        throw std::invalid_argument("Unable to open csv file");
}

std::optional<std::string> csvReader::readNextLine()
{
    std::string result;
    // Skip empty or whitespace lines
    while(std::getline(_ifs, result))
    {
        if(!_ifs) 
            return std::nullopt;

        if(!strIsEmptyOrWhiteSpace(result))
            return result;
    }
    return std::nullopt;
}

std::vector<csvColumn> csvReader::readColumns(bool skipTitleRow)
{
    std::vector<csvColumn> result;

    if(skipTitleRow)
    {
        // Return empty result if there is not even a title row
        if(!readNextLine())
        {
            return result;
        }
    }

    // Get first row in order to define column types
    std::optional<std::string> first_line = readNextLine();
    if(!first_line)
    {
        // Return empty result if there is not even a single row
        return result;
    }

    // Parse types from first row
    auto segments = strSplit(*first_line, ',');
    for(auto& seg : segments)
    {
        auto val = strToNumeric<numericColumn::valueType>(seg);
        if(val)
        {
            result.push_back(numericColumn());
            std::get<numericColumn>(result.back()).cells.push_back(*val);
        }
        /* else(...) Additional types */
    }

    // Process remaining rows
    while(auto row = readNextLine())
    {
        auto segments = strSplit(*row, ',');
        if(segments.size() != result.size()) { continue; } // ill-formed row
        for(size_t i = 0; i < result.size(); ++i)
        {
            auto& col = result[i];
            auto& segment = segments[i];
            if(std::holds_alternative<numericColumn>(col))
            {
                using valType = numericColumn::valueType;
                std::optional<valType> val = strToNumeric<valType>(segment);
                if(!val)
                {
                    // Found new column type, check new found type and replace
                    // the values with the new type.
                }
                std::get<numericColumn>(col).cells.push_back(*val);
            }
            /* else(std::holds_alternative<...>(col)) Additional types */
        }
    }

    return result;
}