#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
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

int generarNumSeis() {
    srand(time(0));
    return rand() % 6 + 1;
}

void escuchar(Cliente& cliente, string nombre, bool& sigue, Despliegue& vista, map<string, int>& usuarios) {
    while (sigue) {
        string msg = cliente.recibirMensaje();
        json jason;
        try {
            jason = json::parse(msg);
        }
        catch(json::parse_error& e) {
            sigue = false;
            break;
            exit(0);
        }
        if (jason.size() < 2 || jason.size() > 4 || !jason.contains("type")) {
            // termina
            sigue = false;
            break;
            exit(0);
        }
        if(jason.size() == 3) {
            if (jason.contains("username")) {
                if (jason.contains("text")) {
                    if (jason["type"] == "TEXT_FROM") {
                        int color = generarNumSeis();
                        if (usuarios.find(jason["username"]) != usuarios.end()) {
                            color = usuarios[jason["username"]];
                        }
                        vista.showPrivateMessage(jason["username"], color, jason["text"]);
                    }

                    else if (jason["type"] == "PUBLIC_TEXT_FROM") {
                        int color = generarNumSeis();
                        if (usuarios.find(jason["username"]) != usuarios.end()) {
                            color = usuarios[jason["username"]];
                        }
                        vista.showPublicMessage(jason["username"], color, jason["text"]);
                    }
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
                    usuarios[jason["username"]] = generarNumSeis();
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
            else if (jason["type"] == "RESPONSE" && jason.contains("operation") &&
                jason.contains("result") && jason.contains("extra")) {

                if (jason["operation"] == "TEXT" && jason["result"] == "NO_SUCH_USER") {
                    string extra = jason["extra"];
                    vista.mostrarMensajeDelSistema("El nombre de usuario " + extra + " no existe.");
                }
            }
        }
        else {
            sigue = false;
            exit(0);
            break;
        }
    }
}

void interactuar(Cliente& cliente, string nombre, bool& sigue, Despliegue& vista, map<string, int>& usuarios) {
    vista.deployMenu();
    while (sigue) {
        int opc = vista.getOption();
        string mensaje;
        string json;
        GeneradorJSON gJSON("Horacio");
        switch (opc) {
            case 1:
                mensaje = vista.obtenerMensaje();
                json = gJSON.publicMessageClient(mensaje);
                break;
            case 2:
                string usr = vista.obtenerDestinatario();
                mensaje = vista.obtenerMensaje();
                json = gJSON.privateMessageClient(usr, mensaje);
                break;
            // case 3:
            //     cout << "no sirve";
            //     break;
            // case 4:
            //     cout << "no sirve";
            //     break;
        }
        cliente.enviarMensaje(json);
    }
}

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
    cout << "Hola.\n";
    if (!cliente.fueAceptado(nombre)) {
        cout << "El nombre que ingresaste ya está ocupado.\n";
        return -1;
    }
    bool sigue = true;
    map<string, int> usuarios;
    thread hiloEscucha(escuchar, ref(cliente), nombre, ref(sigue), ref(vista), ref(usuarios));
    thread hiloUsr(interactuar, ref(cliente), nombre, ref(sigue), ref(vista), ref(usuarios));
    hiloEscucha.join();
    hiloUsr.join();
}
