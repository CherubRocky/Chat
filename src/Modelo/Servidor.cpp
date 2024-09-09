#include "Servidor.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
using namespace std;

Servidor::Servidor() {
    socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in dirServidor;
    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons(1024);
    cout << "oal" << endl;
    dirServidor.sin_addr.s_addr = INADDR_ANY;
    bind(socketServidor, (struct sockaddr*)&dirServidor, sizeof(dirServidor));
    cout << "Puerto asignado a este servidor: " << ntohs(dirServidor.sin_port) << endl;
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &dirServidor.sin_addr, ip, INET_ADDRSTRLEN);
    cout << "IP enlazada al servidor: " << ip << endl;
}

void Servidor::manejarCliente(int socketCliente) {

}

void Servidor::servir() {
    Servidor::aceptarConnection();
}

void Servidor::aceptarConnection() {
    listen(socketServidor, 5);
    int contador = 0;
    while (true) {
        int socketCliente = accept(socketServidor, nullptr, nullptr);
        thread hiloCliente(&Servidor::manejarCliente, this, socketCliente);
        hiloCliente.detach();
        cout << "Cliente " << ++contador << " conectado" << endl;
        cout.flush();
    }
}

void Servidor::procesaCosa() {
    cout << "conectado" << endl;
    listen(socketServidor, 5);
    int socketCliente = accept(socketServidor, nullptr, nullptr);
    char buffer[1024] = {0};
    recv(socketCliente, buffer, sizeof(buffer), 0);
    cout << "Mensaje del cliente: " << buffer << endl;
    close(socketServidor);
}
