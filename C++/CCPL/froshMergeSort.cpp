// <3
// Tema: Divide and Conquer / Conteo de Inversiones con Merge Sort
// Resumen: La otra forma de resolver "Frosh Week" (problema F, CCPL)
// O: (n log n), inversiones contando en la fusion
// Detalle: La otra forma de resolver "Frosh Week" (problema F, CCPL), la misma del archivo
// "frosh" pero sin ninguna estructura de datos. La equivalencia del problema es la misma: el
// minimo de intercambios de vecinos para ordenar la fila es exactamente el numero de
// INVERSIONES. LA IDEA, Y ES DE LAS MAS BONITAS QUE HAY: un merge sort ya compara todas las
// parejas que importan, solo que normalmente tira esa informacion. Al mezclar dos mitades YA
// ORDENADAS, en el momento en que se toma un elemento de la derecha (R[j]) porque es menor que
// L[i], ese elemento es menor que L[i] Y QUE TODOS LOS QUE LE SIGUEN EN L, porque L esta
// ordenada. Como todos ellos estan a la izquierda en el arreglo original, ahi hay n1 - i
// inversiones de golpe. Esa sola linea, respuesta += n1 - i, convierte un ordenamiento en un
// contador. POR QUE SE PUEDEN SUMAR LAS PARTES: toda inversion (i, j) cae en exactamente uno de
// tres casos, las dos dentro de la mitad izquierda, las dos dentro de la derecha, o una en cada
// mitad. Las dos primeras las cuentan las llamadas recursivas y la tercera la cuenta el merge,
// sin solaparse ni dejar ninguna afuera. De ahi sale el O(n log n). EL DETALLE QUE PARECE
// TRIVIAL Y NO LO ES: la comparacion tiene que ser L[i] <= R[j], con el igual del lado
// izquierdo. Si se pone < , los elementos iguales se toman de la derecha y se cuentan como
// inversiones, lo que da de mas. En este problema los numeros de estudiante son todos distintos
// y no se nota, pero en cualquier otro con repetidos si. long long en el contador: con n = 10^6
// al reves salen casi 5*10^11 inversiones. DOS COSAS QUE LE CUESTAN TIEMPO A ESTA VERSION Y NO
// SE VEN (medido, n = 10^6 aleatorio): tal como esta 624 ms agregandole
// ios::sync_with_stdio(false) 452 ms ademas con UN solo buffer en vez de crear L y R 360 ms Lo
// primero es que leer 10^6 enteros con cin sin desactivar la sincronizacion con stdio cuesta
// mas que todo el algoritmo. Lo segundo es que crear dos vectores DENTRO de merge significa ~2
// millones de asignaciones de memoria; con un unico buffer del tamano del arreglo reservado una
// sola vez, se hace una. Asi arreglada es la version mas rapida y la que menos memoria usa (~8
// MB contra los ~16 MB del Fenwick, que guarda el arreglo, su copia ordenada y el bit de long
// long). La de Fenwick se queda en el cuaderno porque se generaliza a otras preguntas; esta
// solo cuenta inversiones. Verificado contra la version de Fenwick con n = 10^6 en tres
// escenarios (aleatorio, invertido y ya ordenado): identicas, 250188280112 en el aleatorio.

#include <bits/stdc++.h>
#include <vector>

using namespace std;

long long respuesta = 0;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            respuesta += n1 - i;
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

int main() {

    int n = 0;

    while(cin >> n){

        respuesta = 0;
        vector <int> arr;


        for(int i = 0; i < n; i++){
            int num = 0;
            cin >> num;
            arr.push_back(num);
        }

        mergeSort(arr, 0, arr.size() - 1);
        cout << respuesta << endl;
    }

    return 0;
}
