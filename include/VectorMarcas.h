/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Declaración de VectorMarcas y sus funciones
// Definición de las funciones en el fichero VectorMarcas.cpp
//
// Fichero: VectorMarcas.h
//
/***************************************************************************/
/***************************************************************************/

#ifndef VECTOR_MARCAS
#define VECTOR_MARCAS

#include "ClaseRegistroDeMarca.h"


/////////////////////////////////////////////////////////////////////////////
// VectorMarcas

class VectorMarcas {

private:
	
	// Redimensión del vector en bloques de tamaño TAMANIO_BLOQUE
	
	static const int TAMANIO_BLOQUE = 5;
	
	string etiqueta;				// Nombre de la prueba
	int num_marcas;					// Número de marcas guardadas
	int capacidad;					// Número de casillas reservadas
	RegistroDeMarca * las_marcas;	// Puntero para acceder a las marcas

public:
	
	////////////////////////////////////////////////////////////
	// Constructores y destructor
	
	/***********************************************************************/
	// Constructor sin argumentos.
	// Crea un array vacío.
	// Necesario para poder crear arrays.

	VectorMarcas (void);
	
	/***********************************************************************/
	// Constructor con dos argumento.
	// Crea un array con un único elemento.
	// Parámetros: registro, el elemento que contendrá el array
	//			   nombre, etiqueta del registro

	VectorMarcas (RegistroDeMarca registro, string nombre = "");
	
	/***********************************************************************/
	// Constructor con dos argumentos.
	// Parámetros: nombre, nombre que tendrá la etiqueta
	//			   tamanio, número de casillas que se reservarán para el vector
	// PRE: 0 < tamanio

	VectorMarcas (string nombre, int tamanio);
	
	/***********************************************************************/
	// Construye un objeto de VectorMarcas a partir de un fichero de prueba.
	// Parámetros: nombre, nombre del fichero del que se lee el vector
	
	VectorMarcas (const string & nombre);
	
	/***********************************************************************/
	// Construye un objeto de VectorMarcas a partir de un fichero de marcas.
	// Parámetros: nombre, nombre del fichero de marcas
	//			   nombre_prueba, prueba que contendrá el vector
	
	VectorMarcas (const string & nombre_fichero, const string & nombre_prueba);
	
	/***********************************************************************/
	// Constructor de copia.

	VectorMarcas (const VectorMarcas & otro);

	/***********************************************************************/
	// Destructor.

	~VectorMarcas (void);
	
	
	
	////////////////////////////////////////////////////////////
	// Métodos Get
	
	string Etiqueta (void);
	int NumMarcas (void);
	int Capacidad (void);
	
	////////////////////////////////////////////////////////////
	// Método Set
	
	void SetEtiqueta (string nueva_etiqueta);
	
	
	/***********************************************************************/
	// Elimina el vector

	void Elimina (void);
	
	/***********************************************************************/
	// Ajusta el vector para que ocupe el mínimo número de casillas posible.

	void Ajusta (void);

	/***********************************************************************/
	// Ordena un vector VectorMarcas.

	void Ordena (void);

	/***********************************************************************/
	// Convierte a string un vector VectorMarcas.

	string ToString (void);
	
	/***********************************************************************/
	// Guarda un dato VectorMarcas en un fichero de texto llamado nombre . El
	// fichero será un fichero de prueba.
	// Parámetros: nombre, nombre del fichero en el que se escribe el vector
	
	void EscribirVectorMarcas (const string & nombre) const;
	
	/***********************************************************************/
	// Lee un dato VectorMarcas de un fichero de texto llamado nombre . El 
	// fichero será un fichero de prueba.
	// Parámetros: nombre, nombre del fichero del que se lee el vector
	
	void LeerVectorMarcas (const string & nombre);
	
	/***********************************************************************/
	// Operador de asignación (Copia profunda)
	// Devuelve: un objeto de la misma clase
	
	VectorMarcas & operator = (const VectorMarcas & otro);
	
	/***********************************************************************/
	// Sobrecarga del operador ()
	// Accede a un elemento del vector dado su índice.
	// Parámetros: indice, posición del elemento al que se accede
	// Devuelve: el elemento en la posición (indice)
	//
	// PRE: 1 <= indice <= num_marcas
	
	RegistroDeMarca & operator () (const int indice);
	
	RegistroDeMarca & operator () (const int indice) const;
	
	/***********************************************************************/
	// Sobrecarga del operador []
	// Accede a un elemento del vector dado su índice.
	// Parámetros: indice, posición del elemento al que se accede
	// Devuelve: el elemento en la posición (indice)
	//
	// PRE: 1 <= indice <= num_marcas
	
	RegistroDeMarca & operator [] (const int indice);
	
	RegistroDeMarca & operator [] (const int indice) const;

	/***********************************************************************/
	// Operadores relacionales
	// NOTA: Se comparán las pruebas, i.e. 1500ML > 100ML

	bool operator == (VectorMarcas otro);

	bool operator != (VectorMarcas otro);

	bool operator <  (VectorMarcas otro);

	bool operator >= (VectorMarcas otro);

	bool operator >  (VectorMarcas otro);

	bool operator <= (VectorMarcas otro);
	
	/***********************************************************************/
	// Operadores binarios + y -
	
	// Operador +
	
	// Versión 1: [VectorMarcas] + [VectorMarcas]
	// PRE: Los dos vectores son de la misma prueba
	//		i.e. vector1.Etiqueta() == vector2.Etiqueta()
	
	friend VectorMarcas operator + (const VectorMarcas & vector1,
									const VectorMarcas & vector2);
	
	// Versión 2: [VectorMarcas] + [RegistroDeMarca]
	// NOTA: Se da por hecho que el registro a añadir
	//		 es de la misma prueba
	
	friend VectorMarcas operator + (const VectorMarcas & vector,
									const RegistroDeMarca & registro);
	
	// Versión 3: [RegistroDeMarca] + [VectorMarcas]
	// NOTA: Se da por hecho que el registro a añadir
	//		 es de la misma prueba
	
	friend VectorMarcas operator + (const RegistroDeMarca & registro,
									const VectorMarcas & vector);
	
	// Operador -
	
	// Versión única: [VectorMarcas] - [string]
	
	friend VectorMarcas operator - (const VectorMarcas & vector,
									const string una_licencia);
	
	/***********************************************************************/
	// Sobrecarga de los operadores combinados += y -=
	
	// Operador +=
	
	// Versión 1: [VectorMarcas] += [VectorMarcas]
	
	VectorMarcas & operator += (const VectorMarcas & vector);
	
	// Versión 2: [VectorMarcas] += [RegistroDeMarca]
	
	VectorMarcas & operator += (const RegistroDeMarca & registro);
	
	// Operador -=
	
	//Versión única: [VectorMarcas] -= [string]
	
	VectorMarcas & operator -= (const string & una_licencia);
	
	/***********************************************************************/
	// Sobrecarga de los operadores >> y <<
	
	friend istream & operator >> (istream & entrada, VectorMarcas & vector);
	
	friend ostream & operator << (ostream & salida,
								  const VectorMarcas & vector);




private:
	
	/***********************************************************************/
	// Reserva memoria para los datos de un vector de marcas con "tamanio"
	// número de casillas.
	// El contenido de las casillas queda INDEFINIDO.
	// Parámetros:
	//		tamanio, número de casillas del vector.
	// PRE: 0 < tamanio

	void ReservaMemoria (int tamanio);
	
	/***********************************************************************/
	// Libera la memoria ocupada por un vector de marcas.
	// POST: El vector queda vacío (todos sus campos a cero).

	void LiberaMemoria (void);
	
	/***********************************************************************/
	// Copia datos desde otro objeto de la misma clase. (Copia profunda).
	// PRE: Se ha reservado memoria para los datos.

	void CopiaDatos (const VectorMarcas & otro);
	
	/***********************************************************************/
	// Redimensiona un vector VectorMarcas con redimensión por bloques.

	void Redimensiona (void);
	
	/***********************************************************************/
	// Método PRIVADO compartido por: 
	// 		RegistroDeMarca & operator () (const int indice);
	// 		RegistroDeMarca & operator () (const int indice) const;
	// 		RegistroDeMarca & operator [] (const int indice);
	// 		RegistroDeMarca & operator [] (const int indice) const;
	// para evitar la duplicidad de código.
	//
	// Devuelve una referencia a un dato RegistroDeMarca del vector
	// dado su posición.
	// PRE: 1 <= indice <= num_marcas

	RegistroDeMarca & el_elemento (int indice) const;
};

#endif
