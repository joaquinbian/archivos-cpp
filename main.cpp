#include <iostream>
#include <cstring>
#include "Pais.h"
#include "Ciudad.h"


bool paisExiste(char codigoPais[4]);
bool existeCiudad(int idCiudad);
int getCantidadPaises();
void listarPaises();
void agregarPais();
void cargarPais(Pais &pais);

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
    //listarPaises();
    //actividad 2
    agregarPais();
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
      fclose(pFile);
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

void agregarPais(){
    FILE *pFile;
    Pais registro;

    pFile = fopen("paises.dat", "ab");

    if(pFile == nullptr){
        std::cout << "NO se pudo abrir el archivo" << std::endl;
        exit(-1);
    }

    cargarPais(registro);

    int res = fwrite(&registro, sizeof(Pais), 1, pFile);

    if(res == 1){
        std::cout<< "El pais se ha guardado con exito" << std::endl;
    } else {
        std::cout<<"no se ha podido guardar el pais" << std::endl;
    }

    
};


bool existeCiudad(int idCiudad){
    FILE *pFile;
    Ciudad registro;

    pFile = fopen("ciudades.dat", "rb");

    if(pFile == nullptr){
        std::cout << "no se pudo abrir el archivo ciudad" << std::endl;
        exit(-1);
    }
    
   while(fread(&registro, sizeof(Ciudad), 1, pFile) == 1){
        if(registro.getID() == idCiudad){
            fclose(pFile);
            return true;
        }
   }

    fclose(pFile);
   return false;
};

//enviamos una referencia pq sino crea una copia de un archivo
void cargarPais(Pais &pais){
    std::string codigo = "";
    std::string codigo2 = "";
    std::string nombre= "";
    std::string continente = "";
    float superficie = 0.0;
    int poblacion = 0;
    short independencia = 0;
    float expectativaDeVida = 0.0;
    int capital = 0;
    std::cout << "Ingrese el codigo de pais: ";
    std::cin >> codigo;
    std::cout << std::endl;
    std::cout << "Ingrese el codigo2 de pais: ";
    std::cin >> codigo2;
    std::cout << std::endl;
    std::cout << "Ingrese el nombre de pais: ";
    std::cin >> nombre;
    std::cout << std::endl;
    std::cout << "Ingrese el continente de pais: ";
    std::cin >> continente;
    std::cout << std::endl;
    std::cout << "Ingrese el superficie de pais: ";
    std::cin >> superficie;
    std::cout << std::endl;
    std::cout << "Ingrese el poblacion de pais: ";
    std::cin >> poblacion;
    std::cout << std::endl;
    std::cout << "Ingrese el independencia de pais: ";
    std::cin >> independencia;
    std::cout << std::endl;
    std::cout << "Ingrese el expectativa De Vida de pais: ";
    std::cin >> expectativaDeVida;
    do{
        std::cout << std::endl;
        std::cout << "Ingrese el capital de pais: ";
        std::cin >> capital;
    }while(!existeCiudad(capital));

    pais.setCodigo(codigo.c_str());
    pais.setCodigo2(codigo2.c_str());
    pais.setNombre(nombre.c_str());
    pais.setContinente(continente.c_str());
    pais.setSuperficie(superficie);
    pais.setPoblacion(poblacion);
    pais.setIndependencia(independencia);
    pais.setExpectativaDeVida(expectativaDeVida);
    pais.setIDCapital(capital);
};
