#include <nlohmann/json.hpp>
#include "GeneradorJSON.h"
#include <string>
using namespace std;
using json = nlohmann::json;

GeneradorJSON::GeneradorJSON(string nombre) {
    nombreUsuario = nombre;
}

string GeneradorJSON::identificarse() {
    json mensajeIdentification;
    mensajeIdentification["type"] = "IDENTIFY";
    mensajeIdentification["username"] = nombreUsuario;
    return mensajeIdentification.dump();
}

string GeneradorJSON::aceptarUsuario(string nombre) {
    json mensajeExitoso;
    mensajeExitoso["type"] = "RESPONSE";
    mensajeExitoso["operation"] = "IDENTIFY";
    mensajeExitoso["result"] = "SUCCESS";
    mensajeExitoso["extra"] = nombre;
    return mensajeExitoso.dump();
}

string GeneradorJSON::mandarNuevoUsuario(string nombre) {
    json nuevoUsuario;
    nuevoUsuario["type"] = "NEW_USER";
    nuevoUsuario["username"] = nombre;
    return nuevoUsuario.dump();
}

string GeneradorJSON::rechazarUsuario(string nombre) {
    json mensajeError;
    mensajeError["type"] = "RESPONSE";
    mensajeError["operation"] = "IDENTIFY";
    mensajeError["result"] = "USER_ALREADY_EXISTS";
    mensajeError["extra"] = nombre;
    return mensajeError.dump();
}

string GeneradorJSON::rechazarNoIdentificado() {
    json mensajeError;
    mensajeError["type"] = "RESPONSE";
    mensajeError["operation"] = "INVALID";
    mensajeError["result"] = "NOT_IDENTIFIED";
    return mensajeError.dump();
}

string GeneradorJSON::publicTextFrom(string nombre, string texto) {
    json mensajeError;
    mensajeError["type"] = "PUBLIC_TEXT_FROM";
    mensajeError["username"] = nombre;
    mensajeError["text"] = texto;
    return mensajeError.dump();
}

string GeneradorJSON::publicMessageClient(string texto) {
    json txtCliente;
    txtCliente["type"] = "PUBLIC_TEXT";
    txtCliente["text"] = texto;
    return txtCliente.dump();
}
