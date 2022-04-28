// TextToHTML
// 28/04/22 Hu Yihui

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: ./TextToHTML plainTextFile htmlOutputFile" << endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    std::ofstream outputFile;
    outputFile.open(argv[2]);

    string line;

    while (getline(inputFile, line))
    {
        if (line == "")
            continue;
        else
        {
            outputFile << "<p>" << endl;
            outputFile << line << endl;
            outputFile << "</p>" << endl
                       << endl;
        }
    }
}
