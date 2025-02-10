#include <winsock2.h>
#include "include/ping-khaldun.h"

int ping_khaldun() {
    WSADATA wsadata;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    hostent *server;
    char *server_ip;
    int count = 0;
    char buf[PING_BUFSIZE];

    result = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (result != NO_ERROR) {
        return 0;
    }
    
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return 0;
    }

    server = gethostbyname(khaldun_url);
    server_ip = inet_ntoa (*(struct in_addr *) *server->h_addr_list);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(server_ip);
    serv_addr.sin_port = TCP_PORT;

    result = bind(sock, (SOCKADDR *) &serv_addr, sizeof(serv_addr));
    if (bind_result = SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    DWORD timeout = 1500;
    int timeoutlen = sizeof(DWORD);
    result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, &timeoutlen);
    if (result == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    result = recv(sock, buf, PING_BUFSIZE, 0);
    result = (result < 1) ? 1 : 0;

    closesocket(sock);
    WSACleanup();
    return result;
}
