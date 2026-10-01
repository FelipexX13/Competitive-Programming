# <3
# Tema: LeetCode Hub / Fusion de Listas Ligadas
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n+m), cirugia de punteros en el sitio
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 21 "Merge Two Sorted Lists": mezclar dos listas ligadas ordenadas. Tecnica del
# codigo: cirugia de punteros en el sitio, insertando los nodos de una lista dentro de la otra
# segun cual cabeza sea menor, y al final se pega la cola que sobro. OJO: es dificil de seguir y
# tiene casos simetricos duplicados. El truco que lo vuelve corto es el NODO CENTINELA: se crea
# un ListNode(0) falso, se van colgando nodos de la lista menor y al final se devuelve
# centinela.next. Asi desaparecen todos los if de bordes.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if(list1 == None and list2 == None):
            return list1
        elif(list1 == None):
            return list2
        elif(list2 == None):
            return list1
        h1 = list1
        h2 = list2
        cabeza1 = list1
        cabeza2 = list2
        if(cabeza1.val <= cabeza2.val):
            ant = cabeza1
            ant2 = cabeza2
            while (cabeza1 != None):
                if(cabeza2 == None):
                    return list1
                if(cabeza1.val >= cabeza2.val):
                    cabeza1 = ant
                    cabeza2 = cabeza2.next
                    ant2.next = cabeza1.next
                    cabeza1.next = ant2
                    ant2 = cabeza2
                ant = cabeza1
                cabeza1 = cabeza1.next

            cabeza1 = h1
            while (cabeza1.next != None):
                cabeza1 = cabeza1.next
            cabeza1.next = cabeza2
            return list1
        else:
            ant = cabeza1
            ant2 = cabeza2
            while (cabeza2 != None):
                if(cabeza1 == None):
                    return list2
                if(cabeza2.val >= cabeza1.val):
                    cabeza2 = ant2
                    cabeza1 = cabeza1.next
                    ant.next = cabeza2.next
                    cabeza2.next = ant
                    ant = cabeza1
                ant2 = cabeza2
                cabeza2 = cabeza2.next
            cabeza2 = h2
            while (cabeza2.next != None):
                cabeza2 = cabeza2.next
            cabeza2.next = cabeza1
            return list2
        
        