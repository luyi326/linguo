#include "basic.h"


// TODO:    Establish a sqlite3 protocol, probably inplement as a GBase class

std::bitset<basic_words_count> getWordTypeHelper(std::string&);
inline void getWordTypeHelperHelper(std::string&, std::bitset<basic_words_count>&);

GDataBase::GDataBase(){
    //std::cout << "Constructor runs...\n";
    sql_cmd = "";
    cmd_word_type = "SELECT p_of_speech FROM Words WHERE content = ?";
    isOpen = false;
    //std::cout << "Constructor done.\n";
}//GDataBase()

GDataBase::GDataBase(std::string _filename){
    //std::cout << "Constructor runs...\n";
    sql_cmd = "";
    cmd_word_type = "SELECT p_of_speech FROM Words WHERE content = ?";
    isOpen = false;
    open(_filename);
    //std::cout << "Constructor done.\n";
}//GDataBase(string _filename)

const bool GDataBase::is_open(){
    return isOpen;
}//is_open()

void GDataBase::open(std::string _filename){
    isOpen = !sqlite3_open(_filename.c_str(), &db);
    sqlite3_prepare_v2(db, cmd_word_type.c_str(), -1, &stmt_word_type, &tail);
}//open(string _filename)

std::bitset<basic_words_count> GDataBase::getWordType(std::string _word){
    sqlite3_bind_text(stmt_word_type, 1, _word.c_str(), -1, NULL);
    //std::cout << "Bind succeeded\n";
    int cols = sqlite3_column_count(stmt_word_type);
    std::bitset<basic_words_count> rtnVaule;
    while (sqlite3_step(stmt_word_type) == SQLITE_ROW) {
        //std::cout << "Excutating query...\n";
        for (int i = 0; i < cols; i++) {
            std::cout << _word << "    " << sqlite3_column_text(stmt_word_type, i) << std::endl;
            string tmp = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt_word_type, i)));
            rtnVaule = getWordTypeHelper(tmp);
        }
    }
    //std::cout << "Query done\n";
    sqlite3_reset(stmt_word_type);
    sqlite3_clear_bindings(stmt_word_type);
    //cout << "Types got from WordNet: " << rtnVaule << endl;
    return rtnVaule;
}//getWordType(string _word)

std::bitset<basic_words_count> getWordTypeHelper(std::string & word_){
    size_t posB = 0, posE = 0;
    string buffer = "";
    std::bitset<basic_words_count> rtnVaule;
    while (posE != string::npos) {
        posE = word_.find('&', posB);
        if (posE == string::npos)
            break;
        posE--;
        buffer = word_.substr(posB, posE - posB);
        getWordTypeHelperHelper(buffer, rtnVaule);
        //cout << "buffer = " << buffer << "  posB = " << posB << "  posE = " << posE << endl;
        posB = posE + 2;
    }
    buffer = word_.substr(posB, word_.length() - 1 - posB);
    getWordTypeHelperHelper(buffer, rtnVaule);
    //cout << "buffer = " << buffer << endl;
    return rtnVaule;
}
/*
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
 */
inline void getWordTypeHelperHelper(std::string & str_, std::bitset<basic_words_count> & type_){
    if (str_ == "adj"){
        type_.set(type_adjectives);
        return;
    }
    if (str_ == "adv"){
        type_.set(type_adverbs);
        return;
    }
    if (str_ == "perp"){
        type_.set(type_perpositions);
        return;
    }
    if (str_ == "conj"){
        type_.set(type_conjunctions);
        return;
    }
    if (str_ == "num"){
        type_.set(type_numerals);
        return;
    }
    if (str_ == "int"){
        type_.set(type_interjections);
        return;
    }
    if (str_ == "vt"){
        type_.set(type_verbs_t);
        return;
    }
    if (str_ == "vi"){
        type_.set(type_verbs_i);
        return;
    }
    if (str_ == "n"){
        type_.set(type_nouns);
        return;
    }
    if (str_ == "pron"){
        type_.set(type_pronouns);
        return;
    }
    if (str_ == "art"){
        type_.set(type_articals);
        return;
    }
}

GDataBase::~GDataBase(){
    sqlite3_finalize(statement);
    sqlite3_finalize(stmt_word_type);
    sqlite3_close(db);
}


const basic_base_class_identifier GDataBase::GIdentifier(){
    return id_GDataBase;
}

