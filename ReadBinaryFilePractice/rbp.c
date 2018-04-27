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
    int a = get_whence(5);
    printf("%d\n", a);
    //printf("%d\n", sizeof(acct_info_t));
    //printf("4(sizeof(char[40]): %d + sizeof(int): %d + sizeof(float): %d) + 2(sizeof(unsigned int)) = %d\n", sizeof(char[40]), sizeof(int), sizeof(float), sizeof(unsigned int), a);
    return 0;
}

int get_whence(int record){
    int bytes = 0;
    printf("%d\n",bytes);
    bytes += 2*sizeof(unsigned int);
    printf("%d\n", bytes);
    bytes += record*sizeof(acct_info_t);
    printf("%d\n", bytes);
    return bytes; 

}