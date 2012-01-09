#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H
#include <iostream>

 #pragma mark -
 #pragma mark Basic const and type define
 extern const char basic_end_seperators[];
 extern const int basic_end_seperators_count;
 //if addition of basic_symbols is needed, add end seperators in the front and change the corresponding const down below.
 extern const char basic_component_symbols[];// define a symbol that's considerred a part of word
 extern const char basic_symbols[];
 const int basic_symbols_removable = 8;
 const int basic_symbols_count = 13;
 const int basic_component_symbols_count = 1;
 const int basic_words_count = 12;
 const int INVALID_SYMBOL= -1;
 //const int NULL = 0;
 
 enum basic_words_type {
 type_undeclared, 
 type_adjectives, 
 type_adverbs, 
 type_perpositions, 
 type_conjunctions, 
 type_numerals, 
 type_interjections, 
 type_verbs_t, 
 type_verbs_i, 
 type_nouns, 
 type_pronouns, 
 type_articals
 };
 const std::string basic_words_type_str[basic_words_count] = {
 "Not defined yet..",
 "adjective",
 "adverb",
 "perposition",
 "conjunction",
 "numeral",
 "interjection",
 "transitive verb",
 "intransitive verb",
 "noun",
 "pronoun",
 "article"
 };
 
 //std::ostream& operator<<(std::ostream& out, basic_words_type_list list);
 
 
 #define LIN_STYPE
 #ifdef LIN_STYLE
 enum basic_words_grammerPos {
 pos_Undeclared, 
 pos_NounPhrase, 
 pos_VerbPhrase, 
 pos_Object, 
 pos_Complement, 
 pos_Predicative, 
 pos_Attributive, 
 pos_Adverbial,
 pos_Symbol
 };
 const int basic_words_grammerPos_count = 9;
 const std::string basic_words_grammerPos_str[basic_words_grammerPos_count] = {
 "Not defined yet..",
 "Subject",
 "Verb",
 "Object",
 "Complement",
 "Predicative",
 "Attributive",
 "Adverbial",
 "Symbol"
 };
 #else //ifdef LIN_STYLE
 enum basic_words_grammerPos {
 pos_Undeclared, 
 pos_Suject, 
 pos_Verb, 
 pos_Object, 
 pos_Complement, 
 pos_Predicative, 
 pos_Attributive, 
 pos_Adverbial,
 pos_Symbol
 };
 const int basic_words_grammerPos_count = 9;
 const std::string basic_words_grammerPos_str[basic_words_grammerPos_count] = {
 "Not defined yet..",
 "Subject",
 "Verb",
 "Object",
 "Complement",
 "Predicative",
 "Attributive",
 "Adverbial",
 "Symbol"
 };
 #endif //ifdef LIN_STYLE
 
 enum basic_base_class_identifier {
 id_GBase, 
 id_GContent,
 id_GLinkedList, 
 id_GListNode,
 id_GListNode_GWord,
 id_GListNode_GSymbol,
 id_GWord, 
 id_GSymbol,
 id_GSentence,
 id_GPhrase,
 id_GDataBase
 };
 
 
 #pragma mark -
 #pragma mark Basic class phrototype:
 /****************************************************************************************
 See phrototype of each class at the beginning of classes, all classes contain
 "
 const basic_base_class_identifier GIdentifier();
 "
 for identification purpose
 ***************************************************************************************/
 class GBase;
 class GSymbol;
 class GListNode;
 class GLinkedList;
 class GWord;
 class GSentence;
 class GPhrase;
 class GDataBase;
 class graParser;
 class lexParser;

#endif //BASIC_TYPES_H