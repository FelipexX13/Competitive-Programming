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

        return curr.isEndLetter
        

    def startsWith(self, prefix: str) -> bool:
        curr = self.root

        for ch in prefix:
            if ch not in curr.dictionary:
                return False

            curr = curr.dictionary[ch]

        return True
        


# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)