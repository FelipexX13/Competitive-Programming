class Solution:
    def rotateString(self, s: str, goal: str) -> bool:
        if(len(s)!=len(goal)):
            return False
        
        inicio = goal[0]

        for i in range(len(s)):
            if(s[i] == inicio):
                j = 1
                k = i+1
                f = True
                while j<len(goal):
                    if(k>=len(s)):
                        k=0
                    if(goal[j]!=s[k]):
                        f = False
                        break
                    j+=1
                    k+=1
                if(f):
                    return True
        return False