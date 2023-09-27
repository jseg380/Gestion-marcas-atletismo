# C++  
  
Proyecto de la asignatura Metodología de la Programación, realizado en C++:  
  
## Gestión de marcas de atletismo  
  
El proyecto en su fase final consiste en crear un programa que reciba por la línea de comandos un archivo que contenga  
nombres de "archivos de marcas", los cuales tienen un formato específico definido arbitrariamente (incluidos archivos   
de marcas de demostración en la carpeta "data"). Los ficheros pueden ser binarios o archivos de texto.  
  
### El programa  
  
El programa recoge todas las marcas que hay en los ficheros de marcas y crea una matriz en la que cada fila contiene  
un vector con todas las marcas de una prueba.  
  
Con el objetivo pedagógico de aplicar conceptos de POO (Programación Orientada a Objetos) se hace uso de diversas clases  
y ya que la cantidad de marcas a leer no está definida con anterioridad se requiere el uso de vectores dinámicos,  
controlando la memoria dinámica con las herramientas que C++ posee.  
  
Después de haber leído y categorizado todas las marcas, se ordenan según el criterio de ordenación establecido (ordenación  
por tiempo y fecha son los dos criterios ya implementados pero se pueden añadir más ) y se muestran por salida estándar.  
Si además se ha especificado un segundo argumento, se guarda la matriz en un fichero cuyo nombre es el argumento.  
