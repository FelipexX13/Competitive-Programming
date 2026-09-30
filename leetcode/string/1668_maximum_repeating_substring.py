class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        ca = []
        i = 0
        while i<len(sequence):
            try:
                j = 1
                c=0
                while True:
                    k = word*j
                    val = hash(k)        
                    s = hash(sequence[i:i+len(k)])
                    if(s == val):
                        c+=1
                    else:
                        break
                    j+=1
                ca.append(c)
            except:
                break
            i+=1
        return max(ca)
        