/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 11:00
 */

#include "BigramCounter.h"
#include <fstream>

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */

//javi
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

//isaac

BigramCounter::BigramCounter(std::string validChars) {

}
//javi

BigramCounter::BigramCounter(const BigramCounter& orig) {
    *this = orig;
}
//isaac

~BigramCounter() {

}
//javi

int BigramCounter::getSize() const {
    return _validCharacters.size();
}
//isaac

int BigramCounter::getNumberActiveBigrams() const {

}
//J

bool BigramCounter::setFrequency(const Bigram& bigram, int frequency) {
    bool founded = false;
    int n;
    n = this->toLanguage().findBigram(bigram);
    if (n == -1) {
        founded = false;
    } else {
        founded = true;
        this->toLanguage().at(n) = frequency;
    }
    return founded;
}
//I

void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency = 0) {

}

//J

BigramCounter& BigramCounter::operator=(const BigramCounter& orig) {
    this->~BigramCounter();
    *_frequency = new int[orig.getSize()];
    _frequency = new int[orig.getSize()];
    int k = 0;
    for (int i = 0; i < orig.getSize(); i++) {
        for (int j = 0; j < orig.getSize(); j++) {
            _frequency[i][j] = orig.toLanguage.at(k);
            k++;
        }
    }

    return *this;

}
//I

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs) {

}
//J

void BigramCounter::calculateFrequencies(char* fileName) {
    ifstream fin;
    std::string text;
    fin.open(fileName);
    if (fin) {
        fin >> text;
        if (!fin) {
            throw std::ios_base::failure(string("error de lectura del fichero\n"))
        }
        fin.close();
    } else {
        throw std::ios_base::failure(string("error de apertura del fichero\n"))
    }

    Bigram *bigrams;
    bigrams = new Bigram[text.size()];
    BigramFreq *bigramfreq;
    bigramfreq = new BigramFreq[text.size()];
    Language l1;
    p = 0;
    for (int i = 0; i < text.size(); i++) {
        bigrams[p].at(0) = text[i];
        bigrams[p].at(1) = text[i + 1];
        bigramfreq[p].setBigram(bigrams[p]);
        bigramfreq[p].setFrequency(1);
        l1.append(bigramfreq[p]);
        p++;
    }
    l1.sort();
    l1.save(fileName);

}
//I

Language BigramCounter::toLanguage() const {

}
//J

int BigramCounter::operator()(int row, int column) const {
    return _frequency[row][column];
}
//I

int BigramCounter::operator()(int row, int column) {
    return _frequency[row][column];
}

void BigramCounter::allocate(int rows, int columns) {
    _rows = rows;
    _columns = columns;
    _frequency = new int*[_rows];
    for (int i = 0; i < _rows; i++) {
        _frequency[i] = new int [_columns];
    }
}

void BigramCounter::deallocate() {
    for (int i = 0; i < _rows; i++) {
        delete[] _frequency[i];
    }
    delete[] _frequency;
}

