# <3
# Tema: LeetCode Hub / Simulacion de Cola
# Resumen: Segundos hasta que la persona en la posicion k termine de comprar, con la fila rotando
# O: (n * tickets) simulando; con la formula seria (n)
# Detalle: LeetCode 2073 "Time Needed to Buy Tickets": segundos hasta que la persona en la
# posicion k termine de comprar, con la fila rotando. Tecnica: rotar la lista con pop(0) y
# append restando uno, y mover k con ella. Sale directo sin simular sumando por persona
# min(tickets[i], tickets[k]) y un +1 para los que van despues de k, pero la simulacion es facil
# de escribir bajo presion.

class Solution:
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        c = 0
        while tickets[k] != 0:
            j = tickets[0]
            if(j>0):
                c+=1
            tickets.pop(0)
            tickets.append(j-1)
            k -= 1
            if(k < 0):
                k = len(tickets)-1            
        return c