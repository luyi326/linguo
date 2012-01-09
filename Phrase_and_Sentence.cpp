//
//  Phrase_and_Sentence.cpp
//  Grammer_helper
//
//  Created by Lu Yi on 11/14/11.
//  Copyright 2011 UC Davis. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "basic.h"
#include "Grammer_analysis.h"


#pragma mark -
#pragma mark GPhrase
/****************************************************************************************
 GPhrase 
 
 Er...This thing is deprecated I guess -- Yi.
 ***************************************************************************************/
GPhrase::GPhrase() : listCount(0), phraseFinalType(pos_Undeclared){}

const basic_base_class_identifier GPhrase::GIdentifier(){
    return id_GPhrase;
}

GPhrase::~GPhrase(){};

void GPhrase::setType(basic_words_grammerPos& pos){
    phraseType.set(pos);
}
void GPhrase::setType(std::bitset<basic_words_grammerPos_count>& list){
    phraseType = list;
}

bool GPhrase::addNode(GWord* word){
    phraseListIt = find(PhraseList.begin(), PhraseList.end(), word);
    if (phraseListIt != PhraseList.end()) {
        return false;
    }
    PhraseList.push_back(word);
    return true;
}

const std::bitset<basic_words_grammerPos_count>& GPhrase::type(){
    return phraseType;
}
const basic_words_grammerPos& GPhrase::finalType(){
    return phraseFinalType;
}

void GPhrase::setFinalType(const basic_words_grammerPos& type){
    phraseFinalType = type;
}

std::ostream& operator<<(std::ostream& stream, const std::bitset<basic_words_grammerPos_count>& list){
    for (int i = 0; i < basic_words_grammerPos_count; i++) {
        if (list[i] == 1) {
            stream << basic_words_grammerPos_str[i] << "   ";
        }
    }
    return stream;
}
#pragma mark -  
#pragma mark GSentence
/****************************************************************************************
 GSentence
 
 Note: This class is a derived class of GLinkedList
 
 void get_sentence(string);  Take a string sentence and put it into the list
 void make_empty();          Slightly different with base class make_empty
 
 ***************************************************************************************/
GSentence::GSentence() : sentence_pos(NULL){
    senStatus_init(status);
}

void GSentence::make_empty(){
    GLinkedList::make_empty();
    delete sentence_pos;
    senStatus_init(status);
}
const basic_base_class_identifier GSentence::GIdentifier(){
    return id_GSentence;
}
void GSentence::get_sentence(std::string sentence){
    if (sentence != "") {
        analysis_scan_sentence(sentence, *this);
        sentence_pos = new basic_words_grammerPos[length()];
        status.notEmpty = true;
    }
}