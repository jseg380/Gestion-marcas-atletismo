/***************************************************************************/
/***************************************************************************/
//
// Autor: Juan Manuel Segura Duarte
//
// Definición de las funciones declaradas en el fichero VectorMarcas.h
//
// Fichero: VectorMarcas.cpp
//
/***************************************************************************/
/***************************************************************************/

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#include "VectorMarcas.h"


////////////////////////////////////////////////////////////
// Constructores y destructor

/***********************************************************************/
// Constructor sin argumentos.
// Crea un array vacío.
// Necesario para poder crear arrays.

VectorMarcas :: VectorMarcas (void)
			 : etiqueta(""),
			   num_marcas(0),
			   capacidad(0),
			   las_marcas(nullptr)
{
}

/***********************************************************************/
// Constructor con un argumento.
// Crea un array con un único elemento.
// Parámetros: registro, el elemento que contendrá el array
//			   nombre, etiqueta del registro

VectorMarcas :: VectorMarcas (RegistroDeMarca registro, string nombre)
{
	etiqueta = nombre;
	ReservaMemoria (1);
	num_marcas = 1;
	las_marcas[0] = registro;
}

/***********************************************************************/
// Constructor con dos argumentos.
// Parámetros: nombre, nombre que tendrá la etiqueta
//			   tamanio, número de casillas que se reservarán para el vector.
// PRE: 0 < tamanio

VectorMarcas :: VectorMarcas (string nombre, int tamanio)
{
	if (tamanio > 0) { // Solo si se cumplen las precondiciones se actua
		etiqueta = nombre;
		num_marcas = 0;
		ReservaMemoria (tamanio);
	}
}

/***********************************************************************/
// Construye un objeto de VectorMarcas a partir de un fichero de prueba.
// Parámetros: nombre, nombre del fichero del que se lee el vector

VectorMarcas :: VectorMarcas (const string & nombre)
{
	las_marcas = nullptr;
	LeerVectorMarcas (nombre);
}

/***********************************************************************/
// Construye un objeto de VectorMarcas a partir de un fichero de marcas.
// Parámetros: nombre, nombre del fichero de marcas
//			   nombre_prueba, prueba que contendrá el vector

VectorMarcas :: VectorMarcas (const string & nombre_fichero, 
							  const string & nombre_prueba)
{
	ifstream fi (nombre_fichero);
	
	string cadena;
	
	getline (fi, cadena);	// Coger la cadena mágica
	
	if (cadena == "MARCAS") {
		
		// Reservar memoria
		
		ReservaMemoria (TAMANIO_BLOQUE);
		
		// Saltar comentarios
		
		while (fi.peek() == '#')
			getline (fi, cadena);
		
		getline (fi, cadena);
		
		while (!fi.eof()) {
			
			istringstream iss (cadena);
			string prueba;
			RegistroDeMarca registro;
			
			iss >> prueba;
			
			if (prueba == nombre_prueba) {
				iss >> registro;
				
				(*this) += registro;
			}
			
			getline (fi, cadena);
		}
	}
}

/***********************************************************************/
// Constructor de copia.

VectorMarcas :: VectorMarcas (const VectorMarcas & otro)
{
	ReservaMemoria (otro.capacidad);
	CopiaDatos (otro);
}

/***********************************************************************/
// Destructor.

VectorMarcas :: ~VectorMarcas (void)
{
	LiberaMemoria ();
}



////////////////////////////////////////////////////////////
// Métodos Get

string VectorMarcas :: Etiqueta (void)
{
	return etiqueta;
}

int VectorMarcas :: NumMarcas (void)
{
	return num_marcas;
}

int VectorMarcas :: Capacidad (void)
{
	return capacidad;
}


////////////////////////////////////////////////////////////
// Método Set

void VectorMarcas :: SetEtiqueta (string nueva_etiqueta)
{
	etiqueta = nueva_etiqueta;
}



/***********************************************************************/
// Elimina el vector

void VectorMarcas :: Elimina (void)
{
	LiberaMemoria();
}

/***********************************************************************/
// Ajusta el vector para que ocupe el mínimo número de casillas posible.

void VectorMarcas :: Ajusta (void)
{
	// Solo hay que ajustar el vector si la capacidad es superior al
	// número de marcas guardadas (casillas ocupadas)
	
	if (num_marcas < capacidad){
		
		// Se guarda la información actual
		
		VectorMarcas antiguo = (*this);
		
		// Se reserva memoria para un vector que tenga la capacidad mínima
		// indispensable
		
		ReservaMemoria (num_marcas);
		
		// Se copian los datos del vector antiguo al actual
		
		CopiaDatos (antiguo);
		
		// Se libera la memoria que ocupa el vector antiguo con el destructor
	}
}

/***********************************************************************/
// Ordena un vector VectorMarcas.

void VectorMarcas :: Ordena (void)
{
	for (int izda = 0 ; izda < num_marcas ; izda++){
		
		// Calcula el menor registro en el subvector desordenado
		// (Esto dependerá de cual sea el criterio escogido para ordenar)
		
		RegistroDeMarca minimo = las_marcas[izda];
		int pos_min = izda;
		
		for (int i = izda + 1 ; i < num_marcas ; i++)
			if (las_marcas[i] < minimo){
				minimo = las_marcas[i];
				pos_min = i;
			}
		
		// Intercambia los valores guardados en "izda" y "pos_min"
		
		RegistroDeMarca temporal = las_marcas[izda];
		las_marcas[izda] = las_marcas[pos_min];
		las_marcas[pos_min] = temporal;
	}
}

/***********************************************************************/
// Convierte a string un vector VectorMarcas.

string VectorMarcas :: ToString (void)
{
	string cad;
	
	for (int i = 0 ; i < num_marcas ; i++)
		cad += las_marcas[i].ToString() + "\n";
	
	return cad;
}

/***********************************************************************/
// Guarda un dato VectorMarcas en un fichero de texto llamado nombre . El
// fichero será un fichero de prueba.
// Parámetros: nombre, nombre del fichero en el que se escribe el vector

void VectorMarcas :: EscribirVectorMarcas (const string & nombre) const
{
	if (num_marcas > 0) {
		ofstream fo (nombre);
		
		fo << "PRUEBA" << endl;
		
		fo << (*this);
	}
}

/***********************************************************************/
// Lee un dato VectorMarcas de un fichero de texto llamado nombre . El 
// fichero será un fichero de prueba.
// Parámetros: nombre, nombre del fichero del que se lee el vector

void VectorMarcas :: LeerVectorMarcas (const string & nombre)
{
	LiberaMemoria();
	
	ifstream fi (nombre);
	
	string cadena;
	
	getline (fi, cadena);
	
	if (cadena == "PRUEBA") {
		
		// Saltar comentarios
		
		while (fi.peek() == '#')
			getline (fi, cadena);
		
		fi >> (*this);
	}
}

/***********************************************************************/
// Operador de asignación (Copia profunda)
// Devuelve: un objeto de la misma clase

VectorMarcas & VectorMarcas :: operator = (const VectorMarcas & otro)
{
	if (this != &otro) { // Evitar autoasignación
		
		// Se libera la memoria que estaban ocupando los datos actuales
		
		LiberaMemoria ();
		
		// Se reserva memoria para alojar los nuevos datos
		
		ReservaMemoria (otro.capacidad);
		
		// Se copian los datos desde otro al objeto implícito
		
		CopiaDatos (otro);
	}
	
	return (*this);
}

/***********************************************************************/
// Sobrecarga del operador ()
// Accede a un elemento del vector dado su índice.
// Parámetros: indice, posición del elemento al que se accede
// Devuelve: el elemento en la posición (indice)
//
// PRE: 1 <= indice <= num_marcas

RegistroDeMarca & VectorMarcas :: operator () (const int indice)
{
	return el_elemento (indice);
}

RegistroDeMarca & VectorMarcas :: operator () (const int indice) const
{
	return el_elemento (indice);
}

/***********************************************************************/
// Sobrecarga del operador []
// Accede a un elemento del vector dado su índice.
// Parámetros: indice, posición del elemento al que se accede
// Devuelve: el elemento en la posición (indice)
//
// PRE: 1 <= indice <= num_marcas

RegistroDeMarca & VectorMarcas :: operator [] (const int indice)
{
	return el_elemento (indice);
}

RegistroDeMarca & VectorMarcas :: operator [] (const int indice) const
{
	return el_elemento (indice);
}

/***********************************************************************/
// Operadores relacionales
// NOTA: El criterio son las etiquetas de las pruebas, i.e. 1500ML > 100ML

bool VectorMarcas :: operator == (VectorMarcas otro)
{
	// Para que dos marcas sean iguales sus etiquetas deben ser idénticas

	return (etiqueta == otro.etiqueta);
}

bool VectorMarcas :: operator != (VectorMarcas otro)
{
	return (!((*this) == otro));
}

bool VectorMarcas :: operator <  (VectorMarcas otro)
{
	// Separar el número de las letras de la etiqueta

	string cadena = "";
	int num1, num2;
	bool terminado = false;

	for (int i = 0 ; i < etiqueta.length() && !terminado; i++) {
		if (etiqueta[i] >= '0' && etiqueta[i] <= '9')
			cadena += etiqueta[i];
		else
			terminado = true;
	}

	num1 = stoi (cadena);
	cadena = "";
	terminado = false;

	for (int i = 0 ; i < otro.etiqueta.length() && !terminado; i++) {
		if (otro.etiqueta[i] >= '0' && otro.etiqueta[i] <= '9')
			cadena += otro.etiqueta[i];
		else
			terminado = true;
	}

	num2 = stoi (cadena);


	return (num1 < num2);
}

bool VectorMarcas :: operator >= (VectorMarcas otro)
{
	return (!((*this) < otro));
}

bool VectorMarcas :: operator >  (VectorMarcas otro)
{
	return (!((*this) >= otro) && ((*this) != otro));
}

bool VectorMarcas :: operator <= (VectorMarcas otro)
{
	return (!((*this) > otro));
}

/***********************************************************************/
// Operadores binarios + y -

// Operador +

// Versión 1: [VectorMarcas] + [VectorMarcas]
// PRE: Los dos vectores son de la misma prueba
//		i.e. vector1.Etiqueta() == vector2.Etiqueta()

VectorMarcas operator + (const VectorMarcas & vector1,
						 const VectorMarcas & vector2)
{
	VectorMarcas resultado;	// Por defecto vector vacío
	
	if (vector1.etiqueta == vector2.etiqueta) {
		
		VectorMarcas suma (vector1.etiqueta,
						   vector1.num_marcas + vector2.num_marcas);
		
		// Copia los datos de vector1 a suma
		
		suma.CopiaDatos (vector1);
		
		// Copia los datos de vector2 a suma
		
		for (int i = 0 ; i < vector2.num_marcas ; i++)
			suma.las_marcas[i + vector1.num_marcas] = vector2.las_marcas[i];
		
		// Se actualizan los campos
		
		suma.num_marcas = vector1.num_marcas + vector2.num_marcas;
		
		resultado = suma;
	}
	
	return resultado;
}

// Versión 2: [VectorMarcas] + [RegistroDeMarca]
// NOTA: Se da por hecho que el registro a añadir
//		 es de la misma prueba

VectorMarcas operator + (const VectorMarcas & vector,
						 const RegistroDeMarca & registro)
{
	// Se crea un vector a partir del registro
	
	VectorMarcas vector_registro (registro, vector.etiqueta);
	
	// Se añade el registro al final
	
	return (vector + vector_registro);
}

// Versión 3: [RegistroDeMarca] + [VectorMarcas]
// NOTA: Se da por hecho que el registro a añadir
//		 es de la misma prueba

VectorMarcas operator + (const RegistroDeMarca & registro,
						 const VectorMarcas & vector)
{
	// Se crea un vector a partir del registro
	
	VectorMarcas vector_registro (registro, vector.etiqueta);
	
	// Se añade el registro al principio
	
	return (vector_registro + vector);
}

// Operador -

// Versión única: [VectorMarcas] - [string]

VectorMarcas operator - (const VectorMarcas & vector, const string una_licencia)
{
	// Se crea un vector con capacidad suficiente para almacenar todos los
	// registros de vector
	
	VectorMarcas copia_vector (vector.etiqueta, vector.num_marcas);
	
	/* Con memmove
	VectorMarcas copia_vector (vector);
	// Se eliminan del vector los registros con esa licencia
	
	// PROBLEMAS con sizeof
	
	int i = 1;
	
	while (i <= copia_vector.num_marcas) {
		if (copia_vector[i].GetLicencia() == una_licencia) {
			memmove (copia_vector[i], copia_vector[i+1], 
					 (copia_vector.num_marcas - i) * sizeof (RegistroDeMarca));
			
			copia_vector.num_marcas--;
		}
		else
			i++;
	}
	*/
	// Se copian en copia_vector todos los valores de vector que no tengan
	// la licencia indicada en el segundo argumento
	
	for (int i = 1 ; i <= vector.num_marcas ; i++)
		if (vector[i].GetLicencia() != una_licencia)
			copia_vector += vector[i];
	
	return copia_vector;
}

/***********************************************************************/
// Sobrecarga de los operadores combinados += y -=

// Operador +=

// Versión 1: [VectorMarcas] += [VectorMarcas]

VectorMarcas & VectorMarcas :: operator += (const VectorMarcas & vector)
{
	(*this) = (*this) + vector;
	
	return (*this);
}

// Versión 2: [VectorMarcas] += [RegistroDeMarca]

VectorMarcas & VectorMarcas :: operator += (const RegistroDeMarca & registro)
{
	(*this) = (*this) + registro;
	
	return (*this);
}

// Operador -=

//Versión única: [VectorMarcas] -= [string]

VectorMarcas & VectorMarcas :: operator -= (const string & una_licencia)
{
	(*this) = (*this) - una_licencia;
	
	return (*this);
}

/***********************************************************************/
// Sobrecarga de los operadores >> y <<

istream & operator >> (istream & entrada, VectorMarcas & vector)
{
	vector.LiberaMemoria();
	
	int tamanio;
	
	entrada >> vector.etiqueta;
	
	entrada >> tamanio;
	
	vector.ReservaMemoria (tamanio);
	
	RegistroDeMarca registro;
	
	for (int i = 0 ; i < tamanio ; i++) {
		entrada >> registro;
		vector += registro;
	}
	
	return entrada;
}

ostream & operator << (ostream & salida, const VectorMarcas & vector)
{
	if (vector.num_marcas > 0) {
		
		salida << vector.etiqueta << endl;
		
		salida << vector.num_marcas;
		
		for (int i = 0 ; i < vector.num_marcas ; i++)
			salida << endl << vector.las_marcas[i];
	}
	
	return salida;
}






///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//	MÉTODOS PRIVADOS DE LA CLASE VectorMarcas
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


/***********************************************************************/
// Reserva memoria para los datos de un vector de marcas con "tamanio"
// número de casillas.
// El contenido de las casillas queda INDEFINIDO.
// Parámetros:
//		tamanio, número de casillas del vector.
// PRE: 0 < tamanio

void VectorMarcas :: ReservaMemoria (int tamanio)
{
	if (tamanio > 0){ // Solo si se cumplen las precondiciones se actua
		las_marcas = new RegistroDeMarca [tamanio];
		
		capacidad = tamanio; // Se establece la nueva capacidad
		num_marcas = 0;
	}
}

/***********************************************************************/
// Libera la memoria ocupada por un vector de marcas.
// POST: El vector queda vacío (todos sus campos a cero).

void VectorMarcas :: LiberaMemoria (void)
{
	if (las_marcas) { // Solo se libera memoria si el puntero apunta a "algo"
		
		delete [] las_marcas;
		
		// Establece todos los campos a 0
		
		etiqueta = "";
		num_marcas = 0;
		capacidad = 0;
		las_marcas = nullptr;
	}
}

/***********************************************************************/
// Copia datos desde otro objeto de la misma clase. (Copia profunda).
// PRE: Se ha reservado memoria para los datos.

void VectorMarcas :: CopiaDatos (const VectorMarcas & otro)
{
	// Copia los registros haciendo uso de memcpy
	
	// PROBLEMA CON MEMCPY
	// Si se usa el delete [] las_marcas da problemas pero si se ejecuta el
	// programa utilizando memcpy y no haciendo uso de delete [] (para que
	// pueda ejecutarse), entonces funciona correctamente, por lo que parece
	// que memcpy funciona correctamente "a medias". No sé cuál puede ser el
	// problema.
	//memcpy (las_marcas, otro.las_marcas,
	//		otro.num_marcas * sizeof (RegistroDeMarca));
	
	for (int i = 0 ; i < otro.num_marcas ; i++)
		las_marcas[i] = otro.las_marcas[i];
	
	// Establece los campos igual que en el otro
	
	etiqueta = otro.etiqueta;
	num_marcas = otro.num_marcas;
}

/***********************************************************************/
// Redimensiona un vector VectorMarcas con redimensión por bloques.

void VectorMarcas :: Redimensiona (void)
{
	// Se almacenan los datos actuales
	
	VectorMarcas antiguo (*this);
	
	// Se libera la memoria ocupada por el vector actual
	
	LiberaMemoria ();
	
	// Se reserva memoria para un vector con más espacio
	
	ReservaMemoria (antiguo.capacidad + TAMANIO_BLOQUE);
	
	// Se copian los datos del vector antiguo al actual
	
	CopiaDatos (antiguo);
	
	// Se libera la memoria que ocupa el vector antiguo con el destructor
}

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

RegistroDeMarca & VectorMarcas :: el_elemento (int indice) const
{
	return las_marcas[indice - 1];
}


/***********************************************************************/
