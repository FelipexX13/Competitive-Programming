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