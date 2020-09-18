#include <string.h>
#include <malloc.h>
#include <stdio.h>

char* flat_text(char** words, int n){
	char* line = NULL;
	int current_index = 0;

	for(int i=0; i<n; i++){
		int len = strlen(words[i]);
		line = realloc(line, sizeof(line)+sizeof(words[i]));
		if (!line){
			return NULL;
		}
		strcpy(line+current_index, words[i]);
		current_index += len;
	}
	return line;
}

int main1(){
	char* my_array[] = {"hello","world","1234","ASDA"};
	char* p = flat_text(my_array, 4);
	if (p != NULL){
		printf("\n%s\n", p);
		free(p);
	}
	return 0;
}

