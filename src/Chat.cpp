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
    Cliente cliente;
    Despliegue vista;
    int puerto = vista.obtenerPuerto();





    cout << "Ingresa el puerto al que quieres conectarte." << endl;
    cin >> puerto;
    cout << "Ingresa el mensaje que quieres enviar." << endl;
    string mensaje;
    cin >> mensaje;
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(puerto);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));

    // sending data
    const char* message = mensaje.c_str();
    send(clientSocket, message, strlen(message), 0);

    // closing socket
    close(clientSocket);
    return 0;
}
