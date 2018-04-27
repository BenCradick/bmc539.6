#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct
{
    char name[40];
    int number;
    float balance;
} acct_info_t;

int get_offset(int);
void name_search(char **, FILE*);
int main(int argc, char **argv){
    unsigned int num_records;
    char offset[5];
    memset(offset, '\0', sizeof(offset));
    int record;
    float balance;


    FILE* fp;
    fp = fopen("acct_info", "rb+");

    fseek(fp, sizeof(int), SEEK_SET);
    fread(&num_records, sizeof(int), 1, fp);

    if(argv[1] != NULL){
        if(! strcmp(argv[1], "-v")){
            name_search(argv,fp);
            return 0;
        }
        strcpy(offset, argv[1]);
        record = atoi(offset);
    }

    else{
    printf("Enter record number:\t");
    fgets(offset, 5, stdin);
    record = atoi(offset);

    }
    if(record > num_records || record < 0){
        printf("Invalid record number\n");
        return -1;
    }
    else{
        fseek(fp, get_offset(record), SEEK_SET);
        fread(&balance, sizeof(float), 1, fp);
    }
    printf("%f\n", balance);
    fclose(fp); 
    return 0;
}

int get_offset(int record){
    int bytes = 0;
    bytes += 2*sizeof(unsigned int);
    bytes += record*sizeof(acct_info_t);
    bytes += sizeof(char[40]);
    bytes += sizeof(int);
    return bytes; 

}
void name_search(char **names, FILE* fp){
    int num_records;
    int i = 0;
    char name[40];

    regex_t preg;
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int rc;

    memset(name, 0, sizeof(name));
    fseek(fp, sizeof(int), SEEK_SET);
    fread(&num_records, sizeof(int), 1, fp);
    fseek(fp, 2*sizeof(int), SEEK_SET);
    
    for(i = 0; i <= num_records; i++){
        fread(name, sizeof(name), 1, fp);
        if(0 != (rc = regcomp(&preg, names[2], 0))){
            exit(EXIT_FAILURE);
        }
        if (0 == (rc = regexec(&preg, name, nmatch, pmatch, 0))){
            printf("A match for %s found on record %d\n", name, i);
        }
        fseek(fp, sizeof(acct_info_t) - sizeof(name), SEEK_CUR);
    }
}