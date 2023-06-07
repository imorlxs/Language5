///*
// * Metodología de la Programación: Language5
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

#include"BigramCounter.h";
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
    bool binary = false;
    bool args = true;
    std::string s = argv[1];
    std::string id = "unknown";
    char FileName[] = "output.bgr";
    if (s[0] == '-'){
        if ( s == "-t"){
            binary = false;
        }
        else if (s == "-b"){
            binary = true;
        }
        else if ( s == "-l"){
            id = argv[2];
        }
        else if ( s == "-o"){
            FileName = argv[2];
        }
        else{
            showEnglishHelp(cout);
        }
    }
    else {
        args = false;
    }
    if (args){
        s = argv[2];
        if (s[0] == "-"){
            if ( s == "-l"){
                id = argv[3];
            }
            else if (s == "-o"){
                FileName = argv[3];
            }
            else{
                showEnglishHelp(cout);
            }
        }
        else{
            args = false;
        }
    }
    
    if (args){
        s = argv[3];
        if (s[0] == "-"){
            if ( s == "-o"){
                FileName = argv[4];
            }
            else{
                showEnglishHelp(cout);
            }
        }
        else{
            args = false;
        }
    }
    
    if (args){
        s = argv[4];
    }
    
    BigramCounter* texts;
    texts = new BigramCounter[argc -1];
    
    texts[0].calculateFrequencies(s);
    
    if (!binary){
        texts[0].toLanguage();
        texts[0].toLanguage().setLanguageId(id);
        texts[0].toLanguage().load(FileName);
    }
}

