#include <crossFilter.hpp>

#include <algorithm>
#include <unordered_set>

void crossFilter::addFilter(filterInstance&& inst)
{
    _filters.push_back(std::move(inst));
}

std::vector<size_t> crossFilter::getFilteredRows(const std::vector<csvColumn>& cols)
{
    std::unordered_set<size_t> failedIndexes;
    size_t totalCols = 0;
    for(auto& filterInstance : _filters)
    {
        for(auto& targetCol : filterInstance.targetColumns)
        {
            if(std::holds_alternative<numericColumn>(cols[targetCol]))
            {
                auto& column = std::get<numericColumn>(cols[targetCol]);
                totalCols = column.cells.size();
                for(size_t i = 0; i < column.cells.size(); ++i)
                {
                    if(!filterInstance.filter->passesFilter(column.cells[i]))
                    {
                        failedIndexes.emplace(i);
                    }
                }
            }
        }
    }
    
    std::vector<size_t> vecResult;
    for(size_t i = 0; i < totalCols; ++i)
    {
        if(!failedIndexes.count(i))
        {
            vecResult.push_back(i);
        }
    }
    return vecResult;
}