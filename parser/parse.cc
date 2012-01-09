/*
 * parse.cc
 *
 *  Created on: Jan 9, 2012
 *      Author: martin
 */

#include <locale.h>
#include <stdio.h>
#include "link_parser/link-includes.h"
#include "link_parser/constituents.h"
#include <string>
#include "parse.h"
//#include <iostream>

using namespace std;

void static printError(const char* error){
	printf("parse: %s\n", error);
}

int parse(string & sentence) {
	int returnCode = 0; //meaning no problem
	Dictionary dict;
	Parse_Options opts;
	Sentence sent;
	Linkage linkage;
	CNode * cn;
	char * string;
	char* word;
	int sent_len = 0;

	setlocale(LC_ALL, "");
	opts = parse_options_create();
	dict = dictionary_create_lang("en");
	if (!dict) {
		printf("Fatal error: Unable to open the dictionary\n");
		return 1;
	}

	sent = sentence_create(sentence.c_str(), dict);
	if (sentence_split(sent, opts)) {
		printf("Warning: Unable to tokenize the sentence\n");
		return 1;
	}

	//	printf("%d\n", sent_len = sentence_length(sent));
	//	 for(int i = 0; i < sent_len; i++){
	//	 printf("%s ", sentence_get_word(sent, i));
	//	 }

	if (sentence_parse(sent, opts)) {
		linkage = linkage_create(0, sent, opts);

		printf("%d\n", sent_len = sentence_length(sent));
		for (int i = 0; i < sent_len; i++) {
			printf("%s ", linkage_get_word(linkage, i));
		}

		//        printf("%s", string = linkage_print_diagram(linkage));
		//        linkage_free_diagram(string);
		//		cn = linkage_constituent_tree(linkage);
		//		print_words_with_labels(cn);
		//		linkage_free_constituent_tree(cn);
//		fprintf(stdout, "\n\n");
		linkage_delete(linkage);
	}else{
		printError("can't parse.\n");
		returnCode = 1;
	}

	sentence_delete(sent);
	dictionary_delete(dict);
	parse_options_delete(opts);
	return returnCode;
}
