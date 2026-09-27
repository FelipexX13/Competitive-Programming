class Solution:
    def reverseParentheses(self, s: str) -> str:
        stack = []
        i = 0
        while i< len(s):
            if(s[i]=="("):
                stack.append(i)
            elif(s[i]==")"):
                pal = s[stack[-1]+1:i]
                pal = pal[::-1]
                ini = s[:stack[-1]]
                fin = s[i+1:]
                s = ini+pal+fin
                stack.pop()
                i-=2
            i+=1
        return s
                
                
