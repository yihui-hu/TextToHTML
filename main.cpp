// TextToHTML
// 28/04/22 Hu Yihui

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void front_boilerplate(string noteTitle, ostream &outputFile);
void back_boilerplate(ostream &outputFile);
void embed_link(ostream &outputFile);
void embed_image(ostream &outputFile);

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
    inputFile >> line;

    front_boilerplate(line, outputFile);

    while (getline(inputFile, line))
    {
        if (line == "")
            continue;
        else
        {
            outputFile << "            <p>" << endl;
            outputFile << "            ";

            istringstream iss(line);
            string wordInLine;

            while (iss >> wordInLine)
            {
                if (wordInLine == "<link>")
                    embed_link(outputFile);
                else if (wordInLine == "<image>")
                    embed_image(outputFile);
                else
                    outputFile << wordInLine << " ";
            }

            outputFile << endl
                       << "            </p>" << endl
                       << endl;
        }
    }

    back_boilerplate(outputFile);
}

void front_boilerplate(string noteTitle, ostream &outputFile)
{
    outputFile << "<!DOCTYPE html>" << endl;
    outputFile << "<html lang=\"en\" dir=\"ltr\">" << endl;
    outputFile << "    <head>" << endl;
    outputFile << "        <meta charset=\"utf-8\">" << endl;
    outputFile << "        <title>" << noteTitle << "</title>" << endl;
    outputFile << "        <meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">" << endl;
    outputFile << "        <link rel=\"stylesheet\" href=\"../../styles.css\">" << endl;
    outputFile << "    </head>" << endl;
    outputFile << "    <body>" << endl;
    outputFile << "        <div class=\"container\">" << endl;
    outputFile << "            <div class=\"header\">" << endl;
    outputFile << "                " << noteTitle << endl;
    outputFile << "            </div>" << endl
               << endl;
}

void back_boilerplate(ostream &outputFile)
{
    outputFile << "            <p></p>" << endl;
    outputFile << "            <a class = \"main\" href = \"../notes.html\">⚛&#xFE0E;return to notes</a>" << endl;
    outputFile << "            <a class = \"main\" href = \"../../index.html\">⁖ return to main</a>" << endl;
    outputFile << "        </div>" << endl;
    outputFile << "    </body>" << endl;
    outputFile << "</html>" << endl;
}

void embed_link(ostream &outputFile)
{
    outputFile << "<a class=\"inline\" href=\"REPLACE_LINK_HERE\" target=\"_blank\">REPLACE_LINK_NAME_HERE</a> ";
}

void embed_image(ostream &outputFile)
{
    outputFile << "<img class=\"normal\" src=\"REPLACE_IMAGE_LINK_HERE\" alt=\"REPLACE_IMAGE_ALT_DESC_HERE\">";
}
