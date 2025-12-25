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

#include "grafo.h"

void GRAFO :: destroy() {
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		//A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	//A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura) {
    ElementoLista  dummy;
    ifstream textfile;
    textfile.open(nombrefichero);
    // Si el archivo abrió bien
    if (textfile.is_open()) {
        errorapertura = 0;
        unsigned i, j, k;
        // Leemos el numero de nodos, arcos y el atributo dirigido
        textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
        // Creamos las n listas de sucesores
        LS.resize(n);
        // Leemos los m arcos
        for (k=0; k < m; ++k) {
            textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c; 
            //Inicializamos j c que son los atributos del struct ElmentoLista
            // Si es dirigido (sucesores y predecesores)
            if (Es_dirigido() == true) { 
                //Redimensionamos LP
                LP.resize(n);      
                //Situamos en la posición del nodo i a dummy mediante push_back           
                dummy.j =  j - 1;   
                LS[i-1].push_back(dummy); 
                dummy.j =  i - 1;
                LP[j-1].push_back(dummy);
            }

            // Si no es dirigido
            if (Es_dirigido() == false) {
                dummy.j = i-1;
                LS[j-1].push_back(dummy);
                // Nos aseguramos de que se haga un doble push back
                // en caso de un bucle en un grafo no dirigido
                if (i!= j) {
                    dummy.j = j-1;
                    LS[i-1].push_back(dummy);
                }
            }
        }
    } 
    else {
        // Si el archivo no abrió bien
        errorapertura = 1;                
    }		
}

void GRAFO::ListaPredecesores() {

}

// Destructor
GRAFO::~GRAFO() {
	destroy();
}

// Constructor
GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    // Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    // Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build (nombrefichero, errorapertura);
}

// Si es dirigido o no
unsigned GRAFO::Es_dirigido() {
    return dirigido;
}

// Información del grafo
void GRAFO::Info_Grafo() {
    std::cout << "Grafo ";
    dirigido == 1 ? std::cout << "dirigido" : std::cout << "no dirigido";
    std::cout << " | Número de nodos: " << n << " | Número de";
    dirigido == 1 ? std::cout << " arcos: " : std::cout << " aristas: ";
    std::cout << m << std::endl;
}

// Mostrar una lista
void Mostrar_Lista(vector<LA_nodo> L) {
    for (int t{0}; t < L.size(); ++t) {
        std::cout << "[" << (t+1) << "] :";
        if (L[t].empty()) std::cout << " 0";
        for (int h{0}; h < L[t].size(); ++h) {
            std::cout << " / " << (L[t][h].j + 1) << " (" << L[t][h].c << ")";
        }
        std::cout << std::endl;
    }
}

// Qué lista va a ser mostrada
void GRAFO :: Mostrar_Listas (int l) {
    vector<LA_nodo> L;
    if (l == 1 || l == 0) {
        L = LS;
        l == 1 ? std::cout << "Nodos de la lista de sucesores" << std::endl : std::cout << "Nodos de la lista de adyacencia" << std::endl;
    } 
    else {
        L = LP;
        std::cout << "Nodos de la lista de predecesores" << std::endl;
    }
    std::cout << "Formato: / nodo (coste) /" << std::endl;
    Mostrar_Lista(L);
}

void GRAFO::Mostrar_Matriz() {//Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) {//Recorrido en profundidad recursivo con recorridos enum y postnum

	visitado[i] = true;
    prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j=0;j<L[i].size();j++)
        if (!visitado[L[i][j].j]){
            dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
        };
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

void GRAFO::RecorridoProfundidad() {
}

void GRAFO::bfs_num(unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) {//vector de distancias a nodo i+1
//Recorrido en amplitud con la construcción de pred y d: usamos la cola

    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);  
    visitado[i-1] = true;
 
    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i-1] = i;
    d[i-1] = 0;

    queue<unsigned> cola;               //creamos e inicializamos la cola
    cola.push(i);                       //iniciamos el recorrido desde el nodo i+1
    bool ajuste_desfase = true;
    while (!cola.empty()) {             //al menos entra una vez al visitar el nodo i+1 y continúa hasta que la cola se vacíe
        unsigned k = cola.front();      //cogemos el nodo k+1 de la cola
        cola.pop();                     //lo sacamos de la cola

        //Hacemos el recorrido sobre L desde el nodo k+1
        if (ajuste_desfase == true) {
            ajuste_desfase = false;
            k = k - 1;
        }
        for (unsigned h=0;h<L[k].size();h++) {
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no está visitado
            unsigned nodo = L[k][h].j;
            if(visitado[nodo] == false) {      //Si el nodo u no está visitado
                visitado[nodo] = true;         //Lo visitamos
                cola.push(nodo);               //Lo metemos en la cola
                pred[nodo] = k+1;              //le asignamos el predecesor
                d[nodo] = d[k]+1;              //le calculamos su etiqueta distancia
            }
        }
        //Hemos terminado pues la cola está vacía
    }
}

void GRAFO::RecorridoAmplitud() { //Construye un recorrido en amplitud desde un nodo inicial
    unsigned int i;
    vector<LA_nodo> L(LS);
    vector<unsigned> pred;
    vector<unsigned> d;
    std::cout << "Vamos a construir un recorrido en amplitud" << std::endl;
    std::cout << "Elija nodo de partida [1 - " << n << "]: ";
    std::cin >> i;
    if (i <= 0) {
        std::cerr << "Error: nodo ingresado no válido." << std::endl;
        exit(EXIT_SUCCESS);
    }
    std::cout << "Nodo inicial: " << i << std::endl << std::endl;
    bfs_num(i,L,pred,d);
    bool aux = true;
  
  
    for (unsigned int t{0}; t < d.size(); ++t) {
        aux = false;
        for (unsigned int h{0}; h < d.size();++h) {
            if(d[h] == t && pred[h] != 0) {
                if (aux == false) std::cout << "Distancia " << t << " aristas";
                aux = true;
                std::cout << " : " << (h+1);
            }
        }
        if (aux == false) break;
        std::cout << std::endl;
    }
  
    std::cout << std::endl;
    std::cout << "Ramas de conexión en el recorrido:" <<std::endl;

    for (unsigned int t{1}; t < pred.size(); ++t) {
        for (unsigned int h{0}; h < d.size(); ++h) {

            vector<unsigned int> v_temp;
            if (d[h] == t && pred[h] != 0) {
                unsigned int temp = h+1;
                v_temp.push_back(temp);
                while (pred[(temp-1)] != i) {
                    temp = pred[temp-1];
                    if (temp != i) v_temp.push_back(temp);
                }
                std::cout << i;
                for (unsigned int x{v_temp.size()}; x > 0; --x ) {
                    std::cout << " - " << v_temp[x-1];
                 }
                std::cout << std::endl;
            }

        }
    }

  
}

void GRAFO::MinimoCoste() {
   
        // Declaro el contador T
        unsigned int T;
        // Vector para comprobar nodos visitados
        vector<bool> M(n, 0);
        // Vector predecesor y coste
        vector<unsigned> pred(n, 0);
        vector<int> coste(n, 9999);
        // Coste del árbol
        int total_coste = 0;
        // Nodo
        unsigned u = 0;

        std::cout << "Recorrido de amplitud a mínimo costo" << std::endl;
        std::cout << "Empezamos en el nodo 1" << std::endl;
        coste[0] = 0;

        // Mientras el contador de iteraciones sea menor al nº de nodos
        while (T < n)
        {
            // Recorremos toda la lista de sucesores
            for (int i = 0; i < LS[u].size(); i++)
            {
                // Si el nodo no está visitado y el coste de dicho nodo es menor al coste guardado
                // guardo el coste actual y guardo el nodo actual como predecesor antes de pasar al siguiente
                if (M[LS[u][i].j] == false && LS[u][i].c < coste[LS[u][i].j])
                {
                    coste[LS[u][i].j] = LS[u][i].c;
                    pred[LS[u][i].j] = u;
                }
            }
            // pred

            int mincost = 9999;
            // Recorro todos los nodos
            for (int i = 0; i < n; ++i)
            {
                // Si el nodo no está visitado y el coste de ese nodo es menor al
                // coste mínimo encontrado, guardo el coste como mínimo
                if (M[i] == false && coste[i] < mincost)
                {
                    mincost = coste[i];
                    u = i;
                }
            }
            // Nodo visitado
            M[u] = 1;
            // Iteración hecha
            T += 1;
        }                                                                                                                                                                                                               

        // Recorro todos los nodos
        for (int i = 1; i < n; ++i)
        {
            if (coste[i] != 9999)
            {
                std::cout << "Coste del nodo " << pred[i] +1 << " al nodo "
                          << i + 1 << ": " << coste[i] << std::endl;
                total_coste += coste[i];
            }
        }
        std::cout << "Coste total del recorrido: " << total_coste << std::endl;
    }