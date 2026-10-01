# <3
# Tema: LeetCode Hub / Suma con Acarreo en Lista Ligada
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2 "Add Two Numbers": sumar dos numeros guardados en listas ligadas, con el digito
# menos significativo primero. Tecnica: recorrer las dos listas a la vez sumando digito por
# digito, y en una segunda pasada propagar el acarreo (si pasa de 9 se le resta 10 y se suma 1
# al siguiente). Si el acarreo se sale por el final, se agrega un digito mas. Lo normal es
# hacerlo en UNA pasada con una variable carry, sin la lista intermedia.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        f = []
        cabeza1 = l1
        cabeza2 = l2
        while True:
            if(cabeza1 and cabeza2):
                v = cabeza1.val + cabeza2.val
                f.append(v)
                cabeza1 = cabeza1.next
                cabeza2 = cabeza2.next
            elif(cabeza1):
                v = cabeza1.val
                f.append(v)
                cabeza1 = cabeza1.next
            elif(cabeza2):
                v = cabeza2.val
                f.append(v)
                cabeza2 = cabeza2.next
            else:
                break

        k = []
        i = 0 
        while (i < len(f)):
            if(f[i]<=9):
                k.append(f[i])
            else:
                k.append(f[i]-10)
                if(i==len(f)-1):
                    f.append(1)
                else:
                    f[i+1] += 1
            i+=1
        final = ListNode()
        final.val = k[0]
        cabeza = final
        for i in range(1, len(k)):
            nuevo = ListNode()  
            nuevo.val = k[i]
            cabeza.next = nuevo     
            cabeza = cabeza.next 

        return final