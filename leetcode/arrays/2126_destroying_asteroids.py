# <3
# Tema: LeetCode Hub / Greedy Creciente
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n log n) por el sort
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2126 "Destroying Asteroids": la nave absorbe la masa de cada asteroide que destruye;
# decir si puede con todos. Tecnica: ordenar y atacar del mas pequeno al mas grande. Si en ese
# orden no alcanza para alguno, no alcanza en ningun orden, porque cualquier otro orden llega
# ahi con la misma masa o menos. Ese argumento de intercambio es lo que justifica el greedy.

class Solution:
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:
        asteroids = sorted(asteroids)
        
        for i in asteroids:
            if(mass>=i):
                mass+=i
            else:
                return False
        return True