# <3
# Tema: LeetCode Hub / Avanzar hasta la Mitad
# Resumen: La mediana de dos arreglos ordenados
# O: (n+m); el problema pide O(log(n+m)) con binaria
# Detalle: LeetCode 4 "Median of Two Sorted Arrays": la mediana de dos arreglos ordenados.
# Tecnica: dos punteros que avanzan como en un merge, pero sin construir el arreglo fusionado,
# solo contando hasta llegar a la posicion del medio y guardando el anterior para el caso par.
# Es O(n+m). El problema en realidad pide O(log(n+m)), que se logra con binaria sobre el punto
# de corte de uno de los dos arreglos; esa version es bastante mas dificil de escribir bien.

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:

        i = 0
        j = 0
        val = 0
        if (len(nums1) == 0 and len(nums2)==0):
            actual = 0
        elif(len(nums1)== 0):
            actual = nums2[j]
            j+=1
        elif(len(nums2)==0):
            actual = nums1[i]
            i+=1

        elif nums1[i] < nums2[j]:
            actual = nums1[i]
            i += 1
        else:
            actual = nums2[j]
            j += 1

        p = (len(nums1) + len(nums2)) // 2

        while True:
            ant = actual

            if i < len(nums1) and j < len(nums2):

                if nums1[i] < nums2[j]:

                    if actual <= nums1[i]:
                        actual = nums1[i]
                        i += 1

                else:

                    if actual <= nums2[j]:
                        actual = nums2[j]
                        j += 1

            elif i < len(nums1):

                if actual <= nums1[i]:
                    actual = nums1[i]
                    i += 1

            elif j < len(nums2):

                if actual <= nums2[j]:
                    actual = nums2[j]
                    j += 1

            val += 1

            if val >= p:
                break

        if (len(nums1) + len(nums2)) % 2 == 1:
            return actual

        else:

            

            return (actual+ant)/2

        