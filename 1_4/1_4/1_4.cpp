#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "1_4.h"

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::string search;
    std::string replace;
};


std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: CopyFile.exe <input file name> <output file name>\n";
        return 1;
    }

    std::ifstream input;
    input.open(args->inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }

    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }
}