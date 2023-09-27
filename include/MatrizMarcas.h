/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Declaración de MatrizMarcas y sus funciones
// Definición de las funciones en el fichero MatrizMarcas.cpp
//
// Fichero: MatrizMarcas.h
//
/***************************************************************************/
/***************************************************************************/

#ifndef MATRIZ_MARCAS
#define MATRIZ_MARCAS

#include "VectorMarcas.h"


/////////////////////////////////////////////////////////////////////////////
// MatrizMarcas

class MatrizMarcas {

private:
	
	int num_pruebas;				// Número de filas
	VectorMarcas * pruebas;			// Puntero para acceder a las filas

public:
	
	////////////////////////////////////////////////////////////
	// Constructores y destructor
	
	/***********************************************************************/
	// Constructor sin argumentos.
	// Por defecto matriz vacía.

	MatrizMarcas (void);
	
	/***********************************************************************/
	// Constructor con un argumento.
	// Parámetros: capacidad, número de filas que tendrá la matriz
	// PRE: 0 < capacidad

	MatrizMarcas (int capacidad);
	
	/***********************************************************************/
	// Construye un objeto de MatrizMarcas a partir de un fichero de marcas.
	// Parámetros: nombre, nombre del fichero de marcas
	
	MatrizMarcas (const string & nombre);
	
	/***********************************************************************/
	// Constructor de copia.

	MatrizMarcas (const MatrizMarcas & otra);
	
	/***********************************************************************/
	// Destructor.

	~MatrizMarcas (void);
	
	
	
	////////////////////////////////////////////////////////////
	// Método Get
	
	int NumPruebas (void);
	
	
	
	/***********************************************************************/
	// Ajusta una matriz MatrizMarcas para que ocupe el mínimo 
	// número de casillas posible.

	void Ajusta (void);

	/***********************************************************************/
	// Ordena una matriz MatrizMarcas.

	void Ordena (void);

	/***********************************************************************/
	// Convierte a string información útil sobre una matriz MatrizMarcas.

	string ToStringInfo (void);

	/***********************************************************************/
	// Convierte a string una matriz MatrizMarcas.
	// Parámetros:  mensaje, mensaje que mostrará como título

	string ToString (const string mensaje = "Ranking general 2021");
	
	/***********************************************************************/
	// Guarda un dato MatrizMarcas en un fichero llamado nombre . El
	// fichero será un fichero de marcas.
	// Parámetros: nombre, nombre del fichero en el que se guarda la matriz
	//			   txt, variable booleana que determina si el fichero es
	//					de texto o binario
	
	void EscribirMatrizMarcas (const string & nombre, bool txt = true) const;
	
	/***********************************************************************/
	// Lee un dato MatrizMarcas de un fichero llamado nombre . El 
	// fichero será un fichero de marcas.
	// Parámetros: nombre, nombre del fichero de marcas
	//			   txt, variable booleana que determina si el fichero es
	//					de texto o binario
	
	void LeerMatrizMarcas (const string & nombre, bool txt = true);
	
	/***********************************************************************/
	// Operador de asignación (Copia profunda)
	// Devuelve: un objeto de la misma clase
	
	MatrizMarcas & operator = (const MatrizMarcas & otra);
		
	/***********************************************************************/
	// Sobrecarga del operador ()
	// Accede a un vector de la matriz dado su índice.
	// Parámetros: indice, posición del vector al que se accede
	// Devuelve: el vector en la posición (indice)
	//
	// PRE: 1 <= indice <= num_marcas

	VectorMarcas & operator () (int indice);

	VectorMarcas & operator () (int indice) const;

	/***********************************************************************/
	// Sobrecarga del operador ()
	// Accede a un elemento de la matriz dado sus índices.
	// Parámetros: fila, fila en la que está el elemento
	//			   columna, columna en la que está el elemento
	// Devuelve: el elemento en la posición (fila, columna)
	//
	// PRE: 1 <= fila <= num_marcas
	// PRE: 1 <= columna <= la_fila (fila).num_marcas

	RegistroDeMarca & operator () (int fila, int columna);

	RegistroDeMarca & operator () (int fila, int columna) const;

	/***********************************************************************/
	// Sobrecarga del operador []
	// Accede a un elemento del vector dado su índice.
	// Parámetros: indice, posición del elemento al que se accede
	// Devuelve: el elemento en la posición (indice)
	//
	// PRE: 1 <= indice <= num_marcas

	VectorMarcas & operator [] (int indice);

	VectorMarcas & operator [] (int indice) const;
	
	/***********************************************************************/
	// Operadores binarios + y -
	
	// Operador +
	
	// Versión 1: [MatrizMarcas] + [MatrizMarcas]
	
	friend MatrizMarcas operator + (const MatrizMarcas & matriz1,
							 const MatrizMarcas & matriz2);
	
	// Versión 2: [MatrizMarcas] + [VectorMarcas]
	
	friend MatrizMarcas operator + (const MatrizMarcas & matriz,
							 const VectorMarcas & vector);
	
	// Versión 3: [VectorMarcas] + [MatrizMarcas]
	
	friend MatrizMarcas operator + (const VectorMarcas & vector,
							 const MatrizMarcas & matriz);
	
	// Operador -
	
	// Versión única: [MatrizMarcas] - [string]
	
	friend MatrizMarcas operator - (const MatrizMarcas & matriz,
							 const string una_licencia);
	
	/***********************************************************************/
	// Sobrecarga de los operadores combinados += y -=
	
	// Operador +=
	
	// Versión 1: [MatrizMarcas] += [MatrizMarcas]
	
	MatrizMarcas & operator += (const MatrizMarcas & matriz);
	
	// Versión 2: [MatrizMarcas] += [VectorMarcas]
	
	MatrizMarcas & operator += (const VectorMarcas & vector);
	
	// Operador -=
	
	//Versión única: [MatrizMarcas] -= [string]
	
	MatrizMarcas & operator -= (const string & una_licencia);
	
	/***********************************************************************/
	// Sobrecarga de los operadores >> y <<
	
	friend istream & operator >> (istream & entrada, MatrizMarcas & matriz);
	
	friend ostream & operator << (ostream & salida, 
								  const MatrizMarcas & matriz);
void OrdenaPruebas (void);




private:
	
	/***********************************************************************/
	// Reserva memoria para los datos de una matriz de marcas con "tamanio"
	// número de filas.
	// Parámetros: tamanio, número de filas de la matriz.
	// PRE: 0 < tamanio

	void ReservaMemoria (int tamanio);
	
	/***********************************************************************/
	// Libera la memoria ocupada por una matriz de marcas.
	// POST: La matriz queda vacía (todos sus campos a cero).

	void LiberaMemoria (void);
	
	/***********************************************************************/
	// Copia datos desde otro objeto de la misma clase. (Copia profunda).
	// PRE: Se ha reservado memoria para los datos.

	void CopiaDatos (const MatrizMarcas & otra);
	
	/***********************************************************************/
	// Elimina las pruebas repetidas fusionándolas en un único VectorMarcas.

	void AjustaPruebas (void);
	
	/***********************************************************************/
	// Une dos pruebas dados sus índices.
	// Parámetros: intacta, índice de la prueba que contendrá al resultado
	//			   a_eliminar, índice de la prueba a unir

	void UnePruebas (const int intacta, const int a_eliminar);
	
	/***********************************************************************/
	// Ordena las pruebas de una matriz de marcas.

	//void OrdenaPruebas (void);
	
	/***********************************************************************/
	// Método PRIVADO compartido por: 
	//      VectorMarcas & operator () (int indice);
	//		VectorMarcas & operator () (int indice) const;
	//      VectorMarcas & operator [] (int indice);
	//		VectorMarcas & operator [] (int indice) const;
	// para evitar la duplicidad de código.
	//
	// Devuelve una referencia a una fila de la matriz dada su posición.
	// PRE: 1 <= indice < num_pruebas

	VectorMarcas & la_fila (int indice) const;

	/***********************************************************************/
	// Método PRIVADO compartido por: 
	//      RegistroDemarca & operator () (int columna);
	//		RegistroDeMarca & operator () (int fila) const;
	// para evitar la duplicidad de código.
	// Devuelve una referencia a un elemento de la matriz dada su posición.
	//
	// PRE: 1 <= fila <= num_marcas
	// PRE: 1 <= columna <= la_fila (fila).num_marcas

	RegistroDeMarca & el_elemento (int fila, int columna) const;
	
	/***********************************************************************/
	// Guarda un dato MatrizMarcas en un fichero de texto llamado nombre . El
	// fichero será un fichero de marcas.
	// Parámetros: nombre, nombre del fichero en el que se guarda la matriz
	
	void EscribirMatrizMarcasTxt (const string & nombre) const;
	
	/***********************************************************************/
	// Guarda un dato MatrizMarcas en un fichero binario llamado nombre . El
	// fichero será un fichero de marcas.
	// Parámetros: nombre, nombre del fichero en el que se guarda la matriz
	
	void EscribirMatrizMarcasBin (const string & nombre) const;
	
	/***********************************************************************/
	// Lee un dato MatrizMarcas de un fichero de texto llamado nombre . El 
	// fichero será un fichero de marcas.
	// Parámetros: nombre, nombre del fichero de marcas
	
	void LeerMatrizMarcasTxt (const string & nombre);
	
	/***********************************************************************/
	// Lee un dato MatrizMarcas de un fichero binario llamado nombre . El 
	// fichero será un fichero de marcas.
	// Parámetros: nombre, nombre del fichero de marcas
	
	void LeerMatrizMarcasBin (const string & nombre);
};

#endif
