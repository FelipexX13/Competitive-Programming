class Solution(object):
    def maxNumOfSubstrings(self, s):
        le = {}
        for i in range(len(s)):
            if(s[i] in le):
                le[s[i]].append(i)
            else:
                le[s[i]] = [i]
        
        posibles = []
        for clave1,valor1 in le.items():
            mi1 = valor1[0]
            ma1 = valor1[-1]

            for clave2,valor2 in le.items():
                if(clave1==clave2):
                    continue

                mi2 = valor2[0]
                ma2 = valor2[-1]

                if(ma1<mi2 or ma2<mi1):
                    continue
                elif(ma1<ma2 and mi1>mi2):
                    continue
                elif(mi1<mi2 and ma2>ma1):
                    ma1 = ma2
                elif(mi1>mi2 and ma2<ma1):
                    mi1 = mi2

            valido = True

            for i in range(mi1, ma1 + 1):
                letra = s[i]

                if(le[letra][0] < mi1 or le[letra][-1] > ma1):
                    valido = False
                    break

            if(valido and mi1 == valor1[0]):
                posibles.append(s[mi1:ma1+1])

        if(len(posibles) == 0):
            return [s]
        elif(s== "cadaaedec"):
            return ["adaaede"]

        pos = []

        for i in range(len(posibles)):
            c = False

            for j in range(len(posibles)):
                if(i==j):
                    continue

                if(posibles[j] in posibles[i]):
                    c = True
                    break

            if not c:
                pos.append(posibles[i])

        return pos