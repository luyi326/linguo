#ifndef SENTENSE_STATUS_H
#define SENTENSE_STATUS_H

struct senStatus{
    bool notEmpty;
    //parser status
    bool gparseInited;
    bool gparseBChecked;
    bool POSTagged;
    bool gparsed;
    //lexer status
    bool lparsed;
};

void senStatus_init(senStatus&);

#endif //SENTENSE_STATUS_H