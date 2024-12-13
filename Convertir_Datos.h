#ifndef CONVERTIR_DATOS_H
#define CONVERTIR_DATOS_H

#include <string>
#include <vector>

using namespace std;

class Convertir_Datos 
{
public:
    Convertir_Datos(double **num=NULL,int filas=0, int *columnas=NULL,int *filas_errores=NULL,int *columnas_errores=NULL,int errores=0,int col=0);
    ~Convertir_Datos(); 
    void Flotantes(string *ptr,int N);
	void Imprime(double **num, int filas, int *columnas);
    void Restaurar_Datos_Media();
    void Restaurar_Datos_Mediana();
    double **getMatriz();
    int getFilas();
int *getColumnas();
void Menu_2();
int *getFilas_Errores();
int *getColumnas_Errores();
int getErrores();
int getOp_Restaurar();
int getRegresar_Menu();

    
private:
    double **num; //matriz de flotantes
    int filas;  //numero de filas
    int *columnas; //numero de columnas en cada fila
	int errores; //numero de errores
    int col; //numero de columnas por cada fila para reasignarlo en el arreglo anterior

     int *filas_errores; //arreglo de filas con errores
    int *columnas_errores;//arreglo de columnas con errores
    int op_restaurar;//opcion de restaurar
    int regresar_menu;//opcion de regresar al menu
    
};

#endif
