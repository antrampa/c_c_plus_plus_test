#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char buffer[1024];

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

    // Bind socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("UDP server listening on port 8888...\n");

    // Receive loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int recv_len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr *)&client, &client_len);

        if (recv_len == SOCKET_ERROR) {
            printf("recvfrom failed: %d\n", WSAGetLastError());
            return 1;
        }

        buffer[recv_len] = '\0';
        printf("Received from %s:%d :: %s\n",
               inet_ntoa(client.sin_addr),
               ntohs(client.sin_port),
               buffer);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
