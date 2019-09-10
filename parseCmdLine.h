#ifndef PARSECMDLINE_H
#define PARSECMDLINE_H

/*
	PARSE COMMAND LINE
	parseCmdLine es una funcion encargada de procesar los argumentos recibidos por l�nea de comandos.

	NOTA:
		Opciones: constan de 2 argumentos; una clave, precedida por "-", y su valor.
	Ejemplo: progrma.exe -clave argumento
	El valor puede comenzar con "-"
		Par�metros: constan de 1 argumento, el cual NO puede comenzar con "-"
	Ejemplo: programa.exe argumento

	Recibe:
		argc, contador de argumentos;
		argv, vector de argumentos; estos dos datos son recibidos por el main del programa usuario, y deben ser
	pasados a parseCmdLine tal como son recibidos al iniciar el programa
		p, puntero a funci�n callback. Esta funci�n debe ser definida por el usuario, y debe ser capaz de
	interpretar y evaluar la validez de las opciones y par�metros pasados por l�nea de comandos, para preparar
	al programa principal para su accionar
		userData, puntero gen�rico. parseCmdLine no modifica ni lee el contenido apuntado; unicamente pasa dicho
	puntero a la funci�n Callback. �ste es el medio por el cual el Callback se comunicar� con el programa principal

	Devuelve:
		N�mero de argumentos y opciones ingresadas.
		En caso de error (opci�n sin clave o valor, argumento inv�lido), devuelve -1.

	Modo de uso:
		En primer lugar, el usuario deber� programar un callback. �ste recibir� de parseCmdLine dos cadenas de
	caracteres por cada opci�n o par�metro le�do desde la l�nea de comandos; el primero (key) contiene la clave de
	la opci�n ingresada (sin el "-"), o es un puntero nulo en caso de haberse ingresado un par�metro. El segundo
	(value), contiene el valor de la opci�n pasada, o el contenido del par�metro, seg�n corresponda.
		En funci�n del parametro u opci�n recibida, el Callback debe informar al programa principal de las operaciones
	que �ste deber� realizar una vez finalizada la lectura de la l�nea de comandos. Para ello, dispone de un puntero
	gen�rico (userData), cuyo contenido e inicializaci�n deben ser definidas por el usuario. Estos Datos del Usuario,
	idealmente, deben ser modificados ante cada llamado al Callback, seg�n los datos pasados, y luego deben ser
	interpretados por el programa principal.
		El Callback deber� informarle a parseCmdLine si la opci�n o par�metro ingresados son v�lidos; en caso
	afirmativo, deber� devolver 1; de presentarse un error en la interpretaci�n, deber� devolver 0.

		Una vez programado el Callback, y habiendo definido los Datos del Usuario, para llamar a parseCmdLine
	es necesario entregarle los valores de argc y argv (recibidos por el main), donde argc contiene el n�mero de
	argumetos pasados al programa, y argv es un arreglo de punteros a cadenas de caracteres, los cuales contienen
	dichos argumentos.
		parseCmdLine devuelve el n�mero de opciones y argumentos ingresados por el usuario. De ocurrir un error
	durante la lectura (par�metro inv�lido, opci�n sin clave o valor, cadena de caracteres vac�a), devuelve -1,
	e imprime en l�nea de comandos el error producido, indicando el argumento conflictivo.

	CONSIDERACIONES:
	-Las cadenas de caracteres pasadas al Callback (mediante sus punteros) NO son una copia, sin� las originales,
	accesibles mediante argv. Al no crear cadenas auxiliares para pasar los argumentos, se evita la necesidad de
	definir una longitud m�xima para los mismos. Se desalienta la modificaci�n de estas cadenas por el Callback;
	el uso de �sta librer�a permite eliminar la necesidad de manipular de manera directa los argumentos pasados
	por l�nea de comandos.


*/

typedef int (*pCallback) (char *key, char *value, void *userData);

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

#endif