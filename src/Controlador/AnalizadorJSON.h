#ifndef ANALIZADORJSON_H
#define ANALIZADORJSON_H
#include <string>
class AnalizadorJSON {
public:
    AnalizadorJSON(string);
    bool esIDValid();
    bool esJSON();
    void parseJSON();
    std::string getNombreID();

private:
    std::string jString;
    nlohmann::json jason;

};
#endif
