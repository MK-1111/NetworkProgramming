#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DiewithError(char *);
int prepare_client_socket(char *, int);
void my_scanf(int);
void commun(int);

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

void commun(int sock)
{
    char buf[BUF_SIZE];
    int len_r;
    len_r = recv(sock, buf, BUF_SIZE, 0);
    if (len_r <= 0)
        DieWithError("recv() failed");
    buf[len_r] = '\0';
    printf("%s\n", buf);
    if (send(sock, buf, strlen(buf), 0) != strlen(buf))
        DieWithError("send() sent a message of unexpected bytes");
}

int prepare_client_socket(char *ipaddr, int port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        DieWithError("socket() failed");

    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet(INADDR_ANY);
    target.sin_port = htons(port);

    bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

    return servSock;
}

int main(int argc, char **argv[])
{
    if (argc != 3)
        DieWithError("usage: ./client ip_address port");

    int sock = prepare_client_socket
}