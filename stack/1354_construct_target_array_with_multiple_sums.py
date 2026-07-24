import heapq
class Solution:
    def isPossible(self, target: List[int]) -> bool:
        tam = []
        for i in target:
            heapq.heappush(tam, i*-1)  

        if(len(target) == 1 and 1 in target):
            return True
        elif(len(target) == 1 and 1 not in target):
            return False

        cantidad = 0
        suma = sum(tam)
        ant = tam.copy()
        while cantidad != len(target): 
            mayor = heapq.heappop(tam) 
            suma -= mayor
            if(mayor == suma):
                break
            me = (-mayor) % (-suma)
            if(me == 0):
                me = -suma
            elif(me < 0):
                break
            heapq.heappush(tam, me*-1)
            cantidad = tam.count(-1)
            print(mayor, suma, me, tam, ant)
            suma -= me
            if(tam == ant):
                break
            ant = tam.copy()

        if(cantidad != len(target)):
            return  False
        else:
            return True

