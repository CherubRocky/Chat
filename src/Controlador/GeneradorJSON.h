#ifndef GENERADORJSON_H
#define GENERADORJSON_H
#include <string>
using namespace std;
class GeneradorJSON {
public:
    GeneradorJSON(string);
    string identificarse();
    string aceptarUsuario(string);
    string mandarNuevoUsuario(string);
    string rechazarUsuario(string);
    string rechazarNoIdentificado();
    string publicTextFrom(string, string);
    string publicMessageClient(string);
    string privateMessageClient(string, string);
    string textFrom(string, string);
    string textNoSuchUser(string);
    string generarResponse(string, string, string);
private:
    string nombreUsuario;
};
#endif
