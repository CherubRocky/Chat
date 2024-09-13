#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <map>
#include <string>
using namespace std;

class Servidor {
public:
    Servidor();
    void servir();
    void aceptarConnection();

private:
    void manejarCliente(int);
    bool existeNombre(string, string&, int);
    bool esIDENTIFY(string);
    void mensajeNUExitoso(string);
    void mensajeNUFallo(int, string);
    void mandarMensaje(string, string);
    void mandarNotID(int);
    void enviarMensajeMenosUno(string, string);
    void procesarJSON(string, string, bool&);
    int socketServidor;
    map<string, int> diccionarioNombres;
};

#endif
