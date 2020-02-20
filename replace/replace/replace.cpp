#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "replace.h"

struct Args
{
    std::string inputFilePath;
    std::string outputFilePath;
    std::string searchString;
    std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFilePath = argv[1];
    args.outputFilePath = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];
    return args;
}

std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{
    size_t pos = 0;
    std::string result;

    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        result.append(subject, pos, foundPos - pos);
        if (foundPos != std::string::npos)
        {
            result.append(replacementString);
            pos = foundPos + searchString.length();
        }
        else
        {
            break;
        }
    }
    return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output, const std::string searchString, const std::string replacementString)
{
    std::string line;
    while (std::getline(input, line))
    {
        output << ReplaceString(line, searchString, replacementString) << "\n";
    }
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
    input.open(args->inputFilePath);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args->inputFilePath << "' for reading\n";
        return 1;
    }

    std::ofstream output;
    output.open(args->outputFilePath);
    if (!output.is_open())
    {
        std::cout << "Failed to open '" << args->outputFilePath << "' for writing\n";
        return 1;
    }

    CopyFileWithReplace(input, output, args->searchString, args->replaceString);
    output.flush();

    return 0;
}