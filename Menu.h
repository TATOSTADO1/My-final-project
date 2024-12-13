#ifndef MENU_H
#define MENU_H

#include "Lector_Archivo.h"
#include "Dinamico_objetos_archivo.h"

class Menu
{
public:
	void Mostrar_Menu();//contiene el menu principal
	void Seleccionar_Archivo(int N, Lector_Archivo &arch_base, Dinamico_objetos_archivo &archivos_base);//valida y asigna el archivo seleccionado
	void Regresar_Menu();//consta de un pause y un cls 
	bool Validar_Seleccion_Archivo(Dinamico_objetos_archivo &archivos_base, Lector_Archivo &arch_base);//valida si hay archivos cargados y llama a la funcion Seleccionar_Archivo

private:
	int ind;
};

#endif
