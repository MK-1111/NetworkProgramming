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
void read_until_delim(int,char *,char,int);
int get_current_balance();
void set_current_balance(int);

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

void commun(int sock)
{
    char buf[BUF_SIZE];
    int balance=get_current_balance();

    read_until_delim(sock,buf,'_',BUF_SIZE);
    balance+=atoi(buf); //預け入れ金額をプラス
    read_until_delim(sock,buf,'_',BUF_SIZE);
    balance-=atoi(buf);  //引き出し金額をマイナス

    set_current_balance(balance);

    sprintf(buf,"%d_",balance);
    if(send(sock,buf,strlen(buf),0)!=strlen(buf))
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

void read_until_delim(int sock,char *buf,char delimiter,int max_length){
    int len_r=0;      //受信文字数
    int index_letter=0;   //受信文字数の合計

    while(index_letter<max_length-1){
        //1文字だけ受信

        if((len_r=recv(sock,buf+index_letter,1,0))<=0){
            //エラー
            printf("接続が切れました\n");
            return;
        }

        if(buf[index_letter]==delimiter)
        //区切り文字を受信ー＞ループを抜ける
        break;
        else index_letter++;
    }
}

int get_current_balance(){
    return 1000000;
}

void set_current_balance(int new_balance){
    return;
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