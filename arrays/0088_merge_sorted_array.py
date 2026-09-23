class Solution:
    
    def combinar(self, izquierda, derecha):

        resultado = []

        i = 0
        j = 0

        while i < len(izquierda) and j < len(derecha):

            if izquierda[i] <= derecha[j]:
                resultado.append(izquierda[i])
                i += 1
            else:
                resultado.append(derecha[j])
                j += 1

        while i < len(izquierda):
            resultado.append(izquierda[i])
            i += 1

        while j < len(derecha):
            resultado.append(derecha[j])
            j += 1

        return resultado

    def merge_sort(self, arr):

        if len(arr) <= 1:
            return arr

        mitad = len(arr) // 2

        izquierda = self.merge_sort(arr[:mitad])
        derecha = self.merge_sort(arr[mitad:])

        return self.combinar(izquierda, derecha)

    def merge(self, nums1: list[int], m: int, nums2: list[int], n: int) -> None:
        resultado = self.merge_sort(nums1[:m] + nums2[:n])

        for i in range(m + n):
            nums1[i] = resultado[i]