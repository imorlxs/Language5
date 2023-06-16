/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */
#include "Language.h"
#include <fstream>

using namespace std;

const string Language::MAGIC_STRING_T = "MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B = "MP-LANGUAGE-B-1.0";

Language::Language() {
    _size = 0;
    _languageId = "unknown";
    _vectorBigramFreq = nullptr;
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
    int max_idx;
    for (int i = 0; i < _size; i++) {
        max_idx = i;
        for (int j = i + 1; j < _size; j++) {
            if (_vectorBigramFreq[j] > _vectorBigramFreq[max_idx]) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            this->swap(i, max_idx);
        }
    }
}

void Language::save(const char fileName[], char mode) const {
    ofstream fout;
    fout.open(fileName);
    if (fout) {
        if (mode == 't') {
            fout << MAGIC_STRING_T << endl;
            fout << *this;
        }
        if (mode == 'b') {
            fout << MAGIC_STRING_B << endl;
            fout << _languageId << endl;
            fout << _size << endl;
            for (int i = 0; i < _size; i++) {
                _vectorBigramFreq[i].serialize(fout);
            }
        }

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
    fin.open(fileName);
    if (fin) {
        fin >> magic_string;

        if (magic_string == MAGIC_STRING_T) {
            fin >> *this;
            if (!fin) {
                throw std::ios_base::failure(string("error_de_lectura_del_fichero\n"));
            }

        } else if (magic_string == MAGIC_STRING_B) {
            fin >> _languageId;
            fin >> _size;
            fin.get();
            delete[] _vectorBigramFreq;
            _vectorBigramFreq = allocate(_size);
            for (int i = 0; i < _size; i++) {
                _vectorBigramFreq[i].deserialize(fin);
            }
        } else {
            throw std::invalid_argument(string("The magic word isn't correct load\n"));
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
        increase();
        _vectorBigramFreq[_size - 1].setBigram(bigram);
        _vectorBigramFreq[_size - 1].setFrequency(freq);

    }
}

void Language::swap(int first, int second) {
    BigramFreq aux;
    aux = _vectorBigramFreq[second];
    _vectorBigramFreq[second] = _vectorBigramFreq[first];
    _vectorBigramFreq[first] = aux;
}

BigramFreq& Language::operator[](int index) const {
    return _vectorBigramFreq[index];
}

BigramFreq& Language::operator[](int index) {
    return _vectorBigramFreq[index];
}

Language& Language::operator+=(const Language& language) {
    for (int i = 0; i < language.getSize(); i++) {
        this->append(language.at(i));
    }
    return *this;
}

BigramFreq* Language::allocate(int n) {
    BigramFreq *v;
    v = new BigramFreq [n];
    return v;


}

void Language::copyFrom(const Language &orig) {
    _size = orig.getSize();
    _vectorBigramFreq = allocate(_size);
    _languageId = orig.getLanguageId();

    for (int i = 0; i < _size; i++) {
        _vectorBigramFreq[i] = orig.at(i);
    }
}

void Language::increase() {
    BigramFreq* aux = new BigramFreq[_size + 1];
    for (int i = 0; i < (_size); i++) {
        aux[i] = _vectorBigramFreq[i];
    }
    delete[] _vectorBigramFreq;
    _size++;
    _vectorBigramFreq = aux;
}

std::ostream &operator<<(std::ostream& os, const Language& language) {
    os << language.getLanguageId() << endl;
    os << language.toString();
    return os;
}

std::istream &operator>>(std::istream& is, Language& language) {
    std::string id;
    int num_bigrams;
    is >> id;
    is >> num_bigrams;
    Language l(num_bigrams);
    l.setLanguageId(id);
    BigramFreq bigramfreq;
    for (int i = 0; i < num_bigrams; i++) {

        is >> bigramfreq;
        l[i] = bigramfreq;
    }
    language = l;

    return is;
}