#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "Status.cpp"
using namespace std;
class Usuario {
public:
    Usuario(string nickname, int socket, Status stat) {
        apodo = nickname;
        socketfd = socket;
        status = stat;
    }

    string getApodo() {
        return apodo;
    }

    int getSocketFd() {
        return socketfd;
    }

    string getStatus() {
        switch (status) {
            case Status::ACTIVE:
                return "ACTIVE";
            case Status::AWAY:
                return "AWAY";
            case Status::BUSY:
                return "BUSY";
        }
        return "malo";
    }

    void setStatus(Status stat) {
        status = stat;
    }

private:
    string apodo;
    int socketfd;
    Status status;

};
#endif
