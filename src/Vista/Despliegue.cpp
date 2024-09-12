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
    cin >> mensaje;
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

void Despliegue::showPublicMessage(string usuario, string mensaje) {
    cout << colorearCadena(usurario) << " " << mensaje << endl;
}

void Despliegue::showPrivateMessage(string usuario, string mensaje) {
    cout << colorearCadena(usurario) << " " << mensaje << endl;
}

void Despliegue::showRoomMessage(string cuarto, string usuario, string mensaje) {

}

string Despliegue::colorearCadena(string cadena) {
        srand(time(0));
        int num = rand() % 6 + 1;
        string s;
        switch (num) {
            case 1:
                s = "\033[31m".append(cadena).append("\033[31m");
                break;
            case 2:
                s = "\033[32m".append(cadena).append("\033[32m");
                break;
            case 3:
                s = "\033[33m".append(cadena).append("\033[33m");
                break;
            case 4:
                s = "\033[34m".append(cadena).append("\033[34m");
                break;
            case 5:
                s = "\033[35m".append(cadena).append("\033[35m");
                break;
            case 6:
                s = "\033[36m".append(cadena).append("\033[36m");
                break;
        }
        return s;
}

void Despliegue::deployMenu() {
    cout << "La siguiente es una lista de opciones. Escribe el número correspondiente para hacer la opción indicada." << endl;
    cout << "1. Enviar un mensaje al chat general" << endl;
    cout << "2. Enviar un mensaje a un usuario en específico" << endl;
    cout << "1. Enviar un mensaje al chat general" << endl;
    cout << "1. Enviar un mensaje al chat general" << endl;
}
