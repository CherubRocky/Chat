#include "Servidor.h"
#include <cstring>
#include <string>
#include <map>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include "../Controlador/AnalizadorJSON.cpp"
#include "../Controlador/GeneradorJSON.cpp"
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
    char mensaje[1024] = {0};
    recv(socketCliente, mensaje, sizeof(mensaje), 0);
    string nombre;
    string jsonCad(mensaje);
    if(!esIDENTIFY(jsonCad)) {
        mandarNotID(socketCliente);
        return; // desconecta al cliente
    }
    if (!existeNombre(jsonCad, nombre, socketCliente))
        mensajeNUExitoso(nombre);
    else {
        mensajeNUFallo(socketCliente, nombre);
        return;
    }
    bool sigue = true;
    while (sigue) {
        char mensaje2[1024] = {0};
        recv(socketCliente, mensaje2, sizeof(mensaje2), 0);
    }
}

void Servidor::servir() {
    Servidor::aceptarConnection();
}

void Servidor::aceptarConnection() {
    listen(socketServidor, 5);
    int contador = 0;
    while (true) {
        int socketCliente = accept(socketServidor, nullptr, nullptr);
        cout << "Hola desde el server.\n";
        thread hiloCliente(&Servidor::manejarCliente, this, socketCliente);
        hiloCliente.detach();
        cout << "Cliente " << ++contador << " conectado" << endl;
        cout.flush();
    }
}

bool Servidor::esIDENTIFY(string cadJSON) {
    AnalizadorJSON aJSON(cadJSON);
    bool valid = false;
    if (aJSON.esJSON()) {
        aJSON.parseJSON();
        if (aJSON.esIDValid())
            valid = true;
    }
    return valid;
}

bool Servidor::existeNombre(string cadJSON, string& nombre, int socketfd) {
    AnalizadorJSON aJSON(cadJSON);
    aJSON.parseJSON();
    bool existe = true;
    if (diccionarioNombres.find(aJSON.getNombreID()) == diccionarioNombres.end()) {
        existe = false;
        nombre = aJSON.getNombreID();
        diccionarioNombres[aJSON.getNombreID()] = socketfd;
    }
    return existe;
}

void Servidor::mensajeNUExitoso(string nombre) {
    GeneradorJSON gJSON("horacio");
    string json1 = gJSON.aceptarUsuario(nombre);
    mandarMensaje(nombre, json1);
    string json2 = gJSON.mandarNuevoUsuario(nombre);
    enviarMensajeMenosUno(nombre, json2);
}

void Servidor::mandarNotID(int socketfd) {
    GeneradorJSON gJSON("horacio");
    string jason = gJSON.rechazarNoIdentificado();
    send(socketfd, jason.c_str(), jason.length(), 0);
}

void Servidor::mensajeNUFallo(int socketClienteFd, string nombre) {
    GeneradorJSON gJSON("horacio");
    string jason = gJSON.rechazarUsuario(nombre);
    send(socketClienteFd, jason.c_str(), jason.length(), 0);
}

void Servidor::mandarMensaje(string nombre, string mensaje) {
    send(diccionarioNombres[nombre], mensaje.c_str(), mensaje.length(), 0);
}

void Servidor::enviarMensajeMenosUno(string nombre, string mensaje) {
    for (auto itr = diccionarioNombres.begin(); itr != diccionarioNombres.end(); ++itr)
        if ((*itr).first != nombre)
            send((*itr).second, mensaje.c_str(), mensaje.length(), 0);
}
