#include <cstring>
#include <string>
#ifndef CLIENTE_H  // Guardas de inclusión para prevenir múltiples inclusiones
#define CLIENTE_H
using namespace std;

class Cliente {
public:
    Cliente();
    void conectarse(string, int);
    void enviarMensaje(string);
    void loopsitoRico();
    string recibirMensaje();
    bool fueAceptado(string);

private:
    int socketCliente;  // Descriptor
};

#endif
