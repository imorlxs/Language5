/*
 * Metodología de la Programación: Language4
 * Curso 2022/2023
 */

/** 
 * @file Bigram.cpp
 * @author Isaac Morales Santana <imorsan@correo.ugr.es>
 * @author Francisco Javier Caceres Martin <javicaceres@correo.ugr.es>
 */

#include <string>
#include <cstring>

#include "Bigram.h"

using namespace std;

Bigram::Bigram(const std::string& text) {
    if (text.size() == 2) {
        strcpy(_text,text.c_str());
    }
    else{
        strcpy(_text, "__"); // ¿Lanzar excepción?
    }
}
    
Bigram::Bigram(char first, char second) { 
    _text[0] = first;
    _text[1] = second;
    _text[2] = '\0';
}

Bigram::Bigram(const char* text)  { 
    if (strlen(text) == 2) {
        strcpy(_text, text);
    }
    else{
        strcpy(_text, "__");  // ¿Lanzar excepción?
    } 
}

std::string Bigram::getText() const{
    return string(_text);
}

std::string Bigram::toString() const {
    return string(_text);
}

const char& Bigram::at(int index) const{
    if(index<0 || index>1){
        throw std::out_of_range(string("const char& Bigram::at(int index) const: ") +
                "invalid position " + to_string(index));
    }
    else{
        return _text[index];
    }
}

char& Bigram::at(int index){
    if(index<0 || index>1){
        throw std::out_of_range(string("char& Bigram::at(int index): ") +
                "invalid position " + to_string(index));
    }
    else{
        return _text[index];
    }
}


void Bigram::toUpper() {
    at(0) = toupper(at(0));
    at(1) = toupper(at(1));
}

bool isValidCharacter(char character, const string& validCharacters) {
    return validCharacters.find(character)!=string::npos;
}

