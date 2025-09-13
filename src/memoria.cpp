#include <iostream>
using namespace std;

int main(int arg, char const *argv[])
{
    int variable = 7;
    cout << "Direccion: " << &variable << endl;
    cout << "Valor: " << variable << endl;
    cout << "Indireccion: " << *(&variable) << endl;
    cout << "Tipos de datos: " << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "bool: " << sizeof(bool) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "char: " << sizeof(char) << endl;
    cout << "double: " << sizeof(double) << endl;
    cout << "byte: " << sizeof(byte) << endl;
    cout << "float: " << sizeof(float) << endl;
    void *direccion = malloc(4);
    cout << "direccion: valor " << direccion << endl;
    cout << "tamanio: " << sizeof(direccion) << endl;
    cout << "direccion puntero: " << &direccion << endl;

    // Casteo
    int prueba = 64;
    char casteo = (char)prueba;
    cout << "Resultado: " << casteo << endl;
    return 0;
}