# <3
# Tema: Greedy / Sorting
# Resuelve "Finding Forks" (Kattis): en un cajon con n tipos de tenedores, cada tipo con a_i
# unidades, al menos dos lugares del cajon quedaron vacios porque no se recuerda que tipo va en
# cada lugar tras lavarlos. Pide el minimo numero de tenedores que debieron estar en el
# lavaplatos para causar esa confusion. Ordena las cantidades con l.sort() y suma las dos mas
# pequenas (l[0]+l[1]), pues la ambiguedad minima se logra siempre entre los dos tipos con
# menos tenedores.

n = int(input())
l = list(map(int, input().split()))

l.sort()

print(l[0]+l[1])

