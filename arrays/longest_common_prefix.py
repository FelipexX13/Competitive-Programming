class Solution(object):
    def longestCommonPrefix(self, strs):
        
        num = len(strs)
        pr = ""
        for i in range(len(strs[0])):
            l = strs[0][i]
            try:
                cont = 0
                for j in range(num):
                    if(strs[j][i] == l):
                        cont+=1
                if(cont==num):
                    pr+=l
                else:
                    break 
            except:
                break
        return (pr)


        """
        :type strs: List[str]
        :rtype: str
        """
        