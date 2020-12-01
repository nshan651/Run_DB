/*Data file for storing global data
*--creates storage class for DataRec struct
*--initializes global DataRec struct once in rundb.c
*--used instead of declaring an extern struct for each file
*/
#include "rundb.h"

/*create an array of structs as a STORAGE_CLASS*/
STORAGE_CLASS struct DataRec myData[MAX_ELEMENTS];