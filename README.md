Autor: Zaldivar Alanis Rodrigo

Para generar los ejecutables, crea una carpeta build en el directorio raíz
y luego haz cd build. Después ejecuta el comando "cmake ..".
Posteriormente ejecuta "cmake --build ."
Luego haz "cd src" y ejecuta "./Chat" y "./Servidor" para el cliente y el
servidor respectivamente.

El uso del cliente es sencillo y te va guiando en la ejecución.
Primero escribes la ip, luego el puerto y luego el nombre.
Ya después aparece un menú desplegable con números. Para cada acción que desees
ejecutar, debes escribir un número y la interfaz te guiará.

Dependencias:
    cmake 3.22.1 https://discourse.cmake.org/t/cmake-3-22-1-available-for-download/4617
    biblioteca de nlohmann para jsons https://github.com/nlohmann/json
    Los sockets son de unix, así que no debería haber mucho problema.
