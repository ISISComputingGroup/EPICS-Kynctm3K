#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

#include "keyence.h"

/**
 *  Parse the response from the Keyence Optical micrometer.
 */
static long keyence_status_parse(aSubRecord *prec) 
{
	return keyence_status_parse_impl(prec);
}

epicsRegisterFunction(keyence_status_parse); /* must also be mentioned in asubFunctions.dbd */
