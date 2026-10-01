# <3
# Tema: LeetCode Hub / Trie hacia Adelante y al Reves
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2 * largo), compara todos los pares
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3042 "Count Prefix and Suffix Pairs I": contar pares donde una palabra es a la vez
# prefijo y sufijo de la otra. Tecnica: dos tries por palabra, uno con la palabra derecha y otro
# con la palabra invertida. Ser sufijo es ser prefijo del reverso, y ese es el unico truco.
# Igual compara todos los pares, asi que es O(n^2 * largo). OJO: deja un print(j, i) de
# depuracion adentro del ciclo.

class Node:
    def __init__(self):
        self.dictionary = {}
        self.isEndLetter = False


class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        curr = self.root

        for ch in word:
            if ch not in curr.dictionary:
                curr.dictionary[ch] = Node()

            curr = curr.dictionary[ch]

        curr.isEndLetter = True

    def search(self, word):
        curr = self.root

        for ch in word:
            if ch not in curr.dictionary:
                return False

            curr = curr.dictionary[ch]

        return True

class Solution:
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        derecho = []
        reves = []

        for i in words:
            trieD = Trie()
            trieR = Trie()
            a = reversed(i)
            trieD.insert(i)
            trieR.insert(a)
            derecho.append(trieD)
            reves.append(trieR)

        cont = 0
        for i in range (len(derecho)):
            for j in range(len(words)):
                if(i <= j):
                    continue
                a = reversed(words[j])
                if(derecho[i].search(words[j]) and reves[i].search(a)):
                    print(j,i)
                    cont+=1
        return cont
            
        