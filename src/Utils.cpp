/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: Utils.cpp
//
/***************************************************************************/

#include<iostream>
#include<cstdlib>
#include<cctype>
#include<iomanip>
#include <cstring>
#include <limits>
#include <string>
#include <cmath>
#include <fstream>

#include "Utils.h"

using namespace std;


/***************************************************************************/
/***************************************************************************/
// Función (asociada a la constante PRECISION_SON_IGUALES) que
// permite que dos números reales muy próximos sean considerados iguales.

bool SonIguales(double uno, double otro) 
{
	return (fabs(uno-otro) <= PRECISION_SON_IGUALES);
}

/***************************************************************************/
/***************************************************************************/
// Comprueba la  existencia y disponibilidad de un fichero

bool ExisteFichero (const string & nombre)
{

	ifstream fichero;

	fichero.open (nombre);

	bool problema = fichero.fail();
	if (!problema) fichero.close();

	return ((problema) ? false : true);
}

/***************************************************************************/
/***************************************************************************/
// Calcula el tamaño (número de bytes) de un fichero. 

int TamanioFichero (const string & nombre)
{
	int tam;

	ifstream fi (nombre);

	fi.seekg (0, ios::end);
	tam = fi.tellg();

	fi.close();

	return (tam);
}

/***************************************************************************/
/***************************************************************************/
// Convierte el dato int "entero" a un string con "num_casillas" casillas 
// que contiene el valor textual de "entero".
// 
// Recibe: 	entero, el valor a transformar.
//			num_casillas, número total de casillas que tendrá el resultado.
//			relleno, el carácter que se emplea para rellenar los huecos. 
// Devuelve: el string compuesto.  
//
// NOTAS: Si el número de casillas solicitado es mayor que el que se necesita, 
//	  	se completa al principio con "relleno" hasta alcanzar un tamaño de 
//	  	"num_casillas". Si el valor tuviera "per se" más de "num_casillas" 
//		se devuelve tal cual.  

string FormatInt (int entero, int num_casillas, char relleno)
{
	// Inicialmente nos quedamos con el resultado de to_string
	string cadena = to_string(entero);

	int long_cadena = (int) cadena.length(); 
	
	// Si es preciso se completa (por la izquierda) con "relleno"
	
	if (long_cadena < num_casillas) {
		
		int num_casillas_faltan = num_casillas-long_cadena; 
		
		for (int i=0; i<num_casillas_faltan; i++) 
			cadena = relleno + cadena; 
	}

	return cadena;
}

/***************************************************************************/
/***************************************************************************/
// Convierte el dato string "la_cadena" a un string con "num_casillas" 
// casillas rellenando con el caracter "relleno" por la izquierda.
// 
// Recibe: 	la_cadena, el valor a transformar.
//			num_casillas, número total de casillas que tendrá el resultado.
//			relleno, el carácter que se emplea para rellenar los huecos. 
// Devuelve: el string compuesto.  
//
// NOTAS: Si el número de casillas solicitado es mayor que el que se necesita, 
//	  	se completa al principio con "relleno" hasta alcanzar un tamaño de 
//	  	"num_casillas". Si el valor tuviera "per se" más de "num_casillas" 
//		se devuelve tal cual.   

string FormatString (string la_cadena, int num_casillas, char relleno)
{
	string cadena = la_cadena;

	string cad_relleno; 
	cad_relleno.push_back(relleno); 

	int long_cadena = (int) la_cadena.length(); 
	
	// Si es preciso se completa (por la izquierda) con "relleno"
	
	if (long_cadena < num_casillas) {
		
		int num_casillas_faltan = num_casillas-long_cadena; 
		
		for (int i=0; i<num_casillas_faltan; i++) 
			cadena = cad_relleno + cadena; 
	}

	return cadena;
}

/***************************************************************************/
/***************************************************************************/
