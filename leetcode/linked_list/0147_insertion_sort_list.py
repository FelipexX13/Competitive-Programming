# <3
# Tema: LeetCode Hub / Insertion Sort en Lista Ligada
# Resumen: Ordenar una lista ligada con insercion
# O: (n^2); en lista ligada el que sirve es merge sort, (n log n)
# Detalle: LeetCode 147 "Insertion Sort List": ordenar una lista ligada con insercion. Tecnica:
# se va armando una lista ordenada aparte y cada nodo se inserta buscando su lugar desde el
# inicio. Guardar siguiente ANTES de mover actual.next es lo unico delicado, si no se pierde el
# resto de la lista. Es O(n^2). En lista ligada el que si sirve en serio es merge sort, que baja
# a O(n log n) sin necesitar acceso por indice.

class Solution:
    def insertionSortList(self, head: ListNode | None) -> ListNode | None:

        if head is None:
            return None

        ordenada = None
        actual = head

        while actual:
            siguiente = actual.next
            if ordenada is None or actual.val < ordenada.val:
                actual.next = ordenada
                ordenada = actual
            else:
                p = ordenada

                while p.next and p.next.val < actual.val:
                    p = p.next

                actual.next = p.next
                p.next = actual

            actual = siguiente

        return ordenada