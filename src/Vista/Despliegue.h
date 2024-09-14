#ifndef DESPLIEGUE_H
#define DESPLIEGUE_H
#include <string>
using namespace std;

class Despliegue {
public:
    int obtenerPuerto();
    string obtenerMensaje();
    string obtenerNombre();
    string obtenerIP();
    void showPublicMessage(string, int, string);
    void showPrivateMessage(string, int, string);
    void showRoomMessage(string, string, string);
    void deployMenu();
    int getOption();
    string obtenerDestinatario();
    void mostrarMensajeDelSistema(string);
private:
    string colorearCadena(string, int);
    string getBold(string);
};

#endif
