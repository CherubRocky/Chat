#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <sys/socket.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include "Modelo/Cliente.cpp"
#include "Vista/Despliegue.cpp"
#include "Controlador/GeneradorJSON.cpp"
using json = nlohmann::json;
using namespace std;

int main(int argc, char const *argv[]) {
    Despliegue vista;
    Cliente cliente;
    string ip = vista.obtenerIP();
    int puerto = vista.obtenerPuerto();
    cliente.conectarse(ip, puerto);
    string nombre = vista.obtenerNombre();
    GeneradorJSON genJson(nombre);
    cout << "Cosa enviada: " << genJson.identificarse() << endl;
    cliente.enviarMensaje(genJson.identificarse());
    if (!cliente.fueAceptado(nombre)) {
        cout << "El nombre que ingresaste ya está ocupado."
        return;
    }
    bool sigue = true;
    thread hiloEscucha(cliente, nombre, sigue);
    thread hiloUsr(cliente, nombre, sigue, vista);
    hiloEscucha.join();
    hiloUsr.join();
}

void escuchar(Cliente& cliente, string nombre, bool& sigue, Desplietue& vista) {
    while (sigue) {
        string msg = cliente.recibirMensaje();
        json jason;
        try {
            jason = json::parse(msg);
        }
        catch(json::parse_error& e) {
            sigue = false;
            break;
            exit();
        }
        if (jason.size() < 2 || jason.size() > 4 || !jason.contains("type")) {
            // termina
            sigue = false;
            break;
            exit();
        }
        if(jason.size() == 3) {
            if (jason.contains("username")) {
                if (jason.contains("text")) {
                    if (jason["type"] == "TEXT_FROM")
                        vista.showPrivateMessage(jason["username"], jason["text"]);

                    else if (jason["type"] == "PUBLIC_TEXT_FROM")
                        vista.showPublicMessage(jason["username"], jason["text"]);
                }
                else if (jason.contains("status") && jason["type"] == "NEW_STATUS") {

                }
                else if (jason.contains("roomname")) {
                    if (jason["type"] == "JOINED_ROOM") {
                        /* code */
                    }
                    else if (jason["type"] == "LEFT_ROOM") {

                    }
                }
            }
            else if (jason.contains("users") && jason.contains("roomname") &&
                jason["type"] == "ROOM_USER_LIST") {
                /* code */
            }

        }
        else if (jason.size() == 2) {
            if (jason.contains("username")) {
                if (jason["type"] == "DISCONNECTED") {
                    /* code */
                }
                else if (jason["type"] == "NEW_USER") {
                    /* code */
                }
                else {

                }
            }
            else if (jason.contains("users") && jason["type"] == "USER_LIST") {

            }
            else {

            }
        }
        else if (jason.size() == 4) {
            if (jason.contains("roomname") && jason.contains("username") &&
                jason.contains("text") && jason["type"] == "ROOM_TEXT_FROM") {
                /* code */
            }
        }
        else {
            sigue = false;
            exit();
            break;
        }
    }
}

void interactuar(Cliente& cliente, string nombre, bool& sigue, Despliegue& vista) {
    vista.deployMenu();
    while (sigue) {
        vista.getOption();

        enviarMensaje();
    }
}
