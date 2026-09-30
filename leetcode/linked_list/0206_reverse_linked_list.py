# <3
# Tema: LeetCode Hub / Invertir Lista Ligada
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 206 "Reverse Linked List": invertir la lista.
# Tecnica del codigo: pasar los valores a un arreglo y reconstruir la lista al reves. Funciona
# pero gasta O(n) de memoria.
# La forma clasica, que vale la pena tener de memoria, son tres punteros: prev = None y en cada
# paso guardar nxt = act.next, apuntar act.next = prev, y correr prev = act, act = nxt. Al final
# prev es la nueva cabeza. Es O(1) de memoria y cinco lineas.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if(head is None):
            return head

        nodos = []
        while head != None:
            nodos.append(head.val)
            head = head.next
        
        prev = ListNode(nodos[len(nodos)-1])
        q = prev
        for i in range(len(nodos)-2,-1,-1):
            act = ListNode(nodos[i])
            prev.next = act
            prev = prev.next

        return q

