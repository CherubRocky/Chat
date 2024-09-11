#ifndef GENERADORJSON_H
#define GENERADORJSON_H
#include <string>
class GeneradorJSON {
public:
    GeneradorJSON(std::string);
    std::string identificarse();
    std::string aceptarUsuario(std::string);
    std::string mandarNuevoUsuario(std::string);
    std::string rechazarUsuario(std::string);
    std::string rechazarNoIdentificado();
private:
    std::string nombreUsuario;
};
#endif
