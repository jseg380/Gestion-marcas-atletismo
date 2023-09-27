/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseFecha.h
//
/***************************************************************************/
/***************************************************************************/

#ifndef CLASE_FECHA
#define CLASE_FECHA

#include <string>

using namespace std;


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

string ToString (int entero, int num_casillas, char relleno = ' '); 

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

string ToString (string la_cadena, int num_casillas, char relleno=' ');





/////////////////////////////////////////////////////////////////////////////
// Registro de fecha

class Fecha {

private: 

	int dia;	// 1 <= dia <= 31 
	int mes; 	// 1 <= mes <= 12
	int anio; 	// 1900 <= anio	

public:

	/***********************************************************************/
	// Constructor sin argumentos.
	// Inicializa el objeto con la fecha actual.

	Fecha (void);

	/***********************************************************************/
	// Constructor directo.
	// Parámetros: trivial.
	// PRE: 1 <= el_dia <= 31
	// PRE: 1 <= el_mes <= 12
	// PRE: 1900 <= el_anio

	Fecha (int el_dia, int el_mes, int el_anio);

	/***********************************************************************/
	// Constructor desde un string.
	// Parámetros: cad, string con la fecha. 
	// PRE: cad contiene una fecha CORRECTA en formato dd/mm/aaaa 
	// PRE: cad.length() == 10	

	Fecha (string cad);

	/***********************************************************************/
	// Métodos Get

	int GetDia  (void) const;
	int GetMes  (void) const;
	int GetAnio (void) const;

	/***********************************************************************/
	// Serializa un dato Fecha.

	string ToString (void) const;
	
	/***********************************************************************/
	// Operadores relacionales
	// Devuelve: un valor bool
	
	bool operator == (const Fecha & otro) const;
	
	bool operator != (const Fecha & otro) const;
	
	bool operator  > (const Fecha & otro) const;
	
	bool operator <= (const Fecha & otro) const;
	
	bool operator  < (const Fecha & otro) const;
	
	bool operator >= (const Fecha & otro) const;
	
	/***********************************************************************/
	// Sobrecarga de los operadores >> y <<
	
	friend istream & operator >> (istream & entrada, Fecha & la_fecha);
	
	friend ostream & operator << (ostream & salida, const Fecha & la_fecha);
	
	
	
	private:
	
	/***********************************************************************/
	// Establece la fecha desde un string.
	// Parámetros: cad, string con la fecha. 
	// PRE: cad contiene una fecha CORRECTA en formato dd/mm/aaaa
	// PRE: cad.length() == 10
	
	void PonerFecha (const string & cad);
	
};

#endif
