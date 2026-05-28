class Solution:
    def isValid(self, s: str) -> bool:
        cola = []

        for i in range(len(s)):
            try:
                if(s[i]== "("):
                    cola.append(1)
                elif(s[i]== "["):
                    cola.append(2)
                elif(s[i]== "{"):
                    cola.append(3)
                elif(s[i]== ")" and cola[len(cola)-1]==1):
                    cola.pop(len(cola)-1)
                elif(s[i]== "]"and cola[len(cola)-1]==2):
                    cola.pop(len(cola)-1)
                elif(s[i]== "}"and cola[len(cola)-1]==3):
                    cola.pop(len(cola)-1)
                elif(s[i]== ")"):
                    break
                elif(s[i]== "]"):
                    break
                elif(s[i]== "}"):
                    break
            except:
                return False
        if(len(cola)==0):
            return True
        else:
            return False
        