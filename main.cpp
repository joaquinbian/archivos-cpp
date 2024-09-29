#include <iostream>
#include <cstring>
#include "Pais.h"

bool paisExiste(char codigoPais[4]);
int getCantidadPaises();
void listarPaises();

int main(){

 /*   
    //ACTIVIDAD 1
    char codigo[4];
    bool exists;

    std::cout << "Ingrese el codigo del pais: ";
    std::cin >> codigo;

    exists =  paisExiste(codigo);

    if(exists){
        std::cout << "El pais existe " << std::endl;
    } else {
        std::cout << "El pais no existe " << std::endl;

    } */
    std::cout << "La cantidad de paises que hay es " << getCantidadPaises() << std::endl;
    //actividad 3
    listarPaises();
    
    return 0;
}

int getCantidadPaises(){
    FILE *pFile;
    Pais pais;
    int cantidad;


    //todo esto es de la clase 
    //abre el archivo en modo lectura
    pFile = fopen("paises.dat", "rb");

    if(pFile == nullptr){
        return -1;
    }

    //movemos el cursor al final del archivo
    fseek(pFile, 0, SEEK_END);


    //ftell nos dice la cantidad de bytes que hay desde el inicio hasta
    //donde esta el cursor(que lo movimos al final), entonces
    //nos dice la cantidad de bytes del archivo, y lo dividimos por
    //lo que ocupa un solo registro, obteniendo el total
    cantidad = ftell(pFile) / sizeof(Pais);

    if(cantidad >= 1){
        return cantidad;
    }

    fclose(pFile);

    return 0;
};

bool paisExiste(char codigoPais[4]){
    FILE * pFile;
    Pais pais;
    int totalPaises = getCantidadPaises();

    pFile = fopen("paises.dat", "rb");

    for(int i = 0; i < totalPaises; i++){
        fread(&pais, sizeof(Pais), 1, pFile);
        //compara 2 chars, si son iguales devuelve 0
        if(strcmp(pais.getCodigo(), codigoPais) == 0){
            return true;
        }

    }

    fclose(pFile);


    return false;
};

void listarPaises(){
    FILE *pFile;
    Pais registro;
    int res;
    pFile = fopen("paises.dat", "rb");

    if(pFile == nullptr){
        std::cout << "No se pudo leer el archivo ";
        exit(-1);
    }

    for(int i = 0; i < getCantidadPaises(); i++){
        res = fread(&registro, sizeof(Pais), 1, pFile);
        if(res == 1){
            registro.mostrar();
        }
    }

    fclose(pFile);
};