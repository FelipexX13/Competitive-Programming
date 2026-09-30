class Solution:
    def smallestPalindrome(self, s: str) -> str:
        t = [
            "a","b","c","d","e","f","g",
            "h","i","j","k","l","m","n",
            "o","p","q","r","s","t","u",
            "v","w","x","y","z"
        ]
        dic = {}
        for i in s:
            if(i not in dic):
                dic[i] = 1
            else:
                dic[i]+=1

        ini = ""
        for i in t:
            if(i in dic and dic[i] > 1):
                cant = dic[i]//2
                dic[i] -= cant*2
                agre = i*cant
                ini+=agre
        
        mitad = ""
        for i in t:
            if(i in dic and dic[i] == 1):
                mitad = i
        
        fin = ini[::-1]
        resp = ini + mitad + fin
        return resp