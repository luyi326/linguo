#include <iostream>
#include "sentense_status.h"

void senStatus_init(senStatus & senS){
    senS.notEmpty = false;
    senS.gparseInited = false;
    senS.gparseBChecked = false;
    senS.POSTagged = false;
    senS.gparsed = false;
    senS.lparsed = false;
}