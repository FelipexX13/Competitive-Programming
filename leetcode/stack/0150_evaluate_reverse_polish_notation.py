class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        lit = []
        ope = set(["+","-","*","/"])
        for i in range(len(tokens)):
            if(tokens[i] not in ope):
                lit.append(int(tokens[i]))
            else:
                if(tokens[i]=="+"):
                    v = lit[-2]+lit[-1]
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
                elif(tokens[i]=="-"):
                    v = lit[-2]-lit[-1]
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
                elif(tokens[i]=="*"):
                    v = lit[-2]*lit[-1]
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
                elif(tokens[i]=="/"):
                    v = int(lit[-2]/lit[-1])
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
        return lit[0]