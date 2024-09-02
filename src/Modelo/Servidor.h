#ifndef SERVIDOR_H
#define SERVIDOR_H

class Servidor {
public:
    Servidor();
    void procesaCosa();

private:
    int socketServidor;  // Descriptor

};

#endif
