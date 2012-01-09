//
//  test_Cmd_Interface.cpp
//
//  Created by Lu Yi on 11/8/12.
//  Copyright 2011 UC Davis. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "Grammer_analysis.h"
#include "helper.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;
void bufferTest();
int LinkedListTest();
int ListNodeTest();
void seperateWordTest();

int main(void){
    clock_t tik,tak;
    tik = clock();
    
    std::cout << "Trying to connect to database webster.db...";
    sqlite3 *db;
    sqlite3_stmt *statement;
    string sql_cmd = "";
    const char *tail;
    int DB_FAILED = 0;
    DB_FAILED = sqlite3_open("webster.db", &db);
    if (DB_FAILED) {cout << "Failed.\n";}else{cout << "Succeeded.\n";}
    
    ListNodeTest();
    LinkedListTest();
    GWord apple("apple");
    bufferTest();
    apple.display();
    tak = clock();
    std::cout << "Time cost: " << 1000*(double)(tak - tik)/CLOCKS_PER_SEC << "ms." << std::endl;
    return EXIT_SUCCESS;
}

void bufferTest(){
    bool quit_flag = false;
    //char ** ptr;
    std::string inputBuffer = "";
    std::cout << "\n\n************************************************\nWelcome to the grammer helper test interface!\nThis interface is for test only!\n************************************************\nPlease input a complete sentence or phrase for testing:\n\n";
    GSentence test;
    while (!quit_flag) {
        std::cout << "Test_input> ";
        std::getline(std::cin, inputBuffer);
        if (inputBuffer == "q" || inputBuffer == "Q"){
            quit_flag = true;
            break;
        }
        if (quit_flag == false) {
            test.make_empty();
            test.get_sentence(inputBuffer);
            //std::cout << "Finish scanning!\n";
            std::cout << "Total elements of buffer: " << test.length() << "\nTotal word: " << test.wordsCount() << "\nTotal symbols: " << test.symbolsCount() << std::endl;
            test.printList();
        }
    }
}
int ListNodeTest(){
    std::cout << "Testing ListNode..............\n";
    std::cout << "This is a test, lol!\n";
    try {
    GListNode thisN("This");
    GListNode is("is");
    GListNode a("a");
    GListNode test("test");
    GListNode s1(',');
    GListNode lol("lol");
    GListNode punc('!');
    
    thisN.setPtr(&is);
    is.setPtr(&a);
    a.setPtr(&test);
    test.setPtr(&s1);
    s1.setPtr(&lol);
    lol.setPtr(&punc);
    
    GListNode * currentPtr = &thisN;
    while (currentPtr != 0) {
        std::cout << currentPtr->content();
        if (currentPtr->nextPointer() != 0)
            if (currentPtr->nextPointer()->GIdentifier() == id_GListNode_GWord)
                std::cout << " ";
        currentPtr = currentPtr->nextPointer();
    }
    std::cout << std::endl;
    }catch(int){
        std::cout << "error occured.\n";
        return EXIT_FAILURE;
    }
    std::cout << "Test for list node done. All good!\n";
    return EXIT_SUCCESS;
}
int LinkedListTest(){
    std::cout << "Test for linked list begin.\n";
    std::cout << "This is a test, lol!\n";
    try {
        GLinkedList test;
        test.addNode("This");
        test.addNode("is");
        test.addNode("a");
        test.addNode("test");
        test.addNode(',');
        test.addNode("lol");
        test.addNode('!');
        test.printList();
        test[0].setContent("That");
        test.printList();
        test[1];
        test[2];
        test[3];
        test[4];
        test[5];
        test[6];
        std::cout << "Total nodes: " << test.length() << std::endl;
        std::cout << "Total words: " << test.wordsCount() << std::endl;
        std::cout << "Total symbols: " << test.symbolsCount() << std::endl;
    } catch (int) {
        std::cout << "Error occured.\n";
        return EXIT_FAILURE;
    }
    std::cout << "Test for linked list done. All good!\n";
    return EXIT_SUCCESS;
}
