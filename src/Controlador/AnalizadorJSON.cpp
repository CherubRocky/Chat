#include <nlohmann/json.hpp>
#include "AnalizadorJSON.h"
#include <string>
using namespace std;
using json = nlohmann::json;

AnalizadorJSON::AnalizadorJSON(string m) {
    jString = m;
}

bool AnalizadorJSON::esJSON() {
    try {
        json jObj = json::parse(jString);
    }
    catch(json::parse_error& e) {
        return false;
    }
    return true;
}

void AnalizadorJSON::parseJSON() {
    jason = json::parse(jString);
}

bool AnalizadorJSON::esIDValid() {
    if (jason.size() != 2 || !jason.contains("type") ||
        !jason.contains("username") || (jason["type"] != "IDENTIFY")) {
        return false;
    }
    return true;
}

string AnalizadorJSON::getNombreID() {
    return jason["username"];
}

bool AnalizadorJSON::aceptadoBienFormado(string nombre) {
    if (jason.size() != 4 || !jason.contains("type") || !jason.contains("operation") ||
        !jason.contains("result") || !jason.contains("extra")) {
        return false;
    }
    if (jason["type"] != "RESPONSE" || jason["operation"] != "IDENTIFY" ||
        !(jason["result"] == "USER_ALREADY_EXISTS" || jason["result"] == "SUCCESS") ||
        jason["extra"] != nombre) {
        return false;
    }
    return true;
}

bool AnalizadorJSON::fueAceptado() {
    return jason["result"] == "SUCCESS";
}
