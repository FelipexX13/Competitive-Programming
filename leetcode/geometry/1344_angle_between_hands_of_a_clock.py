class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        minAng = (360/60)*minutes
        hourAng = ((360/12)*((hour+minutes/60)%24))%360

        return min(abs(minAng-hourAng),abs(hourAng-minAng), 360-abs(minAng-hourAng), 360-abs(hourAng-minAng))
