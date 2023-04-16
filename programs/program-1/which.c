#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) { // also known as: char* argv[]
	int file_exists(char* path); // declarnig function in header so compiler notices it
	// retrieve all paths
	char *p = getenv("PATH");
	//printf("PATH: %s\n", p);

	char *item = strtok(p, ":"); // split paths by ':'
	char *dir[10] = {NULL};
	char flag = 0;
	char *files[10] = {NULL};
	int amt_files = 0;
	int amt_dir = 0;
	int exit_status = 0;

	while(item != NULL){
		dir[amt_dir++] = item;
		item = strtok(NULL, ":");
	}

	//for(int i = 0; i < 10; i++){ // printing all paths 
	//	if(dir[i] != NULL){
        //        	printf("%s\n", dir[i]);
	//	}
        //  }

	// splitting the user input and comparing to -a
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "-a") == 0){ // using strcmp() to compare potential flags to "-a"
			flag = 1;
		} else if(argv[i][0] == '-'){ // able to compare chars without strcmp()
			flag = 2;
		} else { // counting the amount of files the user has input and storing them in an array
			files[amt_files++] = argv[i];
		}
	}
	
	// outputting flag detection
	if(flag == 1){
		printf("Flag '-a' detected\n");
	} else if(flag == 2){
		printf("Unknown flag detected\n");
		exit_status = 2;
	} else {
		printf("No flags detected\n");
	}

	// concatinating file names to the end of the paths
	for(int j = 1; j < amt_files; j++){ // iterating through files, starting at one to ignore the command used to execute the program
		int not_exist = 0; // counter to see how many files don't exist 
		for(int i = 0; i < amt_dir; i++){ // iterating through directories
			char *cat_str = malloc(strlen(dir[i]) + '/' + strlen(files[j]) + 1); // freeing up space for the two chars and an extra two spaces, one for '/' and one for the extra bit of memory at the end
			strcpy(cat_str, dir[i]); // copying the first *char to allocated space in memory
			strcat(cat_str, "/"); // concatinating restof hte *chars to the open space in memory
			strcat(cat_str, files[j]);
			//printf("%s\n", cat_str);
			if(file_exists(cat_str)){
				printf("  '%s' is executable\n", files[j]);
				printf("\tExecutable file '%s' found in the path '%s'\n", files[j], cat_str); // only printing if it finds an executable file
				if(flag != 1){
					break;	
				}
			}
		if((i == amt_dir) && (not_exist == amt_dir) && (exit_status != 2)){ // changing exit_status depending on if a file does not exist 
			exit_status = 1; 
		}	
		free(cat_str);
		}
	}

	return exit_status;

}

	int file_exists(char* path){
		if(access(path, X_OK) == 0 && access(path, F_OK) == 0){
			return 1;
		} else {
			return 0;
		}
	}

