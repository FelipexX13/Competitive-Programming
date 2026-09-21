class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        a= sorted(intervals)
        final = []
        ini = a[0][0]
        fin = a[0][1]
        for i in a:
            if(ini == i[0] and fin == i[1]):
                continue
            else:
                if(i[0]>= ini and i[0]<= fin):
                    if(i[1]>fin):
                        fin = i[1]
                else:
                    final.append([ini,fin])
                    ini = i[0]
                    fin = i[1]
        final.append([ini,fin])
        return final