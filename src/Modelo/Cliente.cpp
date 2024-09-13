#include "Servidor.h"
#include <cstring>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Cliente.h"
#include "../Controlador/AnalizadorJSON.cpp"
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

void Cliente::loopsitoRico() {
    char buffer[1024] = {0};
    while (true) {
        int valread = recv(socketCliente, buffer, 1024, 0);
        string s(buffer);
        cout << buffer;
        cout.flush();
    }
}

string Cliente::recibirMensaje() {
    char buffer[1024] = {0};
    recv(socketCliente, buffer, 1024, 0);
    string msg(buffer);
    return msg;
}

bool Cliente::fueAceptado(string nombre) {
    string msg = recibirMensaje();
    AnalizadorJSON aJSON(msg);
    if (aJSON.esJSON()) {
        aJSON.parseJSON();
        return aJSON.aceptadoBienFormado(nombre) && aJSON.fueAceptado();
    }
    cout << "El servidor no implementa el protocolo correctamente." << endl;
    return false;
}
