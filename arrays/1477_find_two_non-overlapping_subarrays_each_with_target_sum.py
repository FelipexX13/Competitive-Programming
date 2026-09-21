class Solution:
    def minSumOfLengths(self, arr: list[int], target: int) -> int:
        rango = {}
        c = []
        can = 0
        van = 0
        i = 0
        while i < len(arr):
            can += arr[i]
            van += 1
            if(can<=target):
                if(can == target):
                    if(can in rango):
                        rango[can].append([van, i-van+1,i])
                        c.append(van)
                    else:
                        rango[can] = [[van,i-van+1,i]]
                        c.append(van)
            else:
                voy = van
                for j in range(i-voy+1,i+1):
                    can -= arr[j]
                    van -= 1
                    if(can <= target):
                        break
                if(can == target):
                    if(can in rango):
                        rango[can].append([van,i-van+1,i])
                        c.append(van)
                    else:
                        rango[can] = [[van,i-van+1,i]]
                        c.append(van)
            i+=1
        if(len(c)<2):
            return -1
        l = sorted(rango[target], key=lambda x: x[2])

        mini = float("inf")
        mejor = float("inf")
        p = 0

        for actual in l:

            longitud, inicio, fin = actual

            while p < len(l) and l[p][2] < inicio:
                mejor = min(mejor, l[p][0])
                p += 1

            if mejor != float("inf"):
                mini = min(mini, longitud + mejor)
        if(mini==float("inf")):
            return -1
        return mini
                
        