# <3
# Tema: LeetCode Hub / Contar en la Fusion del Merge Sort
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 493 "Reverse Pairs": contar pares i < j con nums[i] > 2 * nums[j].
# Tecnica: la de contar inversiones, pero con el 2. Durante el merge sort, al fusionar dos
# mitades YA ordenadas, un puntero j avanza mientras izquierda[i] > 2*derecha[j] y suma j
# pares de golpe. Es O(n log n) y el patron sirve para cualquier condicion monotona.
# El puntero j NO se reinicia en cada i, y eso es lo que lo deja lineal por fusion.

class Solution:
    def reversePairs(self, nums: list[int]) -> int:

        def merge_sort(arr):
            if len(arr) <= 1:
                return 0

            mitad = len(arr) // 2

            izquierda = arr[:mitad]
            derecha = arr[mitad:]

            cantidad = merge_sort(izquierda)
            cantidad += merge_sort(derecha)

            # Contar reverse pairs
            j = 0

            for i in range(len(izquierda)):
                while j < len(derecha) and izquierda[i] > 2 * derecha[j]:
                    j += 1

                cantidad += j

            # Merge
            i = 0
            j = 0
            k = 0

            while i < len(izquierda) and j < len(derecha):

                if izquierda[i] <= derecha[j]:
                    arr[k] = izquierda[i]
                    i += 1
                else:
                    arr[k] = derecha[j]
                    j += 1

                k += 1

            while i < len(izquierda):
                arr[k] = izquierda[i]
                i += 1
                k += 1

            while j < len(derecha):
                arr[k] = derecha[j]
                j += 1
                k += 1

            return cantidad

        return merge_sort(nums)