# <3
# Tema: LeetCode Hub / Heap por Fecha de Vencimiento
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n log n), un heap por fecha de vencimiento
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1705 "Maximum Number of Eaten Apples": cada dia aparecen manzanas que se danan en
# cierta fecha y se puede comer una por dia; maximizar cuantas se comen. Tecnica: heap minimo
# con la pareja (dia en que se dana, cuantas quedan). Cada dia se come de las que vencen
# PRIMERO, que es el greedy correcto: guardar una que vence lejos nunca es peor que guardar una
# que vence ya. OJO: usa try/except para detectar el heap vacio en vez de revisar el tamano.

import heapq

class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        heap = []
        d = 0
        c = 0
        while True:
            if(d<len(days)):
                heapq.heappush(heap, (days[d]+d, apples[d]))
            if (not heap):
                break
            try:
                menor,quedan = heapq.heappop(heap)
                while menor<=d or quedan < 1:  
                    menor,quedan = heapq.heappop(heap)
                quedan -= 1    
                c+= 1              
                heapq.heappush(heap, (menor,quedan)) 
            except: 
                d+=1
                continue 
            d+=1
        return c