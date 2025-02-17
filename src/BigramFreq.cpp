/*
 * Metodología de la Programaci�n: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramFreq.cpp
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */

#include "BigramFreq.h"
using namespace std;

BigramFreq::BigramFreq(){
     _frequency = 0;
}

const Bigram& BigramFreq::getBigram() const {
    return _bigram;
}

int BigramFreq::getFrequency() const {
    return _frequency;
}

void BigramFreq::setBigram(const Bigram& bigram) {
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency) {
    if (frequency < 0) {
        throw std::out_of_range(string("void BigramFreq::setFrequency(int frequency): ") +
                "invalid frecuency " + to_string(frequency));
    }
    _frequency = frequency;
}

std::string BigramFreq::toString() const {
    return _bigram.toString() + " " + to_string(_frequency);
}

void BigramFreq::serialize(std::ostream& outputStream) {
    this->_bigram.serialize(outputStream);
    outputStream.write((char*) &_frequency, sizeof (int));
}

void BigramFreq::deserialize(std::istream& inputStream) {
    this->_bigram.deserialize(inputStream);
    inputStream.read((char*) &_frequency, sizeof (int));

}

std::ostream &operator<<(std::ostream& os, const BigramFreq& bigramFreq) {
    os << bigramFreq.toString();
    return os;
}

std::istream &operator>>(std::istream& is, BigramFreq& bigramFreq) {
    Bigram bigram;
    int freq;
    is >> bigram >> freq;

    bigramFreq.setBigram(bigram);
    bigramFreq.setFrequency(freq);
    return is;
}

bool operator>(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return bigramFreq2<bigramFreq1;
}

bool operator<(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    bool minor = false;
    if (bigramFreq1.getFrequency() < bigramFreq2.getFrequency()) {
        minor = true;
    } else if (bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) {
        if (bigramFreq1.getBigram().getText() > bigramFreq2.getBigram().getText()) {
            minor = true;
        }
    }
    return minor;
}

bool operator==(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return !(bigramFreq1 < bigramFreq2 || bigramFreq2 < bigramFreq1);
}

bool operator!=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return (bigramFreq1 < bigramFreq2 || bigramFreq2 < bigramFreq1);
}

bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return !(bigramFreq2 < bigramFreq1);
}

bool operator>=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return !(bigramFreq1 < bigramFreq2);
}