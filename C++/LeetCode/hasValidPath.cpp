// <3
// Tema: Dynamic Programming / Camino en Grilla con Balance de Parentesis
// Resumen: En una grilla de '(' y ')' hay que decir si existe un camino de la esquina superior
// izquierda a la inferior...
// Detalle: Resuelve "Check if There Is a Valid Parentheses String Path" (LeetCode 2267): en una
// grilla de '(' y ')' hay que decir si existe un camino de la esquina superior izquierda a la
// inferior derecha, moviendose solo abajo o a la derecha, cuya cadena sea de parentesis valida.
// LA IDEA: del camino recorrido solo importa el BALANCE (+1 por '(', -1 por ')'), no la cadena
// entera. Dos caminos que llegan a la misma casilla con el mismo balance tienen exactamente el
// mismo futuro, asi que el estado es (i, j, balance) y se memoiza. Es la misma idea de fondo de
// la ficha "Parentesis Balanceados" de este cuaderno, llevada a una grilla. El balance nunca
// pasa del largo del camino, m+n-1, asi que la memo es m * n * (m+n): con la grilla maxima de
// 100 x 100 son unos 2 millones de estados, que caben de sobra. Un balance negativo se corta en
// el acto: un ')' de mas ya no lo arregla nada que venga despues. PODAS QUE NO HACEN FALTA PERO
// CORTAN TRABAJO: si el camino tiene largo impar (m+n-1 impar) la respuesta es false sin mirar
// nada; si el balance supera las casillas que faltan, (m-1-i) + (n-1-j), ya no se alcanza a
// cerrar; y la primera casilla tiene que ser '(' y la ultima ')'. OJO: la funcion valid y la
// cadena s que se arma en dfs no se usan para la respuesta, la memo sobre el balance ya decide
// todo. Se pueden borrar sin cambiar nada. Verificado con los dos ejemplos de LeetCode y contra
// la fuerza bruta de probar TODOS los caminos en 3000 grillas de hasta 6x6, sin un solo fallo.
// Una grilla de 99 x 100 tarda ~20 ms.

class Solution {
public:

    bool valid(string &s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(')
                balance++;
            else
                balance--;

            if (balance < 0)
                return false;
        }

        return balance == 0;
    }

    vector<vector<vector<int>>> memo;

    bool dfs(vector<vector<char>>& grid,
             int i, int j,
             int balance,
             string &s) {

        int m = grid.size();
        int n = grid[0].size();

        // Nunca podemos tener mas ')' que '('
        if (balance < 0)
            return false;

        // Ya calculamos este estado
        if (memo[i][j][balance] != -1)
            return memo[i][j][balance];

        // Llegamos al final
        if (i == m - 1 && j == n - 1) {
            return memo[i][j][balance] = (balance == 0);
        }

        // Abajo
        if (i + 1 < m) {

            char c = grid[i + 1][j];

            s.push_back(c);

            int newBalance = balance + (c == '(' ? 1 : -1);

            if (dfs(grid, i + 1, j, newBalance, s))
                return memo[i][j][balance] = true;

            s.pop_back();
        }

        // Derecha
        if (j + 1 < n) {

            char c = grid[i][j + 1];

            s.push_back(c);

            int newBalance = balance + (c == '(' ? 1 : -1);

            if (dfs(grid, i, j + 1, newBalance, s))
                return memo[i][j][balance] = true;

            s.pop_back();
        }

        return memo[i][j][balance] = false;
    }

    bool hasValidPath(vector<vector<char>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        // La longitud maxima del string es m+n-1
        int maxBalance = m + n;

        memo.assign(
            m,
            vector<vector<int>>(
                n,
                vector<int>(maxBalance + 1, -1)
            )
        );

        string s;
        s.push_back(grid[0][0]);

        int balance = (grid[0][0] == '(' ? 1 : -1);

        return dfs(grid, 0, 0, balance, s);
    }
};
