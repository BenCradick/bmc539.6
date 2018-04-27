#include <stdio.h>

typedef struct
{
    char name[40];
    int number;
    float balance;
} acct_info_t;

int get_whence(int);
int main(){
    FILE* fp;
    fopen("acct_info", "rb");
    fseek(fp,)
    return 0;
}

int get_whence(int record){
    int bytes = 0;
    bytes += 2*sizeof(unsigned int);
    bytes += record*sizeof(acct_info_t);
    bytes += sizeof(char[40])
    bytes += sizeof(int);
    return bytes; 

}