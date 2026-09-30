# <3
# Tema: LeetCode Hub / Comparar un Binario con su Reverso
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3750 "Minimum Number of Flips to Reverse Binary String": cuantos bits hay que
# cambiar para que el binario de n sea igual a su reverso.
# Tecnica: bin(n)[2:] da el binario sin el 0b, el reverso sale con [::-1], y se cuentan las
# posiciones donde no coinciden. Sin bitmask ni desplazamientos, todo por string.

class Solution:
    def minimumFlips(self, n: int) -> int:
        bi = bin(n)[2:]
        bini = bi[::-1]
        cont = 0
        for i in range(len(bi)):
            if(bi[i]!=bini[i]):
                cont+=1
        return cont

        