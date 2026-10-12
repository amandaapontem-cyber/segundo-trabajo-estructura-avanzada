#include <iostream>
using namespace std;

const int CAPACIDAD = 10;
const int NULO = -1;

class ListasCursores {
private:
    int data[CAPACIDAD];
    int next[CAPACIDAD];
    int head;
    int free_;

public:
    
    ListasCursores() {
        for (int i = 0; i < CAPACIDAD - 1; i++) {
            next[i] = i + 1; 
        }
        next[CAPACIDAD - 1] = NULO;
        free_ = 0;
        head = NULO;
    }

    
    int asignarNodo() {
        if (free_ == NULO) {
            cout << "¡Sin espacio disponible! (arreglo lleno)\n";
            return NULO;
        }
        int nodo = free_;
        free_ = next[free_];
        return nodo;
    }

   
    void liberarNodo(int idx) {
        next[idx] = free_;
        free_ = idx;
    }

  
    void insertarInicio(int valor) {
        int nuevo = asignarNodo();
        if (nuevo == NULO) return;

        data[nuevo] = valor;
        next[nuevo] = head;
        head = nuevo;
    }

    
    void eliminarValor(int valor) {
        int actual = head;
        int anterior = NULO;

      
        while (actual != NULO && data[actual] != valor) {
            anterior = actual;
            actual = next[actual];
        }

        if (actual == NULO) {
            cout << "Valor " << valor << " no encontrado.\n";
            return;
        }

        
        if (anterior == NULO) {
            head = next[actual]; 
        } else {
            next[anterior] = next[actual];
        }

        liberarNodo(actual);
    }

    
    void imprimir() {
        int actual = head;
        cout << "Lista: ";
        if (actual == NULO) {
            cout << "(vacía)";
        }
        while (actual != NULO) {
            cout << data[actual];
            if (next[actual] != NULO) cout << " -> ";
            actual = next[actual];
        }
        cout << "\n";
    }

   
    void mostrarEstadoInterno() {
        cout << "\n idx:  ";
        for (int i = 0; i < CAPACIDAD; i++) cout << i << "\t";
        cout << "\n data: ";
        for (int i = 0; i < CAPACIDAD; i++) cout << data[i] << "\t";
        cout << "\n next: ";
        for (int i = 0; i < CAPACIDAD; i++) cout << next[i] << "\t";
        cout << "\n head = " << head << " | free = " << free_ << "\n\n";
    }
};

int main() {
    ListasCursores lista;

    cout << "== Insertar 30, 20, 10 al inicio ==\n";
    lista.insertarInicio(30);
    lista.insertarInicio(20);
    lista.insertarInicio(10);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    cout << "== Eliminar el valor 20 ==\n";
    lista.eliminarValor(20);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    cout << "== Insertar 40 al inicio (reutiliza el espacio liberado) ==\n";
    lista.insertarInicio(40);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    return 0;
}