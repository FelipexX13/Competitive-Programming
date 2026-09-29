// <3
// Tema: Combinatorics / Ranking
// Construye el k-esimo palindromo mas pequeno lexicograficamente que se puede formar
// reordenando el string s (o "" si no existen k reordenamientos posibles). Solo arma la mitad
// izquierda del palindromo (mas el caracter central si el largo es impar) y la refleja: para
// cada posicion prueba las letras disponibles de menor a mayor y usa comb()/perms() (conteo de
// permutaciones del multiset restante, saturado a 1e6 para evitar overflow) para saber, sin
// generar todas las combinaciones, cuantos reordenamientos empiezan con esa letra y saltarselos
// si k cae mas adelante.

class Solution {
public:
    const long long LIM = 1000000;

    // C(n, r) saturado a LIM+1 si el valor real lo supera.
    // O(r), con división exacta garantizada en cada paso (identidad de binomiales),
    // en vez de armar vectores de tamaño r y simplificar con gcd (eso era O(r^2) y el cuello de botella real).
    long long comb(long long n, long long r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        long long result = 1;
        for (long long i = 1; i <= r; i++) {
            result = result * (n - i + 1) / i;
            if (result > LIM) return LIM + 1;
        }
        return result;
    }

    // Permutaciones distintas del multiset cnt[0..25] (n = total restante), saturado a LIM+1.
    long long perms(long long n, const array<int,26>& cnt) {
        long long ans = 1;
        long long restantes = n;
        for (int c = 0; c < 26; c++) {
            if (cnt[c] == 0) continue;
            long long ways = comb(restantes, cnt[c]);
            if (ways > LIM) return LIM + 1;
            if (ans > LIM / ways) return LIM + 1;
            ans *= ways;
            restantes -= cnt[c];
            if (ans > LIM) return LIM + 1;
        }
        return ans;
    }

    string smallestPalindrome(string s, int k) {
        int n = s.size();
        bool mid = (n % 2 != 0);
        char midi = mid ? s[n / 2] : '\0';
        string half = s.substr(0, n / 2);

        array<int,26> cnt{};
        long long tot = 0;
        for (char c : half) { cnt[c - 'a']++; tot++; }

        if ((long long)k > perms(tot, cnt)) return "";

        string god;
        god.reserve(half.size());
        long long cont = 0;
        long long curTot = tot;

        for (size_t i = 0; i < half.size(); i++) {
            for (int c = 0; c < 26; c++) {
                if (cnt[c] == 0) continue;
                cnt[c]--;
                curTot--;
                long long permi = perms(curTot, cnt);
                if (cont + permi < k) {
                    cont += permi;
                    cnt[c]++;
                    curTot++;
                } else {
                    god += char('a' + c);
                    break;
                }
            }
        }

        string sol = god;
        if (mid) sol += midi;
        reverse(god.begin(), god.end());
        sol += god;
        return sol;
    }
};