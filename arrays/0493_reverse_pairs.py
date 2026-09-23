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