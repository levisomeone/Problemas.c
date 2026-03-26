#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 12001
#define BUFFER 1024

int main() {
    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[BUFFER];

    printf("Digite o produto: ");
    scanf("%s", buffer);

    sendto(sock, buffer, strlen(buffer), 0,
           (struct sockaddr*)&server, sizeof(server));

    int n = recvfrom(sock, buffer, BUFFER, 0, NULL, NULL);

    if(n < 0) {
        printf("Sem resposta (timeout)\n");
    } else {
        buffer[n] = '\0';
        printf("Resposta: %s\n", buffer);
    }

    close(sock);
    return 0;
}
