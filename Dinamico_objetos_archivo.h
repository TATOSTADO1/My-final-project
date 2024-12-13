#ifndef DINAMICO_OBJETOS_ARCHIVO_H
#define DINAMICO_OBJETOS_ARCHIVO_H

#include "Lector_Archivo.h"

class Dinamico_objetos_archivo {
friend class Menu;
	public:
	Dinamico_objetos_archivo(Lector_Archivo *archivos, int N);
	~Dinamico_objetos_archivo();
	void Imprimir_Nombres();
	void Cargar_Archivo( string nombre_archivo);
	int getN();                        
    Lector_Archivo *getArchivos();     
	void Actualizar_Archivo(Lector_Archivo &archivo_modificado, int indice);
    void setN(int N);                        
    void setArchivos(Lector_Archivo *archivos, int N);	

private:
	Lector_Archivo *archivos;//instanciamos un apuntador a un objeto de la clase Lector_Archivo
	int N;//numero de archivos
};

#endif

