///*
// * Metodología de la Programaci�n: Language5
// * Curso 2022/2023
// */
//
///** 
// * @file LEARN.cpp
// * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
// * @author Andrés Cano Utrera <acu@decsai.ugr.es>
// * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
// * 
// * Created on 29 January 2023, 11:00
// */
// LO HACE JAVI
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */

#include"BigramCounter.h"

using namespace std;

void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) {   
    
    if (argc < 2){
        showEnglishHelp(cout);
        exit(1);
    }
    char mode = 't';
    int param;
    std::string s;
    std::string id = "unknown";
    char const* FileName = "output.bgr";
    for (int i = 1; i < argc; i++) {
        s = argv[i];
        if (s[0] == '-') {
            if (s == "-t") {
                mode = 't';
            } else if (s == "-b") {
                mode = 'b';
            } else if (s == "-o") {
                FileName = argv[i + 1];
                i++;
            } else if (s == "-l") {
                id = argv[i+1];
                i++;
            }else {
                showEnglishHelp(cout);
                exit(1);
            }
        } else {
            param = i;
            break;
        }

    }
    
  
    BigramCounter texts;
    Language l;
    for (int i = param; i < argc; i++){
        texts.calculateFrequencies(argv[i]);
    }
    l = texts.toLanguage();
    l.setLanguageId(id);
    l.sort();
    l.save(FileName,mode);
}

