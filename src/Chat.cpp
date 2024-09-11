#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Modelo/Cliente.cpp"
#include "Vista/Despliegue.cpp"
#include "Controlador/GeneradorJSON.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
    Despliegue vista;
    Cliente cliente;
    string ip = vista.obtenerIP();
    int puerto = vista.obtenerPuerto();
    cliente.conectarse(ip, puerto);
    string nombre = vista.obtenerNombre();
    GeneradorJSON genJson(nombre);
    cout << genJson.identificarse() << endl;
    cliente.enviarMensaje(genJson.identificarse());
    // conectarse al socket servidor
}
