n = list(map(int, input().split()))
if len(n) != 1:
    n, k = n
    while(n != 0):
        if n == 1:
            print("-")
            n = list(map(int, input().split()))
            if len(n) == 1:
                break
            else:
                n, k = n
        w = [0]*(n+1)
        l = [0]*(n+1)
        
        for i in range((k*n*(n-1))//2):
            num1, res1, num2, res2 = input().split()
            num1, num2 = int(num1), int(num2)
            if res1 == res2:
                continue
            if res1 == "rock" and res2 == "paper":
                w[num2] += 1
                l[num1] += 1
            elif res1 == "rock" and res2 == "scissors":
                w[num1] += 1
                l[num2] += 1
            elif res1 == "paper" and res2 == "rock":
                w[num1] += 1
                l[num2] += 1
            elif res1 == "paper" and res2 == "scissors":
                w[num2] += 1
                l[num1] += 1
            elif res1 == "scissors" and res2 == "rock":
                w[num2] += 1
                l[num1] += 1
            elif res1 == "scissors" and res2 == "paper":
                w[num1] += 1
                l[num2] += 1
                
        for i in range(1, n+1):
            wins = w[i]
            loses = l[i]
            
            if wins+loses == 0:
                print("-")
            else:
                print(f"{(wins/(wins+loses)):.3f}")
        print("")
        n = list(map(int, input().split()))
        if len(n) == 1:
            break
        else:
            n, k = n
