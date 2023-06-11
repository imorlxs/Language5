/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */

#include "BigramCounter.h"
using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        showEnglishHelp(cout);
        exit(EXIT_FAILURE);
    }

    double min_distance;
    string min_id;
    BigramCounter text;
    text.calculateFrequencies(argv[1]);
    Language lang_input = text.toLanguage();
    lang_input.sort();


    Language lang_model;
    lang_model.load(argv[2]);
    min_distance = lang_input.getDistance(lang_model);
    min_id = lang_model.getLanguageId();

    for (int i = 3; i < argc; i++) {
        lang_model.load(argv[i]);
        double distance = lang_input.getDistance(lang_model);
        if (distance < min_distance) {
            min_distance = distance;
            min_id = lang_model.getLanguageId();
        }
    }

    cout << "Final decision: language " << min_id << " with a distance of " << min_distance << endl;
    return EXIT_SUCCESS;

}
