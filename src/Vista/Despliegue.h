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
    void showPublicMessage(string, string);
    void showPrivateMessage(string, string);
    void showRoomMessage(string, string, string);
    void deployMenu();
    int getOption();
    string obtenerDestinatario();
    void mostrarMensajeDelSistema(string);
private:
    string colorearCadena(string);
    string getBold(string);
};

#endif
