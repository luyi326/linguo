//
//  test_Cmd_Interface.cpp
//
//  Created by Lu Yi on 11/8/12.
//  Copyright 2011 UC Davis. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "basic.h"
#include "parser/grammerParser.h"
//#include "Grammer_analysis.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;
void bufferTest(GDataBase *);
int LinkedListTest();
int ListNodeTest();
void seperateWordTest();
void dbTest(GDataBase *);
//GDataBase dic;

int main(void){
    clock_t tik,tak;
    tik = clock();
    std::cout << "Trying to connect to database webster.db...";
    static GDataBase dic("./webster.db");
    if (!dic.is_open()) {
        std::cout << "Failed.\n";
    }else{
        std::cout << "Succeeded.\n";
        }
    ListNodeTest();
    LinkedListTest();
    GWord apple("apple");
    bufferTest(&dic);
    dbTest(&dic);
    apple.display();
    tak = clock();
    std::cout << "Time cost: " << 1000*(double)(tak - tik)/CLOCKS_PER_SEC << "ms." << std::endl;
    return EXIT_SUCCESS;
}
void dbTest(GDataBase * database){
    //GWord apple("apple");
    database->getWordType("apple");
    database->getWordType("pear");
}
void bufferTest(GDataBase * db){
    bool quit_flag = false;
    //char ** ptr;
    std::string inputBuffer = "";
    std::cout << "\n\n************************************************\nWelcome to the grammer helper test interface!\nThis interface is for test only!\n************************************************\nPlease input a complete sentence or phrase for testing:\n\n";
    if (db->is_open()) {
        cout << "Database is open\n";
    }else
        cout << "Database not availble\n";
    while (!quit_flag) {
        std::cout << "Test_input> ";
        std::getline(std::cin, inputBuffer);
        if (inputBuffer == "q" || inputBuffer == "Q"){
            quit_flag = true;
            break;
        }
        if ((quit_flag == false) && db->is_open()) {
            GSentence test;
            //test.make_empty();
            test.get_sentence(inputBuffer);
            //std::cout << "Finish scanning!\n";
            std::cout << "Total elements of buffer: " << test.length() << "\nTotal word: " << test.wordsCount() << "\nTotal symbols: " << test.symbolsCount() << std::endl;
            for (int i = 0; i < test.length(); i++) {
                if (test[i].GIdentifier() == id_GListNode_GWord) {
                    db->getWordType(test[i].content());
                }
            }
            test.printList(cout);
            cout << "\n";
            graParser gParser;
            gParser.wordCheck(test);
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
        test.printList(cout);
        test[0].setContent("That");
        test.printList(cout);
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
