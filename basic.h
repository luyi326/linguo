//
//  basic.h
//
//  Created by Lu Yi on 11/8/12.
//  Copyright 2011 UC Davis. All rights reserved.
//

#ifndef BASIC_H
#define BASIC_H

//#include <cstring>
#include <iostream>
#include <bitset>
#include <list>
#include "sqlite3.h"
#include "basicTypes.h"
#include "include_parser.h"

/****************************************************************************************
 Warning!!! Do not try to return a GLinkedList (including children classes) of GListNode type in function call! Use pass parameter as reference! 
 ***************************************************************************************/
#pragma mark -
#pragma mark GBase
class GBase {
public:
    
    virtual const basic_base_class_identifier GIdentifier();
}; 
#pragma mark -
#pragma mark GSymbol
/****************************************************************************************
 GSymbol
 
 GSymbol();               Constructor
 void setContent(char);   set the current symbol, seems to be under construction
 const char content();    return the symbol in charactors of current symbol
 ***************************************************************************************/
class GSymbol : public GBase{
public:
    GSymbol();
    GSymbol(char);
    //virtual ~GSymbol();
    
    void setContent(char);
    const char content();
    const basic_base_class_identifier GIdentifier();
private:
    int symbol_index;
};
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
class GWord : public GBase{
    friend class analysiser;
    friend class graParser;
    friend class lexParser;
public:
    GWord();
    GWord(std::string buffer);
    // Constructors 
    void setContent(const std::string& buffer);
    void setType(const basic_words_type& type);
    void setType(const std::bitset<basic_words_count>&);
    //functions for setting a word
    
    const std::string content();
    const size_t length();
    const std::bitset<basic_words_count>& type();
    const basic_words_type& finalType();
    const void display();
    //functions for reading a word
    const basic_base_class_identifier GIdentifier();
private:
    void setFinalType(const basic_words_type& type);
    std::string wordContent;
    size_t wordLength;
    basic_words_type wordFinalType;
    std::bitset<basic_words_count> wordType;
};
std::ostream& operator<<(std::ostream&,const std::bitset<basic_symbols_count>&);
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
class GListNode : public GBase{
    friend class GLinkedList;
    friend class analysiser;
    friend class graParser;
    friend class lexParser;
public:
    GListNode();
    GListNode(std::string _content);
    GListNode(char _content);
    void setContent(std::string _content);
    void setContent(char _content);
    void setPtr(GListNode* node);
    GListNode* nextPointer();
    const std::string content();
    ~GListNode();
    const basic_base_class_identifier GIdentifier();
private:
    GWord * content_word;
    GSymbol * content_symbol;
    GListNode * nextPtr;
};
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
 const void printList(osteram);     Flush the whole sentense to an osteram obj
 ***************************************************************************************/
class GLinkedList : public GBase{
    friend class analysiser;
    friend class graParser;
    friend class lexParser;
public:
    GLinkedList();
    void addNode(std::string _content);
    void addNode(char _content);
    void make_empty();
    GListNode& operator[](int index);
    const int length();
    const int wordsCount();
    const int symbolsCount();
    void printList(std::ostream&);
    ~GLinkedList();
    const basic_base_class_identifier GIdentifier();
private:
    GListNode* firstPtr;
    GListNode* currentPtr;
    int currentLength;
    int words_count;
    int symbols_count;
};
#pragma mark -
#pragma mark GPhrase
/****************************************************************************************
 GPhrase 
 
 Used as a list for storing phrase
 ***************************************************************************************/
class GPhrase : public GBase{
    friend class analysiser;
    friend class graParser;
    friend class lexParser;
public:
    GPhrase();
    ~GPhrase();
    void setType(basic_words_grammerPos&);
    void setType(std::bitset<basic_words_grammerPos_count>&);
    bool addNode(GWord*); // if successfully added node, return true otherwise false
    
    const std::bitset<basic_words_grammerPos_count>& type();
    const basic_words_grammerPos& finalType();
    
    const basic_base_class_identifier GIdentifier();
private:
    void setFinalType(const basic_words_grammerPos& type);
    std::list<GWord*> PhraseList;
    std::list<GWord*>::iterator phraseListIt;
    int listCount;
    std::bitset<basic_words_grammerPos_count> phraseType;
    basic_words_grammerPos phraseFinalType;
};
std::ostream& operator<<(std::ostream&, const std::bitset<basic_words_grammerPos_count>&);
#pragma mark -
#pragma mark GSentence
/****************************************************************************************
 GSentence
 
 Note: This class is a derived class of GLinkedList
 
 void get_sentence(string);  Take a string sentence and put it into the list
 void make_empty();          Slightly different with base class make_empty
 
 TODO:  Use int * sentence_pos to track the component of the sentence
 ***************************************************************************************/
#include "sentense_status.h"
class GSentence : public GLinkedList {
    friend void analysis_scan_sentence(std::string, GSentence&);
    friend class analysiser;
    friend class graParser;
    friend class lexParser;
public:
    GSentence();
    void get_sentence(std::string sentense);
    void make_empty();
    const basic_base_class_identifier GIdentifier();
private:
    basic_words_grammerPos * sentence_pos;
    std::list<GListNode*> word_list;
    std::list<GListNode*> symbol_list;
    std::list<GPhrase> phrase_list;
    senStatus status;
};
#pragma mark -  
#pragma mark GDataBase
/****************************************************************************************
 GDataBase
 TODO:  SQL statement operations.
 ***************************************************************************************/
class GDataBase : public GBase {
public:
    GDataBase();
    GDataBase(std::string);
    const bool is_open();
    void open(std::string);
    std::bitset<basic_words_count> getWordType(std::string);
    
    const basic_base_class_identifier GIdentifier();
    ~GDataBase();
private:
    sqlite3 *db;
    sqlite3_stmt *statement;
    std::string sql_cmd;
    
    sqlite3_stmt *stmt_word_type;
    std::string cmd_word_type;
    const char *tail;
    bool isOpen;
};
#endif
