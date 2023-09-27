/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Fichero: ClaseRegistroDeMarca.h
//
/***************************************************************************/
/***************************************************************************/

#ifndef CLASE_REGISTRO_DE_MARCA
#define CLASE_REGISTRO_DE_MARCA

#include "ClaseFecha.h"
#include "ClaseTiempo.h"
#include "ClaseLicencia.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////
// Registro de marca

class RegistroDeMarca {

private:
	Fecha fecha_marca;			// Fecha de la marca 
	Licencia licencia;			// Licencia del atleta
	Tiempo tiempo_marca;		// Tiempo registrado

public :

	/***********************************************************************/
	// Constructor sin argumentos. 
	// Necesario para crear arrays o matrices.

	RegistroDeMarca (void); 

	/***********************************************************************/
	// Constructor directo. 
	// Parámetros: trivial. 

	RegistroDeMarca (Fecha la_fecha_marca, string la_licencia, 
		             Tiempo el_tiempo_marca);
	
	/***********************************************************************/
	// Constructor de copia. 
	// Parámetros: trivial.
	
	RegistroDeMarca (const RegistroDeMarca & otro);

	/***********************************************************************/
	// Métodos Get

	Fecha  GetFecha	   (void) const;
	string GetLicencia (void) const;
	Tiempo GetTiempo   (void) const;
	
	/***********************************************************************/
	// Serializa un dato RegistroDeMarca.

	string  ToString (void) const;
	
	/***********************************************************************/
	// Operadores relacionales
	// Devuelve: un valor bool
	
	bool operator == (const RegistroDeMarca & otro) const;
	
	bool operator != (const RegistroDeMarca & otro) const;
	
	bool operator  > (const RegistroDeMarca & otro) const;
	
	bool operator <= (const RegistroDeMarca & otro) const;
	
	bool operator  < (const RegistroDeMarca & otro) const;
	
	bool operator >= (const RegistroDeMarca & otro) const;
	
	/***********************************************************************/
	// Sobrecarga de los operadores >> y <<
	
	friend istream & operator >> (istream & entrada,
								  RegistroDeMarca & registro);
	
	friend ostream & operator << (ostream & salida,
								  const RegistroDeMarca & registro);
	
};

#endif
