#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
int pair_count=0;
struct pair {
    char *key;
    char *value;
};
struct pair hash_table[MAX_SIZE];
int hash(char *key) {
    int sum = 0;
    for (int i = 0; i < strlen(key); i++) {
        sum += key[i];
    }
    return sum % MAX_SIZE;
}
void add_pair(char *key, char *value) {
    int index = hash(key);
    hash_table[index].key = strdup(key);
    hash_table[index].value = strdup(value);
	pair_count++;
}
char *get_value(char *key) {
    int index = hash(key);
    return hash_table[index].value;
}
int update_value(char *key, char *value) {
    int index = hash(key);
    hash_table[index].value = strdup(value);
    return 1;
}
int main () {
	char str[500];
	char newstr[500];
	char cleanstr[500];
	char something[500];
	char array[2000][2000];
	char arraygood[2000][2000];
	char *res;
	char *token;
	FILE *ptr;
	int clean_count = 0;
	int i = 0;
	int f = 0;
	int words = 0;
	int noofwords = 0;
	int result = 0;
	int result2 = 0;
	int result3 = 0;
	ptr = fopen("fluence-energy-report.bak","r");
	if (ptr == NULL) {
		printf("ERROR  | file called skyworks_earnings.txt is not found");
		return 1;
	}
	while ( fgets(str,500,ptr) != NULL) { // line by lin	
		str[strlen(str) -1 ] ='\0';
		res = strtok(str," ");
		while (res != NULL) {	// word by word
			strcpy(newstr,res);
			res = strtok(NULL," ");
			for (i = 0; i< strlen(newstr) ; i++) { //char by char
				if (newstr[i] != '.' && newstr[i] != ';' &&  newstr[i] != ':' && newstr[i] != ','  &&	 newstr[i] != '/' && newstr[i] != '|') { //replace punctuation
					cleanstr[clean_count] = newstr[i];
					clean_count++;
				}	 
			}
			cleanstr[clean_count] = '\0';
			printf("%s",cleanstr); // str with no punctuation
			clean_count = 0;
			if (get_value(cleanstr) == NULL) {
				add_pair(cleanstr,"1");
		        	strcpy(arraygood[words],cleanstr);
				words++;
			}else {
				f = atoi(get_value(cleanstr));
				sprintf(something,"%d",f+1);		
				update_value(cleanstr,something);
			}
			noofwords++;
		}	
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < pair_count ; i++){
		printf("%d. %s  %s  ",i+1,arraygood[i],get_value(arraygood[i]));
		if ( i != 0 ) {
			result = atoi(get_value(arraygood[i])); 
			result2 = result2 + result;
			printf("%d",result2);
		}
		printf("\n");
	}
	printf("Total Number of words are : %d\n",noofwords);
	fclose(ptr);
	return 0;
}
