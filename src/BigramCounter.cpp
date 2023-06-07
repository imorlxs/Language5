/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/**
 * @file BigramCounter.cpp
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */

#include "BigramCounter.h"
using namespace std;

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars).
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */

const char* const BigramCounter::DEFAULT_VALID_CHARACTERS = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(const std::string& validChars) {
    _validCharacters = validChars;
    int size = _validCharacters.size();
    allocate(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            _frequency[i][j] = 0;
        }
    }
}

BigramCounter::BigramCounter(const BigramCounter& orig) {
    this->copyFrom(orig);
}

BigramCounter::~BigramCounter() {
    deallocate();
}

int BigramCounter::getSize() const {
    return _validCharacters.size();
}

int BigramCounter::getNumberActiveBigrams() const {
    int size = this->getSize();
    int activeBigrams = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (_frequency[i][j] > 0) {
                activeBigrams++;
            }
        }
    }
    return activeBigrams;
}

bool BigramCounter::setFrequency(const Bigram& bigram, int frequency) {
    bool founded = false;
    if (_validCharacters.find(bigram[0]) < 0 || _validCharacters.find(bigram[1]) < 0) {
        founded = false;
    } else {
        founded = true;
        this->findBigram(bigram) = frequency;
    }
    return founded;
}

void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency) {
    if (frequency == 0) {
        this->findBigram(bigram)++;
    } else {
        this->findBigram(bigram) += frequency;
    }
}

BigramCounter& BigramCounter::operator=(const BigramCounter& orig) {
    if (this != &orig) {
        this->~BigramCounter();
        allocate(orig.getSize());
        _validCharacters = orig._validCharacters;
        for (int i = 0; i < orig.getSize(); i++) {
            for (int j = 0; j < orig.getSize(); j++) {
                _frequency[i][j] = orig(i, j);
            }
        }
    }
    return *this;
}

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs) {
    for (int i = 0; i < _validCharacters.size(); i++) {
        int row = rhs._validCharacters.find(_validCharacters[i]);
        if (row < 0) {
            continue;
        }
        for (int j = 0; j < _validCharacters.size(); j++) {
            int col = rhs._validCharacters.find(_validCharacters[j]);

            if (col < 0) {
                continue;
            }

            _frequency[i][j] += rhs(row, col);
        }
    }
    return *this;
}

void BigramCounter::calculateFrequencies(char* fileName) {
    ifstream fin;
    std::string text;
    fin.open(fileName);
    if (fin) {
        // Esto solo cogería la primera palabra, no? Utiliza while(fin >> text)
        while (fin >> text) {
            for (int i = 0; i < text.length() - 1; i++) {
                Bigram bigram(text[i], text[i + 1]);
                bigram.toLower();
                if (isValidCharacter(bigram[0], _validCharacters) && isValidCharacter(bigram[1], _validCharacters)) {
                    this->increaseFrequency(bigram);
                }
            }
        }
        //        if (!fin) {
        //            throw std::ios_base::failure(string("error de lectura del fichero\n"));
        //        }
        fin.close();
    } else {
        throw std::ios_base::failure(string("error de apertura del fichero\n"));
    }

}

Language BigramCounter::toLanguage() const {
    Language language(this->getNumberActiveBigrams());
    int size = this->getSize();
    int counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (_frequency[i][j] > 0) {
                Bigram bigram(_validCharacters[i], _validCharacters[j]);
                language[counter].setBigram(bigram);
                language[counter].setFrequency(_frequency[i][j]);
                counter++;
            }
        }
    }
    return language;
}

const int& BigramCounter::operator()(int row, int column) const {
    return _frequency[row][column];
}

int& BigramCounter::operator()(int row, int column) {
    return _frequency[row][column];
}

void BigramCounter::allocate(int size) {
    _frequency = new int*[size];
    for (int i = 0; i < size; i++) {
        _frequency[i] = new int[size];
    }
}

void BigramCounter::deallocate() {
    for (int i = 0; i < this->getSize(); i++) {
        delete[] _frequency[i];
    }
    delete[] _frequency;
}

int& BigramCounter::findBigram(Bigram bigram) {
    int row = _validCharacters.find(bigram[0]);
    int col = _validCharacters.find(bigram[1]);

    if (row >= 0 && col >= 0) {
        return _frequency[row][col];
    } else {
        throw std::invalid_argument(string("int& BigramCounter::findBigram(Bigram bigram): ") + "invalid bigram " + bigram.getText());
    }
}

void BigramCounter::copyFrom(const BigramCounter& orig) {
    allocate(orig.getSize());
    _validCharacters = orig._validCharacters;
    for (int i = 0; i < orig.getSize(); i++) {
        for (int j = 0; j < orig.getSize(); j++) {
            _frequency[i][j] = orig(i, j);
        }
    }
}

// COMO SABER SI UN BIGRAMA ES VALIDO
//_validCharacters.find(bigram[0]);
//_validCharacters.find(bigram[1]);
//  LOS DOS DEBEN SER MAYORES O IGUAL A 0
