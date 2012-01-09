#include "helper.h"
int helper_is_alphabet(char c){
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}
int helper_is_number(char c){
    if ((c >= '0' && c <= '9'))
        return 1;
    return 0;
}
int helper_is_alphabet(std::string c){
    if (c.length() != 1)
        return 0;
    if ((c >= "a" && c <= "z") || (c >= "A" && c <= "Z"))
        return 1;
    return 0;
}
int helper_is_same_word(char c){
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    for (int i = 0; i < basic_component_symbols_count; i++) {
        if (c == basic_component_symbols[i]) {
            return 1;
        }
    }
    return 0;
}
int helper_is_same_word(std::string str){
    if (str.length() != 1)
        return 0;
    char c = str[0];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    for (int i = 0; i < basic_component_symbols_count; i++) {
        if (c == basic_component_symbols[i]) {
            return 1;
        }
    }
    return 0;
}
int helper_is_number(std::string c){
    for (size_t i = 0; i < c.length(); i++) {
        if (c[i] - helper_num_char_bias < 0 || c[i] - helper_num_char_bias > 9)
            return 0;
    }
    return 1;
}
int helper_is_basic_symbol_removal(char c){
    size_t i;
    for (i = 0; i < basic_symbols_removable; i++)
        if (c == basic_symbols[i])
            return 1;
    return 0;
}
int helper_is_basic_end_seperator(char c){
    size_t i;
    for (i = 0; i < basic_end_seperators_count; i++)
        if (c == basic_end_seperators[i])
            return 1;
    return 0;
}
int helper_is_basic_symbol(char c){
    size_t i;
    for (i = 0; i < basic_symbols_count; i++)
        if (c == basic_symbols[i])
            return 1;
    return 0;
}
int helper_get_symbol_index(char c){
    size_t i;
    for (i = 0; i < basic_symbols_count; i++) {
        if (c == basic_symbols[i]) {
            return (int)i;
        }
    }
    std::cout << "Error: Symbol not found!\n";
    return INVALID_SYMBOL;
}

GSymbol::GSymbol(char c){
    if (!helper_is_basic_symbol(c)) {
        std::cout << "In constructor of class GSymbol:\nError: char not valid!\n";
        symbol_index = INVALID_SYMBOL;
    }
    symbol_index = helper_get_symbol_index(c);
}
void GSymbol::setContent(char c){
    if (!helper_is_basic_symbol(c)) {
        std::cout << "In constructor of class GSymbol:\nError: char not valid!\n";
        symbol_index = INVALID_SYMBOL;
    }
    symbol_index = helper_get_symbol_index(c);
}
