/*Program to convert from human-readable 
*time to epoch time
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //for converting date to epoch time
#include <string.h>
#include "rundb.d"

/*method to convert from human-readable to epoch time
  step 1: parse mm/dd/yyyy into month, day, and year
  step 2: set equal to struct tm variables (i.e.)
  step 3: copy tm struct values back into myData[].date[]
*/
void structToEpochTime (int num) {
	struct tm t;
	int i;
	int rc;
	char tmp_date[40];
	int year, month, day;

	strcpy(tmp_date, myData[num].date);
   
	//for loop to iterate through pointer to DataRec struct created in main
	for (i=0; i < strlen(tmp_date); i++) {
      if (tmp_date[i] == '/')
        	tmp_date[i] = ' ';
	}
	sscanf(tmp_date, "%d %d %d", &month, &day, &year);
    memset(&t, 0, sizeof(t)); //set struct tm variables to 0
	t.tm_year = year -1900;
	t.tm_mon = month -1;
	t.tm_mday = day;
	myData[num].edate = mktime(&t); //set epoch	
}

/*function to change a single string to epoch time*/
int stringToEpochTime (char *my_date) {
	struct tm t;
	int i;
	int rc;
	int year, month, day;
   
	//for loop to iterate through pointer to DataRec struct created in main
	for (i=0; i < strlen(my_date); i++) {
      if (my_date[i] == '/')
        	my_date[i] = ' ';
	}
	sscanf(my_date, "%d %d %d", &month, &day, &year);
    memset(&t, 0, sizeof(t)); //set struct tm variables to 0
	t.tm_year = year -1900;
	t.tm_mon = month -1;
	t.tm_mday = day;
	return mktime(&t); //set epoch	
}