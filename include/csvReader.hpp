#pragma once

#include <fstream>
#include <optional>
#include <string>
#include <variant>

#include "column.hpp"

using numericColumn = rangeFilterableColumn<double>;

using csvColumn = std::variant<
    numericColumn
    // Add additional supported column types here
>;

class csvReader
{
private:
    std::ifstream _ifs;

public:
    csvReader(const std::string& filename);
    std::vector<csvColumn> readColumns(bool skipTitleRow);

private:
    std::optional<std::string> readNextLine();
};