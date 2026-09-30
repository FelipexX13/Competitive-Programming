class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        c = 0
        for i in s:
            if(i != "-"):
                c+=1
        cant = c%k
        fin = ""
        if(cant!= 0):
            c = 0
            voy = 0
            for i in range(len(s)):
                if(s[i] != "-"):
                    try:
                        fin += s[i].upper()
                    except:
                        fin += s[i]
                    c+=1
                voy = i
                if(c==cant):
                    fin+="-"
                    break
        else:
            c = 0
            voy = 0
            for i in range(len(s)):
                if(s[i] != "-"):
                    try:
                        fin += s[i].upper()
                    except:
                        fin += s[i]
                    c+=1
                voy = i
                if(c==k):
                    fin+="-"
                    break
        c = 0
        for i in range(voy+1, len(s)):
            if(s[i] != "-"):
                try:
                    fin += s[i].upper()
                except:
                    fin += s[i]
                c+=1
            if(c==k):
                fin += "-"
                c = 0
        try:
            if(fin[-1]== "-"):
                return fin[0:-1]
            else:
                return fin
        except:
            return fin