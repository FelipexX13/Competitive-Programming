# <3
# Tema: Math / Algebra
# Resuelve "The Wisdom of Master Wei": el maestro Wei empezo a programar en el ano W y
# el discipulo Kai en el ano K (W < K); hay que hallar el ano exacto Y en el que la
# experiencia del maestro (Y-W anos) sea el doble de la de Kai (Y-K anos). Despeja la
# ecuacion Y-W = 2*(Y-K), que da Y = 2K - W, y la imprime directamente como
# m + (m - n) usando n=W y m=K, sin necesidad de busqueda ni iteracion.

n,m = list(map(int,input().split()))
print(m+(m-n))


