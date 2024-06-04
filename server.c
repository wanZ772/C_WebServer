#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>

// #pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 8080

int main()  {
    int count = 1;
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    struct addrinfo *result = NULL;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = htons(SERVER_PORT);
    bind(sock, &address, sizeof(address));
    listen(sock, 100);
    printf("listen");

    while (1){
    SOCKET client = accept(sock, 0,0);
    
    char buffer[2560];
    
    recv(client, buffer, 2560, 0);
    printf("%s", buffer);
    char *test = strtok(buffer, "/seats?");
    char *argue[19];
    int  i = 0;
    while (test != NULL)    {
        argue[i++] = test;
        test = strtok(NULL, "/seats"); 
    }
    // if (memcmp(buffer, "GET / ", 6) == 0)   {
        printf("%s", argue[2]);
        printf("\nRequest number: %d\n", count);
        FILE* target_file = fopen("index.html", "r");
        char file_data[2560] = {0};
        fread(file_data, 1, 2560, target_file);
        send(client, file_data, 2560, 0);
        fclose(target_file);
        
        shutdown(client, 2); 
        count++;   
    // } 
    
    }
}