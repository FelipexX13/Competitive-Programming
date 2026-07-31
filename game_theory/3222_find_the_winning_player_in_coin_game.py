class Solution:
    def winningPlayer(self, x: int, y: int) -> str:
        j = True
        while True:
            if(x>=1 and y>=4):
                x-=1
                y-=4
                j = not j
            else:
                break
        if(j):
            return "Bob"
        else:
            return "Alice"
        