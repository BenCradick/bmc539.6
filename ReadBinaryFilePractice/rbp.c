#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[40];
    int number;
    float balance;
} acct_info_t;

int get_offset(int);
int main(){
    unsigned int num_records;
    char* offset;
    float balance;


    FILE* fp;
    fp = fopen("acct_info", "rb+");

    fseek(fp, sizeof(int), SEEK_SET);
    fread(&num_records, sizeof(int), 1, fp);
    
    printf("Enter record number:\t");
    fgets(offset, 5, stdin);
    if(atoi(offset) > num_records || atoi(offset) < 1){
        printf("Invalid record number\n");
        return -1;
    }
    else{
        fseek(fp, get_offset(atoi(offset)), SEEK_SET);
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