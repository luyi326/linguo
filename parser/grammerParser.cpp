/******************************************************************
 THE FOLLOWING CODE IS NOT TESTED AT ALL!!!
 ******************************************************************/
#include <iostream>
#include <sstream>
#include "grammerParser.h"
#include "parserConst.h"

#include "../basicTypes.h"
#include "../helper.h"
#include <cstdlib>

using namespace std;

#define MUTE_GPARSER
#undef MUTE_GPARSER

graParser::graParser(){};

void graParser::startParse(GSentence & sentence, GDataBase & db){
    #ifndef MUTE_GPARSER
    string header = "From startParse(): ";
    cout << header << "Parsing begin\n";
    #endif
    if (!sentence.status.notEmpty){
        #ifndef MUTE_GPARSER
        cout << header << "Null sentense!\n";
        #endif
        return;
    }
    if (!sentence.status.gparseInited)
        init(sentence);
    if (!sentence.status.gparseBChecked) {
        if (!basicCheck(sentence)) {
            #ifndef MUTE_GPARSER
            cout << header << "Error returned from basicCheck()\n";
            #endif
        }
    }
    #ifndef MUTE_GPARSER
    cout << header << "Parsing end\n";
    #endif
}

//PASS 1: Initialize the sentence
inline void graParser::init(GSentence & sentence){
    for (GListNode* i = sentence.firstPtr; i->nextPtr != NULL; i++) {
        if (i->GIdentifier() == id_GListNode_GWord) {
            sentence.word_list.push_back(i);
        }else if (i->GIdentifier() == id_GListNode_GSymbol){
            sentence.symbol_list.push_back(i);
        }else{
            #ifndef MUTE_GPARSER
            cout << "Fatal: Undeclared component in current sentence, of type " << i->GIdentifier() << endl;
            #endif
            exit(-1);
        }
    }
    sentence.status.gparseInited = true;
}

//PASS 2: Briefly check if the current sentence is valid
inline bool graParser::basicCheck(GSentence & sentence){
    #ifndef MUTE_GPARSER
    string header = "From basicCheck(): ";
    #endif
    if (sentence.wordsCount() == 0){
        #ifndef MUTE_GPARSER
        cout << header << "No word found in current sentence\n";
        #endif
        return false;
    }
    if (sentence.symbolsCount() == 0) {
        #ifndef MUTE_GPARSER
        cout << header << "No symbol found in current sentence, appending a period\n";
        #endif
        sentence.addNode(".");
    }
    
    list<GListNode*>::iterator it = sentence.symbol_list.begin();
    bool missing_end = true;
    for (; it != sentence.symbol_list.end(); it++) {
        if (helper_is_basic_end_seperator((*it)->content_symbol->content())){
            missing_end = false;
            break;
        }
    }
    if (missing_end == true){
        #ifndef MUTE_GPARSER
        cout << header << "End seperator missing! Appending a period\n";
        #endif
        sentence.addNode(".");
    }
    #ifndef MUTE_GPARSER
    cout << header << "All good!\n";
    #endif
    sentence.status.gparseBChecked = true;
    return true;
}

//PASS 3: Visit database and assign those words their POS
inline void graParser::wordCheck(GSentence & sentence){
    std::ostringstream oss_sentence;
    sentence.printList(oss_sentence);
    string ori_sentence = oss_sentence.str(); // ready to flush string to Link Parser (CMU)
//    parse(ori_sentence); //todo implement parse()
}

void graParser::tagWithWordNet(GSentence & sentence, GDataBase & database){
    
}
