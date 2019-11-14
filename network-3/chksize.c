#include <stdio.h>

struct money2
{
    int deposit;
    unsigned short numDeps;
    int withdraw;
    unsigned short numWithdraw;
};

struct money3
{
    int deposit;
    int withdraw;
    unsigned short numDeps;
    unsigned short numWithdraw;
};

struct money4
{
    long long a;
    int b;
    int c;
    int d;
};

int main(int argc, char *argv[])
{
    printf("int=%lu　バイト\n", sizeof(int));
    printf("unsigned short=%lu　バイト\n", sizeof(unsigned short));
    printf("unsigned long=%lu　バイト\n", sizeof(unsigned long));
    printf("unsigned long long=%lu　バイト\n", sizeof(unsigned long long));
    printf("char=%lu　バイト\n", sizeof(char));
    printf("double=%lu　バイト\n", sizeof(double));
    printf("float=%lu　バイト\n", sizeof(float));
    printf("%lu　バイト\n", sizeof(struct money2));
    printf("%lu　バイト\n", sizeof(struct money3));
    printf("%lu　バイト\n", sizeof(struct money4));
    return 0;
}