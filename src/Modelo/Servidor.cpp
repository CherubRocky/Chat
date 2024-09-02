#include "Servidor.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

Servidor::Servidor() {
    socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in dirServidor;
    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons(8080);
    dirServidor.sin_addr.s_addr = INADDR_ANY;
    bind(socketServidor, (struct sockaddr*)&dirServidor, sizeof(dirServidor));
}

void Servidor::procesaCosa() {
    listen(socketServidor, 5);
    int socketCliente = accept(socketServidor, nullptr, nullptr);

    char buffer[1024] = {0};
    recv(socketCliente, buffer, sizeof(buffer), 0);
    cout << "Mensaje del cliente: " << buffer << endl;
    close(socketServidor);
}
