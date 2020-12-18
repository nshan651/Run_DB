/* [Running Workout Database]
*--database to track running workouts--
* --by Nick Shannon--
* --11/22/2020--
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for string cmps and sizes
#include <time.h> //for converting date to epoch time
#include <math.h> //for floor() function used in binary search
/*DEFINE_DATA creates an external storage class that 
*initializes global struct; global struct located in rundb.d 
*data file
*/
#define DEFINE_DATA
#include "rundb.d"

/*enum for list of actions to take*/
enum {CREATE, REMOVE, DISPLAY_SORT, SEARCH, CLEAR};

/*static function prototypes*/
static void printArray(int arry[], int size); // <---DELETE LATER
static void displayDB(FILE *f);

/*static vars*/
static char newDistance[25], newTime[25], newDate[25], newMPH[25], newKPH[25]; //temp vars to scan to
static char mode[10]; //temp char to hold sorting mode
static int numOfEntries = 0; //index of struct
static int rc;	//return code
static char flag = 'c'; //flag to continue
static char line[MAX_LINE_LEN]; //string to hold line number
static int buf[MAX_ELEMENTS]; //buffer used to hold possible search matches
static int *buf_ptr; //pointer to buf index

/*main*/
int main(int argc, char **argv) {
	int i, j;

	buf_ptr = buf; //set buf pointer to the address of buf

	//list of commands accepted by the command line
	const char *cmds[] = {"-create", "-remove", "-display_sort", "-search", "-clear", NULL}; 
	
	//open csv file to be read
	FILE *f;
	TRY(f = fopen(DB, "r"));
	//Exception thrown with fewer than 2 command line args
	if (argc < 2) {
		usage: printf("Usage: %s [commands]\n"
			"  -create  Create one or more entries\n"
			"  -remove  Remove an entry\n"
			"  -display_sort  Display by a certain column\n"
			"  -search  Search for an entry by date\n"
			"  -clears  the database\n", argv[0]);
			fclose(f);
			return 0; 
	}
	//function to read and copy db records to struct array
	readDB(f);
	mergeSort(0, numOfEntries-1, "date/d");
    fclose(f);
	//cycle through each command
	for (i =0; cmds[i] && strcmp(argv[1], cmds[i]); i++); 
	//switch statement for each database operation
	switch(i) {
		//enter one or more record
		case CREATE:
			do {
				//get values from the keyboard
				printf("\nCreate an entry:\n");
				printf("Enter a distance in mi:\n");
				scanf("%s", &newDistance);
				printf("Enter a time in min:\n");
				scanf("%s", &newTime);
				printf("Enter a date:\n");
				scanf("%s", &newDate);
				
				//validation
				if (check_date(newDate)) {
					//set struct values if date is valid
	    			myData[numOfEntries].distanceInMiles = atof(newDistance);
	    			myData[numOfEntries].timeInMinutes = atof(newTime);
	    			strcpy(myData[numOfEntries].date, newDate);
	    			structToEpochTime(numOfEntries);
	    			numOfEntries++;	//goto next struct index
				} else {
					printf("not a valid date!\n");
					printf("enter a date in the form 'mm/dd/yyyy'\n");
				}
				printf("Press 'c' to continue:\n");
				scanf(" %c", &flag); //note that there MUST be a space before the %c specifier
				system("cls"); //clear screen			
			} while(flag == 'c');
		break;

		//remove a specified entry 
		case REMOVE:
			do {
				//get values from the keyboard
				printf("Enter date of entry to be removed\n");
				scanf("%s", &newDate);
				searchDB(newDate, numOfEntries, buf_ptr);
				//printArray(buf, 10); //<-- debug

				//allow user to choose which entry to remove (if multiple duplicates)
				int remove = -1;
				flag = 'c';
				while ( (buf[remove] >= 0) && (flag == 'c') ) {
					printf("Enter index of entry to be removed\n");
					printf("Enter '-1' to return\n");
					scanf("%d", &remove); 
					if (remove >= 0) {
						//overwrite the entry to be removed with the last entry
						myData[buf[remove]] = myData[numOfEntries-1];
						//subtract 1 from overall number of entries
						numOfEntries--;
						printf("Entry removed\n");
					} 
					else if (remove == -1) {
						printf("Returning to main program\n");
						break;
					}
					else {
						printf("Not a valid index\n");
					}
					printf("press 'c' to remove another entry on this date\n");
					scanf(" %c", &flag);
				}
				memset(buf,0,sizeof(buf)); //reset buffer array
				printf("Press 'c' to continue:\n");
				scanf(" %c", &flag); //note that there MUST be a space before the %c specifier
				system("cls"); //clear screen
			} while(flag == 'c');

		break;

		//sort by distance and output to terminal
		case DISPLAY_SORT:
			printf("Display sorted entries\n");
			printf("Choose how columns are sorted");
			printf("[Column_name]/[a or d]\n");
			scanf("%s", &mode);
			mergeSort(0, numOfEntries-1, mode);
			TRY(f = fopen(DB, "r"));
			displayDB(f); //print to terminal
			fclose(f);
		break;

		//search the database for a specific entry
		case SEARCH:
			do {
				printf("Enter a date\n");
				scanf("%s", &newDate);
				searchDB(newDate, numOfEntries, buf_ptr); //perform a search 
				memset(buf,0,sizeof(buf)); //reset buffer array
				printf("Press 'c' to continue:\n");
				scanf(" %c", &flag); //note that there MUST be a space before the %c specifier
				system("cls"); //clear screen
			} while(flag == 'c');
		break;

		//clears the entire database
		case CLEAR:
			flag = '\0';
			printf("WARNING: all entries in the database will be deleted\n");
			printf("press 'c' to continue:\n");
			scanf("%c", &flag);
			numOfEntries = 0;	//set the index of the struct to zero so no entries are written
		break;
		
		//defaults to an error message
		default: 
			printf("\nUnknown command\n");
			goto usage;
	} //end switch
	
	//open file to write
	f = fopen(DB, "w");
	//perform merge sort, default way to store data
	mergeSort(0, numOfEntries-1, "date/a");
	//write myData values to csv
	writeDB(f);
	fclose(f);

} //end main

/*TEST function to print an array - DELETE LATER*/
static void printArray(int arry[], int size) {
	int i;
	for (i =0; i < size; i++) {
		printf("%d ", arry[i]);
	}
	printf("\n");
}

/*function to check for a valid date*/
int check_date (char *date) {
	return ((date[2] == '/') && (date[5] == '/') && (strlen(date) == 10));
}

static void displayDB(FILE *f) {
	int i,j;
	printf("\n Distance(mi)  Time(min)      Date\n");
	printf("+------------+----------+---------------+\n");
	for (i =0; i < numOfEntries; i++) {
    	if (line[0] != '_') {
    		//replace commas with empty space
    		if (line[i] == ',') {
    				line[i] = ' ';
    		}
    		else {
    			printf("    %.2f        %.2f        %s\n",myData[i].distanceInMiles,myData[i].timeInMinutes,
			                      myData[i].date);
    		}	
    	}
    }
	
}

/*function to write to db*/
int writeDB(FILE *f) {
	int i;
	fprintf(f, "_Distance_,_Time_,_Date_,_mi/hour_,_Km/hour_,_min/mi_,_min/km_,_edate_\n");	//column headers
	for (i = 0; i < numOfEntries; i++) {
		fprintf(f,"%f,%f,%s,%f,%f,%f,%f,%d\n",myData[i].distanceInMiles,myData[i].timeInMinutes,
			                      myData[i].date, myData[i].edate,myData[i].mph, myData[i].kph,
			                      myData[i].minutesPerMile, myData[i].minutesPerKilometer, 
			                      myData[i].edate);
	}
}

/*function to read in existing db entries to the DataRec struct*/
int readDB(FILE *f) {
	int i;
	//read each line of csv; assign each row to index in struct array
    while ((f != NULL) && (fgets(line, MAX_LINE_LEN, f) != NULL)) {
    	if (line[0] != '_') {
    		//replace commas with empty space
    		for (i = 0; i < strlen(line); i++) {
    			if (line[i] == ',') {
    				line[i] = ' ';
    			}
    		}

    		//set i equal return value of sscanf (which will be no. of vars filled)
    		rc = sscanf(line, "%s %s %s", &newDistance, &newTime, &newDate);
    		if (rc == 3) {
    			myData[numOfEntries].distanceInMiles = atof(newDistance);
    			myData[numOfEntries].timeInMinutes = atof(newTime);
    			strcpy(myData[numOfEntries].date, newDate);
    			structToEpochTime(numOfEntries);
    			//derived entries
    			
    			myData[numOfEntries].mph = 
    				miles_per_hour(myData[numOfEntries].distanceInMiles, myData[numOfEntries].timeInMinutes);
    		   	myData[numOfEntries].kph = 
    		   		kilometers_per_hour(myData[numOfEntries].distanceInMiles, myData[numOfEntries].timeInMinutes);
    		   	myData[numOfEntries].minutesPerMile = 
    		   		min_per_mile(myData[numOfEntries].distanceInMiles, myData[numOfEntries].timeInMinutes);	
    		   	myData[numOfEntries].minutesPerKilometer = 
    		   		min_per_kilometer(myData[numOfEntries].distanceInMiles, myData[numOfEntries].timeInMinutes);
    		   	
    		   numOfEntries++;
    		}   
    	}	
    }
} //end readDB
    
