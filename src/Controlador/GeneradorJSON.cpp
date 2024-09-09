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
