# <3
# Tema: LeetCode Hub / Siguiente Mayor con Pila
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1019 "Next Greater Node In Linked List": para cada nodo, el primer valor mayor que
# aparece despues. Tecnica: pila monotona decreciente que guarda valores Y posiciones. Cuando
# llega uno mas grande, se le resuelve la respuesta a todos los de la pila que sean menores.
# Cada elemento entra y sale una vez, asi que es O(n). El patron next greater element se usa en
# muchisimos problemas; este es la version de lista ligada, pero con arreglo es identico.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        lista = []
        stack = []
        stackpos = []
        p = 0
        c = head
        while c != None:
            lista.append(0)
            while True:
                if(len(stack) != 0 and stack[-1] < c.val):
                    lista[stackpos[-1]] = c.val
                    stack.pop()
                    stackpos.pop()
                else:
                    break
            stack.append(c.val)
            stackpos.append(p)
            p+= 1
            c = c.next
            
        return lista

       
        
        