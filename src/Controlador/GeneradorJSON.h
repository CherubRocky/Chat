#ifndef GENERADORJSON_H
#define GENERADORJSON_H
#include <string>
class GeneradorJSON {
public:
    GeneradorJSON(std::string);
    std::string identificarse();
private:
    std::string nombreUsuario;
};
#endif
