/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/**
 * @file JOIN.cpp
 * @author Francisco Javier Cáceres Martín <javicaceres@correo.ugr.es>
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */

#include "Language.h"
#include <iostream>
using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc)
 */
void showEnglishHelp(ostream& outputStream)
{
    outputStream << "Error, run with the following Parameters:" << endl;
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the
 * input Language objects. The result is then sorted by decreasing order of
 * frequency and alphabetical order of bigrams when there is any tie in
 * frequencies. Finally, the resulting Language is saved in an output file. The
 * program must have at least an output file.
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char* argv[])
{
    int firstParameter = 1;
    bool isTextMode = true;
    char* outputFile = "outputFile.bgr";

    // Filtro de parametros
    if (argc < 2) {
        showEnglishHelp(cout);
        exit(1);
    } else {
        string s = argv[1];
        if (s[0] == '-') {
            if (s == "-t") {
                s = argv[2];
                if (s[0] == '-') {
                    if (s == "-o") {
                        firstParameter = 4;
                        outputFile = argv[3];
                    } else {
                        showEnglishHelp(cout);
                        exit(1);
                    }
                }
            }
            if (s == "-b") {
                s = argv[2];
                if (s[0] == '-') {
                    if (s == "-o") {
                        firstParameter = 4;
                        outputFile = argv[3];
                    } else {
                        showEnglishHelp(cout);
                        exit(1);
                    }
                }
                isTextMode = false;
            }
            if (s == "-o") {
                firstParameter = 3;
                outputFile = argv[2];
            } else {
                showEnglishHelp(cout);
                exit(1);
            }
        }
    }

    Language output;
    Language buffer;
    output.load(argv[firstParameter]);
    if (argc > firstParameter) {
        firstParameter++;
        for (int i = firstParameter; i < argc - firstParameter; i++) {
            buffer.load(argv[i]);
            output.join(buffer);
        }
    }
    output.sort();
    output.save(outputFile);
}
