#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DiewithError(char *);
int prepare_server_socket(int);
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

int prepare_server_socket(int port)
{
    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock < 0)
        DieWithError("socket() failed");

    struct sockaddr_in servAddress;
    servAddress.sin_family = AF_INET;
    servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddress.sin_port = htons(80);

    bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

    return servSock;
}

int main(int argc, char **argv)
{
    int servSock = prepare_server_socket(10001);
    struct sockaddr_in servAddress;
    struct sockaddr_in clientAddress;
    int cliSock;
    unsigned int szClientAddr;

    listen(servSock, 5);
    while (1)
    {
        szClientAddr = sizeof(clientAddress);
        cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr);
        commun(cliSock);
        close(cliSock);
    }
    close(servSock);
    return 0;
}