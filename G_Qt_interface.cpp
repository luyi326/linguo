#include "G_Qt_interface.h"

GQt::GQt(): output(""){
    dic = new GDataBase("webster.db");
}

GQt::~GQt(){
    delete dic;
}

string GQt::getAnswer(string str){
    input = new GSentence;
    input->get_sentence(str);
    output = "Total elements of buffer: ";
    output += input->length();
    output += "\nTotal word: ";
    output += input->wordsCount();
    output += "\nTotal symbols: ";
    output += input->symbolsCount();
    output += "\n";
    if (dic->is_open()){
        for (int i = 0; i < input->length(); i++) {
            if ((*input)[i].GIdentifier() == id_GListNode_GWord) {
                dic->getWordType((*input)[i].content());
            }
        }
    }
    delete input;
    return output;
}
