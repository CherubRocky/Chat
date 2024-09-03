#ifndef CLIENTE_H  // Guardas de inclusión para prevenir múltiples inclusiones
#define CLIENTE_H

class Cliente {
public:
    Cliente();
    void procesaCosa();

private:
    int socket_cliente;  // Descriptor

};

#endif
