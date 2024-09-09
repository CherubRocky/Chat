#include <cstring>
#ifndef CLIENTE_H  // Guardas de inclusión para prevenir múltiples inclusiones
#define CLIENTE_H

class Cliente {
public:
    Cliente();
    void conectarse(std::string, int);

private:
    int socketCliente;  // Descriptor
};

#endif
