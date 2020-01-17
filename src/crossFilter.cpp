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

    for(size_t colIdx = 0; colIdx < cols.size(); ++colIdx)
    {
        if(std::holds_alternative<numericColumn>(cols[colIdx]))
        {
            auto col = std::get<numericColumn>(cols[colIdx]);
            totalCols = col.size();
            for(auto& filterInst : _filters)
            {
                if(std::count(filterInst.targetColumns.begin(), filterInst.targetColumns.end(), colIdx))
                {
                    for(size_t cellIdx = 0; cellIdx < col.cells.size(); ++cellIdx)
                    {
                        if(failedIndexes.count(cellIdx)) { continue; }
                        if(!filterInst.filter->passesFilter(col.cells[cellIdx]))
                        {
                            failedIndexes.emplace(cellIdx);
                        }
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