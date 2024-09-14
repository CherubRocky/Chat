#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Despliegue.h"
using namespace std;

int Despliegue::obtenerPuerto() {
    cout << "Ingrese el puerto del servidor al cual quiere conectarse." << endl;
    int puerto;
    cin >> puerto;
    return puerto;
}

string Despliegue::obtenerMensaje() {
    cout << "Ingrese el mensaje que desea enviar." << endl;
    string mensaje;
    getline(cin, mensaje);
    return mensaje;
}

string Despliegue::obtenerIP() {
    cout << "Buen día, bienvenide al chatroom." << endl;
    cout << "Ingrese la dirección IP a la que desea conectarse." << endl;
    string address;
    cin >> address;
    return address;
}

string Despliegue::obtenerNombre() {
    cout << "Escriba su nombre de usuario." << endl;
    string nombre;
    cin >> nombre;
    return nombre;
}

void Despliegue::showPublicMessage(string usuario, int num, string mensaje) {
    cout << colorearCadena(usuario, num) << ": " << mensaje << endl;
}

void Despliegue::showRoomMessage(string cuarto, string usuario, string mensaje) {

}

string Despliegue::colorearCadena(string cadena, int num) {
        string s;
        switch (num) {
            case 1:
                s = string("\033[31m").append(cadena).append("\033[0m");
                break;
            case 2:
                s = string("\033[32m").append(cadena).append("\033[0m");
                break;
            case 3:
                s = string("\033[33m").append(cadena).append("\033[0m");
                break;
            case 4:
                s = string("\033[34m").append(cadena).append("\033[0m");
                break;
            case 5:
                s = string("\033[35m").append(cadena).append("\033[0m");
                break;
            case 6:
                s = string("\033[36m").append(cadena).append("\033[0m");
                break;
        }
        return s;
}

void Despliegue::deployMenu() {
    cout << "La siguiente es una lista de opciones. Escribe el número correspondiente para hacer la opción indicada." << endl;
    cout << "1. Enviar un mensaje al chat general" << endl;
    cout << "2. Enviar un mensaje a un usuario en específico" << endl;
    cout << "3. Obtener la lista de usuarios del chat" << endl;
    cout << "4. Enviar un mensaje al chat general" << endl;
}

int Despliegue::getOption() {
    int num;
    bool notValid = false;
    do {
        cin >> num;
        if (cin.fail()) {
            notValid = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Entrada no válida. Inténtalo de nuevo.\n";
        }
        else {
            notValid = false;
        }
    } while(notValid);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return num;
}

string Despliegue::obtenerDestinatario() {
    cout << "Ingrese el nombre del usuario al que desea mandar un mensaje." << endl;
    string nombre;
    getline(cin, nombre);
    return nombre;
}

string Despliegue::getBold(string mensaje) {
    return string("\033[1m").append(mensaje).append("\033[0m");
}

void Despliegue::mostrarMensajeDelSistema(string msg) {
    cout << getBold(msg) << endl;
}

void Despliegue::showPrivateMessage(string usuario, int num, string mensaje) {
    cout << getBold("privado:: ") << colorearCadena(usuario, num) << ": " << mensaje << endl;
}
