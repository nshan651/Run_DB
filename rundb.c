/* [Running Workout Database]
*--database to track running workouts--
* --by Nick Shannon--
* --11/22/2020--
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for string cmps and sizes
#include <time.h> //for converting date to epoch time
#define DB "runningData.csv" //database name
/*exception handling using perror() library function*/
#define TRY(a)  if (!(a)) {perror(#a);exit(1);} 
#define TRY2(a) if((a)<0) {perror(#a);exit(1);}
/*max number of entries in the db and max line length to read*/
#define MAX_ELEMENTS 10000 
#define MAX_LINE_LEN 250   
/*define boolean values*/
#define TRUE 1
#define FALSE 0
typedef unsigned char BOOL;

/*struct to contain each data record*/
struct DataRec {
	float distance;		
	float timeInMinutes;
	char date[25];
	time_t edate;
};

/*create an array of structs*/
struct DataRec myData[MAX_ELEMENTS];
struct DataRec sortedData[MAX_ELEMENTS];

/*enum for list of actions to take*/
enum {CREATE, REMOVE, DISPLAY_SORT, SHOW_LATEST, CLEAR};

/*func prototypes*/
int readDB(FILE *f); //func to read db
int writeDB(FILE *f); //func to write to db
static void toEpochTime(int idx); //func to convert from human-readable to epoch file
static int check_date(char *c); //func to validate date entered via terminal
static void mergeSort(int arry[], int left, int right); //func to sort entries
static void merge(int arry[], int left, int middle, int right); //helping method for mergeSort
static void printArray(int arry[], int size); // <---DELETE LATER

/*static vars*/
static char newDistance[25], newTime[25], newDate[25]; //temp vars to scan to
static int idx = 0; //index of struct
static int rc;	//return code
static char flag = 'c'; // flag to continue
static char line[MAX_LINE_LEN]; // string to hold line number

/*main*/
int main(int argc, char **argv) {
	int i, j;
	//list of commands accepted by the command line
	const char *cmds[] = {"-create", "-remove", "-display_sort", "-show_latest", "-clear", NULL}; 
	
	//open csv file to be read
	FILE *f;
	TRY(f = fopen(DB, "r"));
	//Exception thrown with fewer than 2 command line args
	if (argc < 2) {
		usage: printf("Usage: %s [commands]\n"
			"-create  Create one or more entries\n"
			"-remove  Remove an entry\n"
			"-display_sort  Display by a certain column\n"
			"-show_latest  Show the most recent entry\n"
			"-clear Clear the database", argv[0]);
			fclose(f);
			return 0; 
	}

	//function to read and copy db records to struct array
	readDB(f);
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
				/*
				printf("Enter a distance in mi:\n");
				scanf("%s", &newDistance);
				printf("Enter a time in min:\n");
				scanf("%s", &newTime);
				*/
				printf("Enter a date:\n");
				scanf("%s", &newDate);
				
				//validation
				if (check_date(newDate)) {
					//set struct values if date is valid
					/*debug mode, not taking time/distance
	    			myData[idx].distance = atof(newDistance);
	    			myData[idx].timeInMinutes = atof(newTime);
	    			*/
					myData[idx].distance = 1;
	    			myData[idx].timeInMinutes = 1;
	    			strcpy(myData[idx].date, newDate);
	    			toEpochTime(idx);
	    			idx++;	//goto next struct index
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
			printf("Remove an entry\n");
			printf("oops, nothing here :(\n");
		break;

		//sort by distance and output to terminal
		case DISPLAY_SORT:
			printf("Display sorted entries\n");
			printf("oops, nothing here :(\n");
		break;

		//show most recent entry
		case SHOW_LATEST:
			printf("Show most recent entry\n");
			printf("oops, nothing here :(\n");
		break;

		//clears the entire database
		case CLEAR:
			flag = '\0';
			printf("WARNING: all entries in the database will be deleted\n");
			printf("press 'c' to continue:\n");
			scanf("%c", &flag);
			idx = 0;	//set the index of the struct to zero so no entries are written
		break;
		
		//defaults to an error message
		default: 
			printf("\nUnknown command\n");
			goto usage;
	} //end switch

	//open file to write
	f = fopen(DB, "w");
	
	//create an array of epoch dates for sorting
	int epoch_list[idx];
	for (i =0; i < idx; i++) {
		epoch_list[i] = myData[i].edate;
	}
	
	mergeSort(epoch_list, 0, idx-1);

	//copy myData values to sortedData based on epoch_list order
	for (i =0; i < idx; i++) {
		for (j =0; j < idx; j++) {
			if (epoch_list[i] == myData[j].edate) {
				sortedData[i].edate = myData[j].edate;
				sortedData[i].distance = myData[j].distance;
				sortedData[i].timeInMinutes = myData[j].timeInMinutes;
				strcpy(sortedData[i].date, myData[j].date);
			}
		}
	}
	//copy sorted struct back into original struct
	for (i =0; i < idx; i++) {
		 myData[i].edate = sortedData[i].edate;
		 myData[i].distance = sortedData[i].distance;
		 myData[i].timeInMinutes = sortedData[i].timeInMinutes;
		 strcpy(myData[i].date, sortedData[i].date);
	}

	//write myData values to excel
	writeDB(f);
	fclose(f);

} //end main

/*TEST METHOD function to print an array - DELETE LATER*/
static void printArray(int arry[], int size) {
	int i;
	for (i =0; i < size; i++) {
		printf("%d ", arry[i]);
	}
	printf("\n");
}

/*function to sort an array using merge sort*/
static void mergeSort(int arry[], int left, int right) {
	if (left < right) {
		//equivalent to (left+right)/2 but avoids overflow
		int middle = left + (right - left) / 2; 
		
		//sort first and second halves
		mergeSort(arry, left, middle);
		mergeSort(arry, middle + 1, right);

		//merge the two halves
		//merge(arry, left, middle, right);
		int i,j,k;	//indexes for right, left, and middle
		int size_left = middle - left + 1; //left partition size
		int size_right = right - middle;	//right partition size
		//temp arrays
		int L[size_left], R[size_right];
		//copy new data into left and right arrays (L[] and R[])
		for (i =0; i < size_left; i++) {
			L[i] = arry[left + i]; 
		}
		for (j =0; j < size_right; j++) {
			R[j] = arry[middle + 1 + j];
		}
		//merge right and left arrays back into arry[]
		i =0;
		j =0;
		k =left;
		while (i < size_left && j < size_right) {
			if (L[i] <= R[j]) {
				arry[k] = L[i];
				i++;
			}
			else {
				arry[k] = R[j];
				j++;
			}
			k++;
		}
		//copy any remaining elements of either the right or left arrays
		while (i < size_left) {
			arry[k] = L[i];
			i++;
			k++;
		}
		while (j < size_right) {
			arry[k] = R[j];
			j++;
			k++;
		}
	}
}

/*method to convert from human-readable to epoch time
  step 1: parse mm/dd/yyyy into month, day, and year
  step 2: set equal to struct tm variables (i.e.)
  step 3: copy tm struct values back into myData[].date[]
*/
static void toEpochTime (int idx) {
	struct tm t;
	int i;
	int rc;

	char tmp_date[40];
	int year, month, day;

	strcpy(tmp_date, myData[idx].date);
   
	//for loop to iterate through pointer to DataRec struct created in main
	for (i=0; i < strlen(tmp_date); i++) {
      if (tmp_date[i] == '/')
        tmp_date[i] = ' ';
	}
	sscanf(tmp_date, "%d %d %d", &month, &day, &year);

    memset(&t, 0, sizeof(t)); //set struct tm variables to 0
	t.tm_year = year - 1900;
	t.tm_mon = month -1;
	t.tm_mday = day;
	myData[idx].edate = mktime(&t); //set epoch	
}

/*function to check for a valid date*/
int check_date (char *date) {
	return ((date[2] == '/') && (date[5] == '/') && (strlen(date) == 10));
}

/*function to write to db*/
int writeDB(FILE *f) {
	int i;
	fprintf(f, "_Distance_,_Time_,_Date_\n");	//column headers
	for (i = 0; i < idx; i++) {
		fprintf(f,"%f,%f,%s,%d\n",myData[i].distance,myData[i].timeInMinutes,
			                      myData[i].date, myData[i].edate);
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
    			myData[idx].distance = atof(newDistance);
    			myData[idx].timeInMinutes = atof(newTime);
    			strcpy(myData[idx].date, newDate);
    			toEpochTime(idx);
    		   idx++;
    		}   
    	}	
    }
} //end readDB
    