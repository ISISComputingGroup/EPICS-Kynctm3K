#include <string.h>
#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <menuFtype.h>
#include <errlog.h>
#include <epicsString.h>
#include <epicsExport.h>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "keyence.h"


/**
 *  
 */
long keyence_status_parse_impl(aSubRecord *prec) 
{
    prec->vala = prec->a;
    return 0; /* process output links */
}
