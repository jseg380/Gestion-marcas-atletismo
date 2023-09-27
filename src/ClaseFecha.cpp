/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseFecha.cpp
//
/***************************************************************************/
/***************************************************************************/

#include <sstream>
#include <iomanip>	// Para usar put_time
#include <ctime>

#include "ClaseFecha.h"

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

string ToString (int entero, int num_casillas, char relleno)
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

string ToString (string la_cadena, int num_casillas, char relleno)
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






/***********************************************************************/
// Constructor sin argumentos.
// Inicializa el objeto con la fecha actual.

Fecha :: Fecha (void)
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream oss;
	oss << put_time (&tm, "%d/%m/%Y");
	auto cad = oss.str();
	
	dia  = stoi(cad.substr(0,2));	 
	mes  = stoi(cad.substr(3,2));	  	
	anio = stoi(cad.substr(6,4));
}

/***************************************************************************/
// Constructor directo. 
// Parámetros: trivial. 
// PRE: 1 <= el_dia <= 31 
// PRE: 1 <= el_mes <= 12
// PRE: 1900 <= el_anio	

Fecha :: Fecha (int el_dia, int el_mes, int el_anio)
		        : dia (el_dia), mes (el_mes), anio (el_anio)
{ }

/***************************************************************************/
// Constructor desde un string.
// Parámetros: cad, string con la fecha. 
// PRE: cad contiene una fecha CORRECTA en formato dd/mm/aaaa 
// PRE: cad.length() == 10	

Fecha :: Fecha (string cad)
{
	PonerFecha (cad);
}

/***********************************************************************/
// Métodos Get

int Fecha :: GetDia (void) const
{
	return dia; 
}

int Fecha :: GetMes (void) const
{
	return mes; 
}

int Fecha :: GetAnio (void) const
{
	return anio; 
}

/***************************************************************************/
// Serializa un dato Fecha.

string Fecha :: ToString (void) const
{
	const string MESES[] = {"Enero     ", "Febrero   ", "Marzo     ", 
							"Abril     ", "Mayo      ", "Junio     ", 
							"Julio     ", "Agosto    ", "Septiembre", 
							"Octubre   ", "Noviembre ", "Diciembre "};
	string cad; 
	
	cad = cad + ::ToString(dia,  2, ' ') + " " +  MESES[mes-1] + " " + 
		        ::ToString(anio, 4, ' ');
	
	return cad; 
}

/***********************************************************************/
// Operadores relacionales
// Devuelve: un valor bool

/***************************************************************************/
// Operador ==

bool Fecha :: operator == (const Fecha & otro) const
{
	return (dia == otro.GetDia() && mes == otro.GetMes() && 
			anio == otro.GetAnio());
}

/***************************************************************************/
// Operador !=

bool Fecha :: operator != (const Fecha & otro) const
{
	return (!((*this) == otro));
}

/***************************************************************************/
// Operador >

bool Fecha :: operator  > (const Fecha & otro) const
{
	bool mayor = false;
	
	if (anio > otro.anio)
		mayor = true;
	else {
		if (anio == otro.anio && mes > otro.mes)
			mayor = true;
		else if (anio == otro.anio && mes == otro.mes && dia > otro.dia)
			mayor = true;
	}
	
	return mayor;
}

/***************************************************************************/
// Operador <=

bool Fecha :: operator <= (const Fecha & otro) const
{
	return (!((*this) > otro));
}

/***************************************************************************/
// Operador <

bool Fecha :: operator  < (const Fecha & otro) const
{
	return (!((*this) > otro) && !((*this) == otro));
}

/***************************************************************************/
// Operador >=

bool Fecha :: operator >= (const Fecha & otro) const
{
	return (((*this) > otro) || ((*this) == otro));
}

/***********************************************************************/
// Sobrecarga de los operadores >> y <<

istream & operator >> (istream & entrada, Fecha & la_fecha)
{
	string cadena;
	
	entrada >> cadena;
	
	la_fecha.PonerFecha (cadena);
	
	return entrada;
}

ostream & operator << (ostream & salida, const Fecha & la_fecha)
{
	salida << setfill('0') << setw(2) << la_fecha.dia << "/" 
		   << setfill('0') << setw(2) << la_fecha.mes << "/" 
		   << setfill('0') << setw(4) << la_fecha.anio;
	
	return salida;
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//	MÉTODOS PRIVADOS DE LA CLASE Fecha
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/***********************************************************************/
// Establece la fecha desde un string.
// Parámetros: cad, string con la fecha. 
// PRE: cad contiene una fecha CORRECTA en formato dd/mm/aaaa
// PRE: cad.length() == 10

void Fecha :: PonerFecha (const string & cad)
{
	dia  = stoi(cad.substr(0,2));
	mes  = stoi(cad.substr(3,2));
	anio = stoi(cad.substr(6,4));
}



