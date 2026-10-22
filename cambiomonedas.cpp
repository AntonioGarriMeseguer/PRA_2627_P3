#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función para resolver el problema del cambio de monedas mediante Programación Dinámica
vector<int> calcularCambioMonedas(const vector<int>& V, int M) {
    int n = V.size();
    int NONE = -1; // Representa el valor no alcanzable
    
    // Crear la tabla T de tamaño n x (M + 1) inicializada a NONE (-1)
    vector<vector<int>> T(n, vector<int>(M + 1, NONE));
    
    // Caso base: T[0, 0] = 0
    T[0][0] = 0;
    
    // Cálculo de la primera fila
    for (int j = 1; j <= M; ++j) {
        if (j >= V[0] && T[0][j - V[0]] != NONE) {
            T[0][j] = 1 + T[0][j - V[0]];
        }
    }
    
    // Cálculo del resto de la tabla
    for (int i = 1; i < n; ++i) {
        T[i][0] = 0;
        for (int j = 1; j <= M; ++j) {
            if (j < V[i] || T[i][j - V[i]] == NONE) {
                T[i][j] = T[i - 1][j];
            } else if (T[i - 1][j] != NONE) {
                T[i][j] = min(T[i - 1][j], 1 + T[i][j - V[i]]);
            } else {
                T[i][j] = 1 + T[i][j - V[i]];
            }
        }
    }
    
    // Recuperar la solución (recorrido hacia atrás)
    vector<int> Sol(n, 0);
    int i = n - 1;
    int j = M;
    
    while (i != 0 && j != 0) {
        if (i == 0 || T[i][j] != T[i - 1][j]) {
            Sol[i] = Sol[i] + 1;
            j = j - V[i];
        } else {
            i = i - 1;
        }
    }
    
    // Ajuste para la primera moneda si el bucle se detiene en i = 0
    while (j > 0 && i == 0) {
        Sol[0] = Sol[0] + 1;
        j = j - V[0];
    }
    
    return Sol;
}

int main() {
    vector<int> V = {1, 4, 6};
    int M = 8;
    
    vector<int> solucion = calcularCambioMonedas(V, M);
    
    cout << "Monedas utilizadas para el cambio de " << M << ":" << endl;
    for (size_t i = 0; i < V.size(); ++i) {
        cout << "Moneda de " << V[i] << ": " << solucion[i] << " unidades" << endl;
    }
    
    return 0;
}
