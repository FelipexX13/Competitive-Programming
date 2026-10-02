# <3
# Tema: LeetCode Hub / Palindromo Filtrando Caracteres
# Resumen: Palindromo ignorando mayusculas, espacios y signos
# O: (n), un filtro y dos punteros
# Detalle: LeetCode 125 "Valid Palindrome": palindromo ignorando mayusculas, espacios y signos.
# Tecnica: primero se limpia la cadena dejando solo letras y digitos, y despues se compara con
# dos punteros desde las puntas. OJO: deja un print(guar). En Python el filtro sale mas corto
# con i.isalnum().

class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = s.lower()
        lt = ["a","b","c","d","e","f","g","h","i","j",
                "k","l","m","n","o","p","q","r","s","t",
                "u","v","w","x","y","z"
            ]

        n = ["0","1","2","3","4","5","6","7","8","9"]

        guar = ""
        for i in range(0,len(s)):
            if ((s[i] in lt) or (s[i] in n)):        
                guar += s[i]

        print(guar)

        total = len(guar)

        for i in range(0,total):
            if guar[i] != guar[total-1]:
                return False
            total = total - 1

        return True

                