# <3
# Tema: LeetCode Hub / Liebre y Tortuga
# Resumen: Decir si la lista tiene un ciclo
# O: (n) tiempo y (1) memoria, que es la gracia de Floyd
# Detalle: LeetCode 141 "Linked List Cycle": decir si la lista tiene un ciclo. Tecnica: dos
# punteros, uno avanza de a uno y el otro de a dos. Si hay ciclo se encuentran; si no, el rapido
# llega al final. Es el algoritmo de Floyd y gasta O(1) de memoria, que es la ventaja sobre el
# set de visitados (como dice el comentario del autor). El mismo truco encuentra el INICIO del
# ciclo: al encontrarse, se manda uno a la cabeza y se avanzan los dos de a uno hasta que
# coincidan.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        slow = head
        fast = head

        #Puedo hacer el de visitados y sale, pero para practicar eso
        #uno mas rapido que otro

        while fast != None and fast.next!=None:
            slow = slow.next
            fast = fast.next.next

            if slow == fast:
                return True

        return False
        