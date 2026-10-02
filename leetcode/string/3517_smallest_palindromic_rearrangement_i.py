# <3
# Tema: LeetCode Hub / Palindromo Lexicograficamente Menor
# Resumen: Reordenar las letras para formar el palindromo alfabeticamente menor
# O: (n + 26), frecuencias y armar las dos mitades
# Detalle: LeetCode 3517 "Smallest Palindromic Rearrangement I": reordenar las letras para
# formar el palindromo alfabeticamente menor. Tecnica: se cuentan las letras, se parte cada
# cuenta a la mitad y la primera mitad se escribe en orden alfabetico; el centro es la unica
# letra que quedo impar y la segunda mitad es el reverso. Poner las letras chicas primero es lo
# que minimiza, y como el palindromo obliga a que la segunda mitad sea el espejo, no hay nada
# mas que decidir.

class Solution:
    def smallestPalindrome(self, s: str) -> str:
        t = [
            "a","b","c","d","e","f","g",
            "h","i","j","k","l","m","n",
            "o","p","q","r","s","t","u",
            "v","w","x","y","z"
        ]
        dic = {}
        for i in s:
            if(i not in dic):
                dic[i] = 1
            else:
                dic[i]+=1

        ini = ""
        for i in t:
            if(i in dic and dic[i] > 1):
                cant = dic[i]//2
                dic[i] -= cant*2
                agre = i*cant
                ini+=agre
        
        mitad = ""
        for i in t:
            if(i in dic and dic[i] == 1):
                mitad = i
        
        fin = ini[::-1]
        resp = ini + mitad + fin
        return resp