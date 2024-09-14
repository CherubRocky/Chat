#include "Servidor.h"
#include <cstring>
#include <string>
#include <map>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include "Usuario.cpp"
#include "Status.cpp"
#include "../Controlador/AnalizadorJSON.cpp"
#include "../Controlador/GeneradorJSON.cpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

string Servidor::obtenerIP() {
    string tipo = "wlp2s0";
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        cerr << "Error al crear el socket\n";
        return "";
    }

    struct ifreq ifr;
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, tipo.c_str(), IFNAMSIZ - 1);

    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
        cerr << "Error al obtener la dirección IP de " << tipo << "\n";
        close(fd);
        return "";
    }
    close(fd);
    return inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);
}


Servidor::Servidor() {
    socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in dirServidor;
    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons(9090);
    dirServidor.sin_addr.s_addr = INADDR_ANY;
    bind(socketServidor, (struct sockaddr*)&dirServidor, sizeof(dirServidor));
    cout << "Puerto asignado a este servidor: " << ntohs(dirServidor.sin_port) << endl;
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &dirServidor.sin_addr, ip, INET_ADDRSTRLEN);
    cout << "IP enlazada al servidor: " << obtenerIP() << endl;
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
        char buffer2[1024] = {0};
        recv(socketCliente, buffer2, sizeof(buffer2), 0);
        string mensaje2(buffer2);
        procesarJSON(nombre, mensaje2, sigue);
    }
}

void Servidor::procesarJSON(string nombre, string mensaje, bool& sigue) {
    json jason;
    try {
        jason = json::parse(mensaje);
    }
    catch(json::parse_error& e) {
        sigue = false;
        // saca al cliente o algo así
        return;
    }
    if (jason.size() < 1 || jason.size() > 4 || !jason.contains("type")) {
        // termina
        sigue = false;
        return;
    }
    GeneradorJSON gJSON("Horacio");
    if (jason.size() == 1 && jason["type"] == "USERS") {
        mandarMensaje(nombre, gJSON.darUserList(diccionarioNombres));
    }
    else if (jason.size() == 2) {
        if (jason.contains("text") && jason["type"] == "PUBLIC_TEXT") {
            enviarMensajeMenosUno(nombre, gJSON.publicTextFrom(nombre, jason["text"]));
        }
    }
    else if (jason.size() == 3) {
        if (jason.contains("username")) {
            if (jason.contains("text") && jason["type"] == "TEXT") {
                if (diccionarioNombres.find(jason["username"]) != diccionarioNombres.end()) {
                    mandarMensaje(jason["username"], gJSON.textFrom(nombre, jason["text"]));
                }
                else {
                    mandarMensaje(nombre, gJSON.textNoSuchUser(jason["username"]));
                }
            }

            else if (true) {

            }
        }
        /* code */
    }
    else if (jason.size() == 4) {
        /* code */
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
        shared_ptr<Usuario> newUser = make_shared<Usuario>(aJSON.getNombreID(), socketfd, Status::ACTIVE);
        nombre = aJSON.getNombreID();
        diccionarioNombres[aJSON.getNombreID()] = newUser;
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
    send(diccionarioNombres[nombre]->getSocketFd(), mensaje.c_str(), mensaje.length(), 0);
}

void Servidor::enviarMensajeMenosUno(string nombre, string mensaje) {
    for (auto itr = diccionarioNombres.begin(); itr != diccionarioNombres.end(); ++itr)
        if ((*itr).first != nombre)
            send((*itr).second->getSocketFd(), mensaje.c_str(), mensaje.length(), 0);
}
