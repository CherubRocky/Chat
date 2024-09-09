#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Modelo/Cliente.cpp"
#include "Vista/Despliegue.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
    Despliegue vista;
    Cliente cliente;
    string ip = vista.obtenerIP();
    int puerto = vista.obtenerPuerto();
    cliente.conectarse(ip, puerto);
    vista.obtenerNombre();
    // conectarse al socket servidor
}
