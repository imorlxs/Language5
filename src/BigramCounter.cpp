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
using namespace std;

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars).
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */

// javi
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

// isaac

BigramCounter::BigramCounter(std::string validChars)
{
    _validCharacters = validChars;
    int size = _validCharacters.size();
    allocate(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            _frequency[i][j] = 0;
        }
    }
}
// javi
//  El constructor de copia no se puede hacer así porque se llama al destructor y no hay ningún
// objeto creado
BigramCounter::BigramCounter(const BigramCounter& orig)
{
    *this = orig;
}
// isaac

BigramCounter::~BigramCounter()
{
    deallocate();
}
// javi

int BigramCounter::getSize() const
{
    return _validCharacters.size();
}
// isaac

int BigramCounter::getNumberActiveBigrams() const
{
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
// J
//
bool BigramCounter::setFrequency(const Bigram& bigram, int frequency)
{
    bool founded = false;
    int n;
    n = this->findBigram(bigram); // Lo suyo sería buscar las dos letras en el string validchars y acceder a su posicion en la matriz
    if (n >= 0) {
        founded = true;
        this->findBigram(bigram) = frequency; // Hay que cambiarlo directamente en la matriz
    } else {
        founded = false;
    }
    return founded;
}
// I

void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency = 0)
{
    if (frequency == 0) {
        this->findBigram(bigram)++;
    } else {
        this->findBigram(bigram) += frequency;
    }
}

// J

BigramCounter& BigramCounter::operator=(const BigramCounter& orig)
{
    if (this != &orig) {
        this->~BigramCounter();
        allocate(orig.getSize());
        _validCharacters = orig.getValidCharacters();
        for (int i = 0; i < orig.getSize(); i++) {
            for (int j = 0; j < orig.getSize(); j++) {
                _frequency[i][j] = orig(i, j);
            }
        }
    }
    return *this;
}
// I

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs)
{
    for (int i = 0; i < _validCharacters.size(); i++) {
        int row = rhs._validCharacters.find(_validCharacters[i]);
        if(row < 0){
            continue;
        }
        for(int j = 0; j < _validCharacters.size(); j++){
            int col = rhs._validCharacters.find(_validCharacters[j]);

            if(col < 0){
                continue;
            }

            _frequency[i][j] += rhs._frequency[row][col];

        }
    }
    return *this;
}
// J

void BigramCounter::calculateFrequencies(char* fileName)
{
    ifstream fin;
    std::string text;
    fin.open(fileName);
    if (fin) {
        fin >> text;
        if (!fin) {
            throw std::ios_base::failure(string("error de lectura del fichero\n"));
        }
        fin.close();
    } else {
        throw std::ios_base::failure(string("error de apertura del fichero\n"));
    }

    Bigram* bigrams;
    bigrams = new Bigram[text.size()];
    BigramFreq* bigramfreq;
    bigramfreq = new BigramFreq[text.size()];
    // Hay que hacerlo directamente sobre la matriz 2D
    for (int i = 0; i < text.size(); i++) {
        bigrams[i].at(0) = text[i];
        bigrams[i].at(1) = text[i + 1];
        if (this->findBigram(bigrams[i]) >= 1) {
            findBigram(bigrams[i])++;
        } else {
            this->findBigram(bigrams[i]) = 1;
        }
    }
}
// I

Language BigramCounter::toLanguage() const{
    Language language(this->getNumberActiveBigrams());
    
}
// J

const int& BigramCounter::operator()(int row, int column) const
{
    return _frequency[row][column];
}
// I

int& BigramCounter::operator()(int row, int column)
{
    return _frequency[row][column];
}

void BigramCounter::allocate(int size)
{
    _frequency = new int*[size];
    for (int i = 0; i < size; i++) {
        _frequency[i] = new int[size];
    }
}

void BigramCounter::deallocate()
{
    for (int i = 0; i < this->getSize(); i++) {
        delete[] _frequency[i];
    }
    delete[] _frequency;
}

int& BigramCounter::findBigram(Bigram bigram)
{
    int row = _validCharacters.find(bigram[0]);
    int col = _validCharacters.find(bigram[1]);

    if (row >= 0 && col >= 0) {
        return _frequency[row][col];
    } else {
        throw std::out_of_range(string("int& BigramCounter::findBigram(Bigram bigram): ") + "invalid bigram " + bigram.getText());
    }
}

std::string BigramCounter::getValidCharacters() const
{
    return _validCharacters;
}
// COMO SABER SI UN BIGRAMA ES VALIDO
//_validCharacters.find(bigram[0]);
//_validCharacters.find(bigram[1]);
//  LOS DOS DEBEN SER MAYORES O IGUAL A 0
