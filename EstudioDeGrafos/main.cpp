 /**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author S. Laya González
 * @date APR 13 2023
 * @brief Works with graphs
 *
 */

#include <string.h>
#include "grafo.h"


void menu (unsigned dirigido, char &opcion) {
    //Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
    cout << "Optimiza!cion en Grafos, 2022-2023 Sebsatián Laya González" << endl;
    cout << "c. [c]argar grafo desde fichero" << endl;
    if (dirigido == 0) { //Grafo no dirigido
        cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
        cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
        cout << "r. Realizar un [r]ecorrido en amplitud del grafo desde un nodo por sucesores" << endl;
	    //Aquí se añaden más opciones al menú del grafo no dirigido
    } 
    else {
        cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
        cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
        cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
        cout << "r. Realizar un [r]ecorrido en amplitud del grafo desde un nodo por sucesores" << endl; 
	    //Aquí se añaden más opciones al menú del grafo dirigido
    }
    cout << "m. Realizar un recorrido en amplitud del grafo asumiendo el coste [m]ínimo" << endl;
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
}


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
int main(int argc, char *argv[]) {
    int error_apertura;
    char nombrefichero[85], opcion;
    //system("clear");
    //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
    if (argc > 1) {
        cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    } 
    else {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    }
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1) {
        cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
        //pressanykey();
        //system("clear");
    } 
    else {
        cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
        //pressanykey();
        //system("clear");
    do {
        menu(G.Es_dirigido(), opcion);
        switch (opcion) {
        case 'c' :
            //system("clear");
            std::cout << std::endl << "===========" << std::endl << std::endl;
            cout << "Introduce el nombre completo del fichero de datos" << endl;
            cin >> nombrefichero;
            G.actualizar(nombrefichero, error_apertura);
            if (error_apertura == 1) {
                cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
            } 
            else {
                cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
            }
            std::cout << std::endl << "===========" << std::endl << std::endl;
            //pressanykey();
            //system("clear");
            break;

        case 'i' :
            //system("clear");
            std::cout << std::endl << "===========" << std::endl << std::endl;
            cout << "Grafo cargado desde " << nombrefichero << endl;
            G.Info_Grafo();
            //pressanykey();
            //system("clear");
            std::cout << std::endl << "===========" << std::endl << std::endl;
            break;

		case 's':
            std::cout << std::endl << "===========" << std::endl << std::endl;
            G.Mostrar_Listas(1);
            std::cout << std::endl << "===========" << std::endl << std::endl;
            break;

		case 'p':
            std::cout << std::endl << "===========" << std::endl << std::endl;
            G.Mostrar_Listas(-1);
            std::cout << std::endl << "===========" << std::endl << std::endl;
            break;       
        
		case 'r':
            std::cout << std::endl << "===========" << std::endl << std::endl;
            G.RecorridoAmplitud();
            std::cout << std::endl << "===========" << std::endl << std::endl;
            break;
        
		case 'a':
            std::cout << std::endl << "===========" << std::endl << std::endl;
            G.Mostrar_Listas(0);
            std::cout << std::endl << "===========" << std::endl << std::endl;
            break;

        case 'm':
            std::cout << std::endl << "===========" << std::endl << std::endl;
            G.MinimoCoste();
            std::cout << std::endl << "===========" << std::endl << std::endl;
            break;
        }
    }   
    while (opcion != 'q');
    }
    cout << "Fin del programa" << endl;
	return(0);
}