/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file Bigram.cpp
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 */

#include "Bigram.h"

using namespace std;

Bigram::Bigram(const std::string& text) {
    if (text.size() == 2) {
        strcpy(_text, text.c_str());
    } else {
        strcpy(_text, "__");
    }
}

Bigram::Bigram(char first, char second) {
    _text[0] = first;
    _text[1] = second;
    _text[2] = '\0';
}

Bigram::Bigram(const char text[]) {
    if (strlen(text) == 2) {
        strcpy(_text, text);
    } else {
        strcpy(_text, "__");
    }
}

std::string Bigram::getText() const {
    return string(_text);
}

std::string Bigram::toString() const {
    return string(_text);
}

const char& Bigram::at(int index) const {
    if (index < 0 || index > 1) {
        throw std::out_of_range(string("const char& Bigram::at(int index) const: ") +
                "invalid position " + to_string(index));
    } else {
        return _text[index];
    }
}

char& Bigram::at(int index) {
    if (index < 0 || index > 1) {
        throw std::out_of_range(string("char& Bigram::at(int index): ") +
                "invalid position " + to_string(index));
    } else {
        return _text[index];
    }
}

void Bigram::toUpper() {
    int asciidiff = 'a' - 'A';
    //int isodiff = 'à' - 'À';
    for (int i = 0; i < 2; i++) {
        if (_text[i] >= 'a' && _text[i] <= 'z') {
            _text[i] = _text[i] - asciidiff;
        } /*else if (_text[i] >= à' && _text[i] <= 'ü') {
                _text[i] = _text[i] - isodiff;
        }*/
    }
}

void Bigram::toLower() {
    int asciidiff = 'a' - 'A';
    //int isodiff = 'à' - 'À';
    for (int i = 0; i < 2; i++) {
        if (_text[i] >= 'A' && _text[i] <= 'Z') {
            _text[i] = _text[i] + asciidiff;
        } /*else if (_text[i] >= À' && _text[i] <= 'Ü') {
                _text[i] = _text[i] - isodiff;
        }*/
    }
}

void Bigram::serialize(std::ostream& outputStream) {
    outputStream.write(_text, 2);
}

void Bigram::deserialize(std::istream& inputStream) {
    inputStream.get(_text, 3);

}

char& Bigram::operator[](size_t pos) {
    return _text[pos];
}

const char& Bigram::operator[](size_t pos) const {
    return _text[pos];
}

bool isValidCharacter(char character, const string& validCharacters) {
    if (validCharacters.find(character) >= 0 && validCharacters.find(character) < validCharacters.size())
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream& os, const Bigram& bigram) {
    os << bigram.getText();
    return os;
}

std::istream &operator>>(std::istream& is, Bigram& bigram) {
    string s;
    is >> s;
    bigram[0] = s[0];
    bigram[1] = s[1];
    bigram[2] = '\0';
    return is;
}
