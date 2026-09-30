class Solution:
    def beautifulArray(self, n: int) -> list[int]:

        if n == 1:
            return [1]

        arr = self.beautifulArray((n + 1) // 2)

        impares = []
        pares = []

        for x in arr:
            if 2 * x - 1 <= n:
                impares.append(2 * x - 1)

            if 2 * x <= n:
                pares.append(2 * x)

        return impares + pares