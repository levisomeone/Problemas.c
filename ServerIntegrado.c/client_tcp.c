#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12000
#define BUFFER 1024

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Erro de conexao\n");
        return 1;
    }

    printf("Digite o produto: ");
    scanf("%s", buffer);

    write(sock, buffer, strlen(buffer));
    read(sock, buffer, BUFFER);

    printf("Resposta: %s\n", buffer);

    close(sock);
    return 0;
}
