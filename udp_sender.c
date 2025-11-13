#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char *message = "Hello Antonis UDP";

    printf("Starting UDP Client...\n");

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        return 1;
    }

    // Server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // change to target IP
    server.sin_port = htons(8888);                   // change to target port

    // Send message
    if (sendto(sock, message, strlen(message), 0,
               (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("sendto failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Message sent: %s\n", message);

    closesocket(sock);
    WSACleanup();
    return 0;
}
