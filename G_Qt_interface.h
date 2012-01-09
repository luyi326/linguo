#ifndef G_QT_INTERFACE_H
#define G_QT_INTERFACE_H
#include "basic.h"
#include <iostream>
using namespace std;

class GQt{
public:
    GQt();
    ~GQt();
    string getAnswer(string);
private:
    GDataBase * dic;
    GSentence * input;
    string output;
};

#endif // G_QT_INTERFACE_H
