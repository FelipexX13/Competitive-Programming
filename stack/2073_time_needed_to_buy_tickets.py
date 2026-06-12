class Solution:
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        c = 0
        while tickets[k] != 0:
            j = tickets[0]
            if(j>0):
                c+=1
            tickets.pop(0)
            tickets.append(j-1)
            k -= 1
            if(k < 0):
                k = len(tickets)-1            
        return c