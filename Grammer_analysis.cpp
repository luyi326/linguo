#include "Grammer_analysis.h"

void analysis_scan_sentence(std::string buffer, GSentence& result){
    const char * buffer_c_str = buffer.c_str();
    int scan_pos = 0;
    while (scan_pos <= buffer.length()) {
        if (helper_is_alphabet(buffer_c_str[scan_pos])) 
        {
            int _word_len = 0, _ori_pos = scan_pos;
            while (helper_is_same_word(buffer_c_str[scan_pos])) 
            {
                if (helper_is_same_word(buffer_c_str[scan_pos]))
                    _word_len++;
                scan_pos++;
            }
            result.addNode(buffer.substr(_ori_pos, _word_len));
        }else if (helper_is_basic_symbol(buffer[scan_pos]))
        {
            result.addNode(buffer_c_str[scan_pos]);
            scan_pos++;
            
        } else if ((int)buffer[scan_pos] == (int)' ')
        {
            scan_pos++;
        } else {
            scan_pos++;
        }
    }
}
