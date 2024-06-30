#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

// #pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
#define CURRENT_LOCATION_FILE "../bus_reservation_system/database/location.log"


int count = 1;


char booked[30][2] = {"A1", "A2"};

void send_response(int mode, SOCKET client, char http_request[BUFFER_SIZE])    {
        
        // printf("\nRequest number: %d\n", count);
        // printf("\nMode: %d\n", mode);
        FILE* target_file;
        if (mode == 1)  {
            target_file = fopen("book.html", "r");
        }  else if (mode == 2)  {
            send(client, *booked, BUFFER_SIZE, 0);
        } else if (mode == 3)    {
            target_file = fopen(CURRENT_LOCATION_FILE, "r");
        } else    {
            target_file = fopen("index.html", "r");
        }  
        
        char http_response[BUFFER_SIZE] = {0};
        fread(http_response, 1, BUFFER_SIZE, target_file);
        send(client, http_response, BUFFER_SIZE, 0);
        // send(client, "hi", BUFFER_SIZE, 0);
        fclose(target_file);
        
        shutdown(client, 2); 
        count++; 
}

int main()  {
    int count = 0;
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    struct addrinfo *result = NULL;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = htons(SERVER_PORT);
    bind(sock, (struct sockaddr *)&address, sizeof(address));
    listen(sock, 100);
    printf("listen\n");

    while (1){
    SOCKET client = accept(sock, 0,0);
    
    char http_request[BUFFER_SIZE];
    
    recv(client, http_request, BUFFER_SIZE, 0);
    // printf("%s\n\n\n\n", http_request);
    
    

    if (strstr(http_request, "/update_location?location=") == NULL)
        send_response(0, client, http_request);
    else    {
        printf("\nUPDATE LOCATION REQUEST");
        strtok(http_request, "=");
        // strtok(NULL, "=");
        char *data = strtok(NULL, " ");
        FILE *location = fopen(CURRENT_LOCATION_FILE, "w");
        // fprintf(location, "HTTP/1.1 200 OK\nContent-type: text/html\n\n%s", data);
        fprintf(location, "%s", data);
        fclose(location);
        send_response(0, client, http_request);
    } 

    // if (strstr("/update_location/location=", http_request) != NULL) {
    //     printf("\nlocation update");
    //     char *data = strtok(http_request, "=");
    //     data = strtok(NULL, " ");
    //     // FILE *location = fopen("../bus_reservation_system/database/location.log", "w");
    //     FILE *location = fopen("location.log", "w");
        
    //     fprintf(location, "HTTP/1.0 200 OK\nContent-type: text/html\n\n%s", data);
    //     fclose(location);
    //     send_response(3, client, http_request); 
    // }   else
    //         send_response(0, client, http_request);



    
  
    
    }
}