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
            
        