class Solution:
    def findRightInterval(self, intervals: list[list[int]]) -> list[int]:
        ic = {}

        for i in range(len(intervals)):
            if intervals[i][0] in ic:
                ic[intervals[i][0]].append(i)
            else:
                ic[intervals[i][0]] = [i]

        res = []

        for i in intervals:
            fin = i[1]

            mejor = float("inf")
            indice = -1

            for inicio in ic:
                if inicio >= fin and inicio < mejor:
                    mejor = inicio
                    indice = ic[inicio][0]

            res.append(indice)

        return res