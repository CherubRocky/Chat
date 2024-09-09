#include <iostream>
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
