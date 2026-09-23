import heapq

class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        heap = []
        d = 0
        c = 0
        while True:
            if(d<len(days)):
                heapq.heappush(heap, (days[d]+d, apples[d]))
            if (not heap):
                break
            try:
                menor,quedan = heapq.heappop(heap)
                while menor<=d or quedan < 1:  
                    menor,quedan = heapq.heappop(heap)
                quedan -= 1    
                c+= 1              
                heapq.heappush(heap, (menor,quedan)) 
            except: 
                d+=1
                continue 
            d+=1
        return c