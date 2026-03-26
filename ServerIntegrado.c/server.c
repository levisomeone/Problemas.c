#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>

#define TCP_PORT 12000
#define UDP_PORT 12001
#define BUFFER 1024

typedef struct {
    char nome[50];
    float preco;
} Produto;

Produto produtos[] = {
    {"ARROZ", 5.50},
    {"FEIJAO", 7.20},
    {"MACARRAO", 4.00},
    {"LEITE", 3.80},
};

int total_produtos = 4;
pthread_mutex_t lock;

float buscar_preco(char *nome) {
    pthread_mutex_lock(&lock);

    for(int i = 0; i < total_produtos; i++) {
        if(strcmp(produtos[i].nome, nome) == 0) {

            float variacao = ((rand() % 100) / 100.0) - 0.5;
            float preco = produtos[i].preco + variacao;

            pthread_mutex_unlock(&lock);
            return preco;
        }
    }

    pthread_mutex_unlock(&lock);
    return -1;
}


void *tcp_client(void *arg) {
    int client_sock = *(int*)arg;
    free(arg);

    char buffer[BUFFER];
    read(client_sock, buffer, BUFFER);

    float preco = buscar_preco(buffer);

    char resposta[BUFFER];

    if(preco < 0)
        sprintf(resposta, "Produto nao encontrado");
    else
        sprintf(resposta, "Preco: R$ %.2f", preco);

    write(client_sock, resposta, strlen(resposta));

    close(client_sock);
    return NULL;
}
//TCp:
void *tcp_server(void *arg) {
    int server_sock, client_sock;
    struct sockaddr_in server, client;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(TCP_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr*)&server, sizeof(server));
    listen(server_sock, 5);

    printf("TCP rodando na porta %d\n", TCP_PORT);

    while(1) {
        socklen_t c = sizeof(client);
        client_sock = accept(server_sock, (struct sockaddr*)&client, &c);

        int *new_sock = malloc(sizeof(int));
        *new_sock = client_sock;

        pthread_t t;
        pthread_create(&t, NULL, tcp_client, new_sock);
        pthread_detach(t);
    }
}

//UDp:
void *udp_server(void *arg) {
    int sock;
    struct sockaddr_in server, client;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(UDP_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server, sizeof(server));

    printf("UDP rodando na porta %d\n", UDP_PORT);

    char buffer[BUFFER];

    while(1) {
        socklen_t len = sizeof(client);

        int n = recvfrom(sock, buffer, BUFFER, 0,
                         (struct sockaddr*)&client, &len);

        buffer[n] = '\0';

        float preco = buscar_preco(buffer);

        char resposta[BUFFER];

        if(preco < 0)
            sprintf(resposta, "Produto nao encontrado");
        else
            sprintf(resposta, "Preco: R$ %.2f", preco);

        sendto(sock, resposta, strlen(resposta), 0,
               (struct sockaddr*)&client, len);
    }
}


int main() {
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);

    pthread_t tcp, udp;

    pthread_create(&tcp, NULL, tcp_server, NULL);
    pthread_create(&udp, NULL, udp_server, NULL);

    pthread_join(tcp, NULL);
    pthread_join(udp, NULL);

    return 0;
}
