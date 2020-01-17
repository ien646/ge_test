#include <crossFilter.hpp>

#include <algorithm>
#include <unordered_set>

void crossFilter::addFilter(filterInstance&& inst)
{
    _filters.push_back(std::move(inst));
}

std::vector<size_t> crossFilter::getFilteredRows(const std::vector<csvColumn>& cols)
{
    std::unordered_set<size_t> result;
    for(auto& filterInstance : _filters)
    {
        for(auto& targetCol : filterInstance.targetColumns)
        {
            if(std::holds_alternative<numericColumn>(cols[targetCol]))
            {
                auto& column = std::get<numericColumn>(cols[targetCol]);
                for(size_t i = 0; i < column.cells.size(); ++i)
                {
                    if(filterInstance.filter->passesFilter(column.cells[i]))
                    {
                        result.emplace(i);
                    }
                    else
                    {
                        result.erase(i);
                    }
                }
            }
        }
    }
    
    std::vector<size_t> vecResult;
    vecResult.reserve(result.size());

    std::copy(result.begin(), result.end(), std::back_inserter(vecResult));
    std::sort(vecResult.begin(), vecResult.end());
    return vecResult;
}