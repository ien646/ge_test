#include <csvReader.hpp>
#include <crossFilter.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Not enough arguments!" << std::endl;
        return -1;
    }

    std::string path(argv[1]);
    csvReader csv(path);
    auto cols = csv.readColumns(true);

    crossFilter cross;

    filterInstance filter0;
    filter0.targetColumns = { 3 };
    filter0.filter = std::make_unique<crossFilterRange<double>>(1000, 2000);

    cross.addFilter(std::move(filter0));

    auto filteredCols = cross.getFilteredRows(cols);

    for(auto& idx : filteredCols)
    {
        std::cout << idx << std::endl;
    }

    return 0;
}