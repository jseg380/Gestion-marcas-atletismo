/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: Utils.h
//
/***************************************************************************/

#ifndef UTILS
#define UTILS

#include <string>

using namespace std;

/***************************************************************************/
/***************************************************************************/
// Dos números son reales si su diferencia (en valor absoluto) es menor 
// que el valor de la constante PRECISION_SON_IGUALES

const double PRECISION_SON_IGUALES = 1e-6; // 0.000001

/***************************************************************************/
/***************************************************************************/
// Función (asociada a la constante PRECISION_SON_IGUALES) que
// permite que dos números reales muy próximos sean considerados iguales.

bool SonIguales(double uno, double otro);

/***************************************************************************/
/***************************************************************************/
// Comprueba la  existencia y disponibilidad de un fichero

bool ExisteFichero (const string & nombre);

/***************************************************************************/
/***************************************************************************/
// Calcula el tamaño (número de bytes) de un fichero. 

int TamanioFichero (const string & nombre);

/***************************************************************************/
/***************************************************************************/

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

string FormatInt (int entero, int num_casillas, char relleno='0'); 

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

string FormatString (string la_cadena, int num_casillas, char relleno=' '); 

/***************************************************************************/
/***************************************************************************/

#endif
