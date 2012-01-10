/********************************************************
                This is the grammer parser 
                    UNDER CONSTRUCTION
                                        -Yi
 ********************************************************/
#ifndef GRAMMER_PARSER_H
#define GRAMMER_PARSER_H

#include "../basicTypes.h"

enum grapar_symbol_status{
    grapar_symbol_single,
    grapar_symbol_multiple
};// deprecated 

class graParser{
public:
    graParser();
    void startParse(GSentence &, GDataBase &);
     void wordCheck(GSentence&);
private:
    inline void init(GSentence&);
    inline bool basicCheck(GSentence&);
//    inline void wordCheck(GSentence&);
    void tagWithWordNet(GSentence&, GDataBase&);
    //inline grapar_symbol_status checkSymbol(GSentence&);
};

#endif //GRAMMER_PARSER_H
