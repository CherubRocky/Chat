#ifndef GENERADORJSON_H
#define GENERADORJSON_H
#include <string>
#include <map>
#include <memory>
#include "../Modelo/Usuario.cpp"
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
    string pedirUserList();
    string darUserList(map<string, shared_ptr<Usuario>>);
private:
    string nombreUsuario;
    string crearStatusMap(const map<string, shared_ptr<Usuario>> diccionario);
};
#endif
