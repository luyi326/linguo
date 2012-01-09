//
//  basic.cpp
//  Grammer_helper
//
//  Created by Lu Yi on 11/9/11.
//  Copyright 2011 UC Davis. All rights reserved.
//

#include <iostream>
#include <bitset>
#include "basic.h"
#include "helper.h"

const char basic_end_seperators[] = {'!', '?', '.'};
const int basic_end_seperators_count = 3;
const char basic_symbols[] = {'!', '?', '.', '(', ')', ',', ';', ':', '#', '$', '&', '~','\''};
const char basic_component_symbols[] = {'\''};

#pragma mark -
#pragma mark GBase

const basic_base_class_identifier GBase::GIdentifier(){
        return id_GBase;
}
#pragma mark -
#pragma mark GSymbol
/****************************************************************************************
 GSymbol
 
 GSymbol();               Constructor
 void setContent(char);   set the current symbol, seems to be under construction
 const char content();    return the symbol in charactors of current symbol
 ***************************************************************************************/
GSymbol::GSymbol(){
    symbol_index = INVALID_SYMBOL;
}

const char GSymbol::content(){
    if (symbol_index == INVALID_SYMBOL) {
        std::cout << "Warning: Invalid symbol, return space!\n";
        return ' ';
    }
    return basic_symbols[symbol_index];
}//GSymbol::content()

const basic_base_class_identifier GSymbol::GIdentifier(){
    return id_GSymbol;
}//GSymbol::GIdentifier()
#pragma mark -
#pragma mark GWord
/****************************************************************************************
 GWord
 
 GWord();                               Constructor
 GWord(string);                         String Copy Constructor
 void setContent(string);               set the content of current word
 void setType(basic_words_type);        
 void setPos(basic_words_grammerPos);
 const string content();                return content
 const size_t length();                 return length of word
 const basic_words_type_list type();
 const basic_words_grammerPos position();
 const void display();                  print the word
 ***************************************************************************************/
GWord::GWord(){
    wordContent = "";
    wordLength = 0;
    wordType.set(0);
    wordFinalType = type_undeclared;
}//GWord::GWord()

GWord::GWord(std::string buffer){
    wordContent = buffer;
    wordLength = buffer.length();
    wordType.set(0);
    wordFinalType = type_undeclared;
}//GWord::GWord(string)
// Constructors

void GWord::setContent(const std::string & buffer){
    wordContent = buffer;
    wordLength = buffer.length();
}//GWord::setContent(string)

void GWord::setType(const basic_words_type & type){
    //basic_words_type tmp = type_undeclared;
    for (int i = 0; i < basic_words_count; i++) {
        if ((basic_words_type)i == type) {
            wordType[i] = true;
            return;
        }
    }
}//GWord::setType()

void GWord::setType(const std::bitset<basic_words_count> & list){
    wordType = list;
}//GWord::setType()

void GWord::setFinalType(const basic_words_type& type){
    wordFinalType = type;
}//GWord::setFinalType()
//functions for setting a word

const std::string GWord::content(){
    return wordContent;
}//GWord::content()

const size_t GWord::length(){
    return wordLength;
}//GWord::length()

const std::bitset<basic_words_count>& GWord::type(){
    return wordType;
}//GWord::type()

const basic_words_type& GWord::finalType(){
    return wordFinalType;
}//GWord::finalType()

const void GWord::display(){
    std::cout << "Content: " << content() << "  Length: " << length() << "  Type: " << type() << "\n";
}//GWord::display()
//functions for reading a word

const basic_base_class_identifier GWord::GIdentifier(){
    return id_GWord;
}//GWord::Gindentifier()

std::ostream& operator<<(std::ostream& stream, const std::bitset<basic_symbols_count>& list){
    for (int i = 0; i < basic_symbols_count; i++) {
        if (list[i] == true) {
            stream << basic_words_type_str[i] << " ";
        }
    }
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const std::bitset<basic_words_count>& list){
    for (int i = 0; i < basic_words_count; i++) {
        if (list[i] == true) {
            stream << basic_words_type_str[i] << " ";
        }
    }
    return stream;
}
#pragma mark -
#pragma mark GListNode
/****************************************************************************************
 GListNode
 Note: This class can switch its content btw symbol and word automatically,
 all thing needed to be done is to use the setContent functions.
 
 GListNode();                       Constructor
 GListNode(string);                 String Copy Constructor
 GListNode(char);                   Charactor/Symbol Copy Constructor
 void setContent(string);           Set this node to a word with string
 void SetContent(char);             Set this node to a symbol with a charactor
 void setPtr(GListNode* node);      Set next pointer of this node
 GListNode* nextPointer();          Return the next pointer
 const string content();            Return content
 ***************************************************************************************/
GListNode::GListNode() : content_word(NULL), content_symbol(NULL), nextPtr(NULL){}
//GListNode::GListNode()

GListNode::GListNode(std::string _content){
    if (_content.length() == 1) {
        if (helper_is_basic_symbol(_content[0])) {
            content_symbol = new GSymbol(_content[0]);
            content_word = NULL;
            nextPtr = NULL;
            return;
        }
    }
    content_word = new GWord(_content);
    content_symbol = NULL;
    nextPtr = NULL;
}//GListNode::GListNode(string)

GListNode::GListNode(char _content){
    content_symbol = new GSymbol(_content);
    content_word = NULL;
    nextPtr = NULL;
}//GListNode::GListNode(char)

void GListNode::setContent(std::string _content){
    if (GIdentifier() == id_GListNode_GSymbol)
    {
        if (content_symbol != NULL)
            delete content_symbol;
        content_symbol = NULL;
        content_word = new GWord(_content);
    }else if (GIdentifier() == id_GListNode_GWord) {
        if (content_word == NULL)
            content_word = new GWord();
        content_word->setContent(_content);
    }else{
        if (content_word == NULL)
            content_word = new GWord(_content);
        else
            content_word->setContent(_content);
    }
}//GListNode::setContent(string)

void GListNode::setContent(char _content){
    if (GIdentifier() == id_GListNode_GWord)
    {
        if (content_word != NULL)
            delete content_word;
        content_word = NULL;
        content_symbol = new GSymbol(_content);
    }else if (GIdentifier() == id_GListNode_GSymbol) {
        if (content_word == NULL)
            content_symbol = new GSymbol();
        content_symbol->setContent(_content);
    }else{
        if ( content_symbol == NULL)
            content_symbol = new GSymbol(_content);
        else
            content_symbol->setContent(_content);
    }
}//GListNode::setContent(char)

void GListNode::setPtr(GListNode* node){
    nextPtr = node;
}//GListNode::setPtr(GListNode*)

GListNode* GListNode::nextPointer(){
    return nextPtr;
}//GListNode::nextPointer()

const std::string GListNode::content(){
    if (content_word != NULL){
        return content_word->content();
    }else if (content_symbol != NULL){
        return std::string(1,(content_symbol->content()));
    }
    return " ";
}//GListNode::content()

GListNode::~GListNode(){
    //std::cout << "Destructor of List node  running....";
    if (content_word != NULL)
        delete content_word;
    if (content_symbol != NULL)
        delete content_symbol;
    //std::cout << "Done.\n";
}//GListNode::~GListNode()

const basic_base_class_identifier GListNode::GIdentifier(){
    if (content_symbol != NULL)
        return id_GListNode_GSymbol;
    if (content_word != NULL)
        return id_GListNode_GWord;
    return id_GListNode;
}//GListNode::Gindentifier()
#pragma mark -
#pragma mark GLinkedList
/****************************************************************************************
 GLinkedList
 
 GLinkedList();                     Constructor
 void addNode(string);              Add a word as node
 void addNode(char);                Add a symbol as node
 void makeEmpty();                  Re-initialize the list
 GListNode& operator[](int index);  Overloaded operator[], CAN be used as lvalue
 const int length(){;               Return the count of total nodes in list
 const int wordsCount();            Return total number of words
 const int symbolsCount();          Return total number of symbols
 const void printList();            Print the content of the whole list
 ***************************************************************************************/
GLinkedList::GLinkedList(): firstPtr(NULL), currentPtr(NULL), currentLength(NULL), words_count(NULL), symbols_count(NULL){}//GLinkedList::GLinkedList()

void GLinkedList::addNode(std::string _content){
    if (firstPtr == NULL){
        firstPtr = new GListNode(_content);
        currentPtr = firstPtr;
        currentLength++;
    }else {
        currentPtr->nextPtr = new GListNode(_content);
        currentPtr = currentPtr->nextPtr;
        currentLength++;
    }
    words_count++;
    //std::cout << "Node added :" << currentPtr << std::endl;
}//GLinkedList::addNode(std::string _content)

void GLinkedList::addNode(char _content){
    if (firstPtr == NULL){
        firstPtr = new GListNode(_content);
        currentPtr = firstPtr;
        currentLength++;
    }else {
        currentPtr->nextPtr = new GListNode(_content);
        currentPtr = currentPtr->nextPtr;
        currentLength++;
    }
    symbols_count++;
    //std::cout << "Node added :" << currentPtr << std::endl;
}//GLinkedList::addNode(char _content)

void GLinkedList::make_empty(){
    if (firstPtr != NULL) {
        GListNode * tmpPtr = firstPtr;
        currentPtr = firstPtr;
        while (currentPtr->nextPtr != NULL) {
            currentPtr = currentPtr->nextPtr;
            delete tmpPtr;
            tmpPtr = currentPtr;
        }
        delete currentPtr;
    }
    currentPtr = NULL;
    firstPtr = NULL;
    currentLength = NULL;
    words_count = NULL;
    symbols_count = NULL;
}
GListNode& GLinkedList::operator[](int index){
    if (index < 0){
        std::cout << "In class LinkedList:\nError: Invalid index!Return first Node.\n";
        return *firstPtr;
    }
    if (index - 1 > currentLength){
        std::cout << "In class LinkedList:\nError: Node not exist!Return last Node.\n";
        return *currentPtr;
    }
    GListNode * rtnPtr = firstPtr;
    for (int i = 0; i < index; i++) {
        rtnPtr = rtnPtr->nextPointer();
    }
    return *rtnPtr;
}
const int GLinkedList::length(){
    return currentLength;
}
const int GLinkedList::wordsCount(){
    return words_count;
}
const int GLinkedList::symbolsCount(){
    return symbols_count;
}
void GLinkedList::printList(std::ostream & stream){
    GListNode * tmpPtr = firstPtr;
    while (tmpPtr != NULL) {
        stream << tmpPtr->content();
        if (tmpPtr->nextPointer() != NULL)
            if (tmpPtr->nextPointer()->GIdentifier() == id_GListNode_GWord)
                stream << " ";
        tmpPtr = tmpPtr->nextPointer();
    }
}
GLinkedList::~GLinkedList(){
    //std::cout << "Destructor of linked list running....";
    GListNode * uppPtr = firstPtr;
    GListNode * lowPtr = NULL;
    if (firstPtr == NULL) {return;}
    if (firstPtr->nextPointer() != NULL)
        lowPtr = firstPtr->nextPointer();
    while (uppPtr != NULL) {
        //std::cout << "uppPtr = " << uppPtr << "  lowPtr = " << lowPtr << "...";
        delete uppPtr;
        uppPtr = lowPtr;
        if (uppPtr == NULL)
            return;
        if (lowPtr->nextPointer() == NULL){
            delete lowPtr;
            //std::cout << "M..done.\n";
            return;
        }
        lowPtr = lowPtr->nextPointer();
        //std::cout << "done.\n";
    }
    //std::cout << "Done.\n";
}
const basic_base_class_identifier GLinkedList::GIdentifier(){
    return id_GLinkedList;
}
