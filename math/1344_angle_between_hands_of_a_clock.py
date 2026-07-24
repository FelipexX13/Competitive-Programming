class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        dic = {3: 90, 2:60, 1:30, 12: 0, 11: 330, 10: 300, 9: 270, 8: 240, 7: 210, 6: 180, 5: 150, 4: 120}
        prop = minutes/60
        aguja_pe = dic[hour]

        prop2 = int(minutes/5)
        if(prop2 == 0):
            prop2 = 12
        dif = minutes - prop2*5
        dic2 = {}
        i = 0
        can = 0
        while can < 12:
            dic2[hour+i] = 30*can
            if(hour+i == 12):
                hour = 0
                i = 0
            i += 1
            can += 1
        aguja_gr = abs(dic2[prop2] + (dif*6) - prop*30)
        if(360-aguja_gr < aguja_gr):
            return 360-aguja_gr
        else:
            return aguja_gr
        