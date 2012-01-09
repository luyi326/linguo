//
//  helper.h
//  Test_helper
//
//  Created by Lu Yi on 11/8/13.
//  Copyright 2011 UC Davis. All rights reserved.
//

#ifndef Test_helper_helper_h
#define Test_helper_helper_h
#include <iostream>
#include "basic.h"
int helper_is_basic_end_seperator(char);
int helper_is_basic_symbol_removal(char);
int helper_is_basic_symbol(char);
int helper_get_symbol_index(char);
int helper_is_alphabet(char);
int helper_is_alphabet(std::string);
int helper_is_same_word(char);
int helper_is_same_word(std::string);
int helper_is_number(char);
int helper_is_number(std::string);
const int helper_num_char_bias = '1' - 1;

#endif
