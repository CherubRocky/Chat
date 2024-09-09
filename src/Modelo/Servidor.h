#ifndef SERVIDOR_H
#define SERVIDOR_H

class Servidor {
public:
    Servidor();
    void procesaCosa();
    void servir();
    void aceptarConnection();

private:
    void manejarCliente(int);
    int socketServidor;  // Descriptor
};

#endif
