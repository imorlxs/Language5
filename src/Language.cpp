/*
 * Metodología de la Programación: Language4
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 */
#include "Language.h"
#include <fstream>

using namespace std;

const string Language::MAGIC_STRING_T = "MP-LANGUAGE-T-1.0";

Language::Language() {
    _size = 0;
    _languageId = "unknown";
    _vectorBigramFreq = allocate(0);
}

Language::Language(int numberBigrams) {
    if (numberBigrams >= 0) {
        _size = numberBigrams;
        _vectorBigramFreq = allocate(numberBigrams);
        _languageId = "unknown";
    } else {
        throw std::out_of_range(string("Language::Language(int numberBigrams) ")
                + "invalid number " + to_string(numberBigrams));
    }
}

Language::Language(const Language& orig) {
    this->copyFrom(orig);

}

Language::~Language() {
    delete[] _vectorBigramFreq;
}

Language& Language::operator=(const Language& orig) {
    if (this != &orig) {
        delete[] _vectorBigramFreq;
        this->copyFrom(orig);
    }

    return *this;
}

const std::string& Language::getLanguageId() const {
    return _languageId;
}

void Language::setLanguageId(const std::string &id) {
    _languageId = id;
}

const BigramFreq& Language::at(int index) const {
    if (index < _size && index >= 0) {
        return _vectorBigramFreq[index];
    } else {
        throw std::out_of_range(std::string("Language::at(int index) const ")
                + "invalid position " + std::to_string(index));
    }
}

BigramFreq& Language::at(int index) {
    if (index < _size && index >= 0) {
        return _vectorBigramFreq[index];
    } else {
        throw std::out_of_range(std::string("Language::at(int index) ")
                + "invalid position " + std::to_string(index));
    }
}

int Language::getSize() const {
    return _size;
}

double Language::getDistance(const Language &otherLanguage) const {
    double distance = 0;
    double rankL2;

    for (int i = 0; i < _size; i++) {
        rankL2 = otherLanguage.findBigram(at(i).getBigram());

        if (rankL2 < 0)
            rankL2 = _size;

        distance = distance + ((abs(i - rankL2)) / (double) (_size * _size));

    }
    return distance;
}

int Language::findBigram(const Bigram &bigram) const {
    for (int i = 0; i < _size; i++) {
        if (_vectorBigramFreq[i].getBigram().getText() == bigram.getText()) {
            return i;
        }
    }
    return -1;
}

std::string Language::toString() const {
    std::string text = to_string(_size);
    text += '\n';
    for (int i = 0; i < _size; i++) {
        text += _vectorBigramFreq[i].toString();
        text += '\n';
    }
    return text;
}

void Language::sort() {
    for (int i = 0; i < _size; i++) {
        for (int j = _size - 1; j > i; j--) {
            if (_vectorBigramFreq[j].getFrequency() > _vectorBigramFreq[j - 1].getFrequency()) {
                this->swap(j, j - 1);
            } else if (_vectorBigramFreq[j].getFrequency() == _vectorBigramFreq[j - 1].getFrequency()) {
                if (_vectorBigramFreq[j].getBigram().at(0) < _vectorBigramFreq[j - 1].getBigram().at(0)) {
                    this->swap(j, j - 1);
                } else if (_vectorBigramFreq[j].getBigram().at(0) == _vectorBigramFreq[j - 1].getBigram().at(0)) {
                    if (_vectorBigramFreq[j].getBigram().at(1) < _vectorBigramFreq[j - 1].getBigram().at(1)) {
                        this->swap(j, j - 1);
                    }
                }
            }
        }
    }
}

void Language::save(const char fileName[]) const {
    ofstream fout;
    fout.open(fileName);
    if (fout) {
        fout << MAGIC_STRING_T << endl;
        fout << _languageId << endl;
        fout << this->toString();
        if (!fout) {
            throw std::ios_base::failure(string("error_de_escritura_del_fichero\n"));
        }
        fout.close();
    } else {
        throw std::ios_base::failure(string("error_de_apertura_del_fichero\n"));
    }
}

void Language::load(const char fileName[]) {
    ifstream fin;
    string magic_string;
    int frequency;
    string text;
    fin.open(fileName);
    if (fin) {
        fin >> magic_string;
        
        if (magic_string != MAGIC_STRING_T) {
            throw std::invalid_argument(string("The magic word isn't correct\n"));
        }
        
        fin >> _languageId;
        this->setLanguageId(_languageId);
        
        fin >> _size;
        
        delete[] _vectorBigramFreq;
        _vectorBigramFreq = allocate(_size);
        
        for (int i = 0; i < _size; i++) {
            fin >> text;
            fin >> frequency;
            Bigram bigram(text);
            _vectorBigramFreq[i].setBigram(bigram);
            _vectorBigramFreq[i].setFrequency(frequency);
        }


        if (!fin) {
            throw std::ios_base::failure(string("error_de_lectura_del_fichero\n"));
        }
        fin.close();
        
    } else {
        throw std::ios_base::failure(string("error_de_apertura_del_fichero\n"));
    }
}

void Language::append(const BigramFreq &bigramFreq) {
    Bigram bigram = bigramFreq.getBigram();
    int index = this->findBigram(bigram);
    int freq = bigramFreq.getFrequency();
    if (index >= 0) {
        _vectorBigramFreq[index].setFrequency(freq + _vectorBigramFreq[index].getFrequency());
    } else {
        increase(_vectorBigramFreq, _size, 1);
        _vectorBigramFreq[_size - 1].setBigram(bigram);
        _vectorBigramFreq[_size - 1].setFrequency(freq);

    }
}

void Language::join(const Language &language) {
    for (int i = 0; i < language.getSize(); i++) {
        this->append(language.at(i));
    }
}

void Language::swap(int first, int second) {
    BigramFreq aux;
    aux = _vectorBigramFreq[second];
    _vectorBigramFreq[second] = _vectorBigramFreq[first];
    _vectorBigramFreq[first] = aux;
}

BigramFreq* Language::allocate(int n) {
    if (n > 0) {
        BigramFreq *v;
        v = new BigramFreq [n];
        return v;
    } else if (n == 0) {
        BigramFreq *v = nullptr;
        return v;
    } else {
        throw std::out_of_range(string("Language::allocate(int n) ")
                + "invalid value " + std::to_string(n));
    }

}

void Language::copyFrom(const Language &orig) {
    _size = orig.getSize();
    _vectorBigramFreq = allocate(_size);
    _languageId = orig.getLanguageId();

    for (int i = 0; i < _size; i++) {
        _vectorBigramFreq[i] = orig.at(i);
    }
}

void Language::increase(BigramFreq* &vector1, int &nElements, int increment) {
    nElements += increment;
    BigramFreq* vector2 = new BigramFreq[increment];
    for (int i = 0; i < nElements; i++) {
        vector2[i] = vector1[i];
    }
    delete[] vector1;
    vector1 = vector2;
}