class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        fi = []
        i = 0
        while i < len(prices)-1:
            j = i+1
            a = len(fi)
            while j<len(prices):
                if(prices[j]<=prices[i]):
                    fi.append(prices[i]-prices[j])
                    break
                j+=1
            if(a == len(fi)):
                fi.append(prices[i])
            i+=1

        fi.append(prices[i])
        return fi