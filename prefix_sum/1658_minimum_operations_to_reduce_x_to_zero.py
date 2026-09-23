class Solution:
    def minOperations(self, nums: list[int], x: int) -> int:
        suma1 = []
        suma2 = []
        posiciones1 = {}
        posiciones2 = {}

        s1 = 0
        s2 = 0

        for i in range(len(nums)):
            s1 += nums[i]
            s2 += nums[len(nums)-i-1]

            suma1.append(s1)
            suma2.append(s2)

            if s1 not in posiciones1:
                posiciones1[s1] = i

            if s2 not in posiciones2:
                posiciones2[s2] = i

        mejor = float("inf")

        for i in range(len(suma1)):

            if x-suma1[i] in posiciones2:
                pos = posiciones2[x-suma1[i]]

                if i + pos + 2 <= len(nums):
                    best = i + pos + 2
                    if best < mejor:
                        mejor = best

            if x-suma2[i] in posiciones1:
                pos = posiciones1[x-suma2[i]]

                if i + pos + 2 <= len(nums):
                    best = i + pos + 2
                    if best < mejor:
                        mejor = best

            if x-suma1[i] == 0:
                best = i + 1
                if best < mejor:
                    mejor = best

            if x-suma2[i] == 0:
                best = i + 1
                if best < mejor:
                    mejor = best

        if mejor == float("inf"):
            return -1

        return mejor