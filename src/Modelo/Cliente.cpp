#include "Servidor.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Cliente.h"
using namespace std;

Cliente::Cliente() {
    socketCliente = socket(AF_INET, SOCK_STREAM, 0);


}

void Cliente::conectarse(string ip, int puerto) {
    sockaddr_in addrServidor;
    addrServidor.sin_family = AF_INET;
    addrServidor.sin_port = htons(puerto);
    addrServidor.sin_addr.s_addr = inet_addr(ip.c_str());
    connect(socketCliente, (struct sockaddr*)&addrServidor, sizeof(addrServidor));
    cout << "conexión exitosa." << endl;
}

void Cliente::enviarMensaje(string mensaje) {
    send(socketCliente, mensaje.c_str(), strlen(mensaje.c_str()), 0);
}
