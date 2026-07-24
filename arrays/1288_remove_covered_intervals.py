class Solution:
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:
        n = len(intervals)
        deleted = set()
        for i in range(len(intervals)):
            for j in range(len(intervals)):
                if i != j:
                    if intervals[i][0] <= intervals[j][0] and intervals[i][1] >= intervals[j][1] and (intervals[j][0], intervals[j][1]) not in deleted:
                        n -= 1
                        deleted.add((intervals[j][0], intervals[j][1]))
        return n