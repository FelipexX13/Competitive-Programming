# <3
# Tema: LeetCode Hub / Fuerza Bruta con Poda
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (limit^2); por inclusion-exclusion seria (1)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2928 "Distribute Candies Among Children I": repartir n dulces entre 3 ninos sin que
# ninguno reciba mas de limit. Tecnica: dos ciclos anidados sobre lo que recibe el primero y el
# segundo; el tercero queda determinado. Los continue son la poda, si con lo que ya se dio mas
# 2*limit no se alcanza n, no hay caso. OJO: deja cuatro prints de depuracion adentro del ciclo,
# y con eso se vuelve lentisimo. Tambien se puede por inclusion-exclusion: C(n+2,2) menos los
# casos donde alguno pasa limit.

class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        cont = 0
        for val1 in range(limit+1):
            if(val1+2*limit < n):
                continue
            else:
                for val2 in range(limit+1):
                    if(val1+val2+limit < n or (val1==val2 and val1== n-val1-val2) or n-val1-val2 < 0):
                        continue
                    else:
                        print(val1)
                        print(val2)
                        print(n-val1-val2)
                        print("--------")
                        cont+=1
        for i in range(limit+1):
            if(i*3 == n):
                cont+=1
        return (cont)