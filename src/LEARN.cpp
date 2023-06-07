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
    int param = 1;
    std::string s = argv[1];
    std::string id = "unknown";
    char FileName[] = "output.bgr";
    if (s[0] == '-'){
        if ( s == "-t"){
            binary = false;
            param++;
            s = argv[param];
            if (s == "-l"){
                id = argv[3];
                param = 4;
                s = argv[param];
                if ( s == "-o"){
                    FileName = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
            else if ( s == "-o"){
                FileName = argv[3];
                param = 4;
                s = argv[param];
                if ( s == "-l"){
                    id = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
        }
        else if (s == "-b"){
            binary = true;
            param++;
            s = argv[param];
            if (s == "-l"){
                id = argv[3];
                param = 4;
                s = argv[param];
                if ( s == "-o"){
                    FileName = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
            else if ( s == "-o"){
                FileName = argv[3];
                param = 4;
                s = argv[param];
                if ( s == "-l"){
                    id = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
        }
        else if ( s == "-l"){
            id = argv[2];
            param = 3;
            s = argv[param];
            if ( s == "-t"){
                binary = false;
                param++;
                s = argv[param];
                if ( s == "-o"){
                    FileName = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
            else if ( s == "-b"){
                binary = true;
                param++;
                s = argv[param];
                if ( s == "-o"){
                    FileName = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
            else if ( s == "-o"){
                FileName = argv[4];
                param = 5;
                s = argv[param];
                if ( s == "-t"){
                    binary = false;
                    param++;
                    s = argv[param];
                }
                else if ( s == "-b"){
                    binary = true;
                    param++;
                    s = argv[param];
                }
            }
        }
        else if ( s == "-o"){
            FileName = argv[2];
            param = 3;
            s = argv[param];
            if ( s == "-t"){
                binary = false;
                param++;
                s = argv[param];
                if ( s == "-l"){
                    id = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
            else if ( s == "-b"){
                binary = true;
                param++;
                s = argv[param];
                if ( s == "-l"){
                    id = argv[5];
                    param = 6;
                    s = argv[param];
                }
            }
            else if ( s == "-l"){
                id = argv[4];
                param = 5;
                s = argv[param];
                if ( s == "-t"){
                    binary = false;
                    param++;
                    s = argv[param];
                }
                else if ( s == "-b"){
                    binary = true;
                    param++;
                    s = argv[param];
                }
            }
        }
        else{
            showEnglishHelp(cout);
        }
    }
    
    BigramCounter* texts;
    texts = new BigramCounter[argc - param];
    int conter = 0;
    for (int i = param; i < argc; i++){
        texts[conter].calculateFrequencies(s);
        texts[conter].toLanguage();
        texts[conter].toLanguage().setLanguageId(id);
        texts[conter].toLanguage().load(FileName);
        conter++;
    }
}

