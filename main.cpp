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
void notes_page_table_template(ostream &outputFile);

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

    // add starter boilerplate
    front_boilerplate(line, outputFile);

    // each line is considered a block in the plain text
    while (getline(inputFile, line))
    {
        // if empty, ignore
        if (line == "")
            continue;
        else
        {
            // encapsulate the block in <p> and </p>
            outputFile << "            <p>" << endl
                       << "            ";

            // process each word in the block
            istringstream iss(line);
            string wordInLine;

            while (iss >> wordInLine)
            {
                // flag to create template for links
                if (wordInLine == "<link>")
                    embed_link(outputFile);
                // flag to create template for images
                else if (wordInLine == "<image>")
                    embed_image(outputFile);
                // process word as usual
                else
                    outputFile << wordInLine << " ";
            }

            outputFile << endl
                       << "            </p>" << endl
                       << endl;
        }
    }

    // add remaining boilerplate
    back_boilerplate(outputFile);
    notes_page_table_template(outputFile);
}

void front_boilerplate(string noteTitle, ostream &outputFile)
{
    outputFile << "<!DOCTYPE html>" << endl
               << "<html class=\"normal\" lang=\"en\" dir=\"ltr\">" << endl
               << "    <head>" << endl
               << "        <meta charset=\"utf-8\">" << endl
               << "        <title>" << noteTitle << "</title>" << endl
               << "        <meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">" << endl
               << "        <link rel=\"stylesheet\" href=\"../../styles.css\">" << endl
               << "    </head>" << endl
               << "    <body>" << endl
               << "        <div class=\"container\">" << endl
               << "            <div class=\"header\">" << endl
               << "                " << noteTitle << endl
               << "            </div>" << endl
               << endl;
}

void back_boilerplate(ostream &outputFile)
{
    outputFile << "            <p></p>" << endl
               << "            <a class = \"main\" href = \"../notes.html\">⚛&#xFE0E;return to notes</a>" << endl
               << "            <a class = \"main\" href = \"../../index.html\">⁖ return to main</a>" << endl
               << "        </div>" << endl
               << "    </body>" << endl
               << "</html>" << endl;
}

void embed_link(ostream &outputFile)
{
    outputFile << "<a class=\"inline\" href=\"REPLACE_LINK_HERE\" target=\"_blank\">REPLACE_LINK_NAME_HERE</a> ";
}

void embed_image(ostream &outputFile)
{
    outputFile << "<img class=\"normal\" src=\"REPLACE_IMAGE_LINK_HERE\" alt=\"REPLACE_IMAGE_ALT_DESC_HERE\">";
}

void notes_page_table_template(ostream &outputFile)
{
    outputFile << endl
               << "<tr>" << endl
               << "    <td>REPLACE_DATE_HERE</td>" << endl
               << "    <td><a class=\"inline\" href=\"../pages/notes/REPLACE_NOTES_LINK_HERE\">REPLACE_NOTES_NAME_HERE</a></td>" << endl
               << "</tr>" << endl;
}
