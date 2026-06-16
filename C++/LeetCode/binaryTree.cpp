// <3
// Tema: Data Structures / Tree Construction
// Resuelve "Create Binary Tree From Descriptions": dado un arreglo de tripletas
// [parent, child, isLeft], construye el arbol enlazando cada hijo a su padre y devuelve la raiz
// (el unico nodo que nunca aparece como hijo).

#include <bits/stdc++.h>;

using namespace std;

class Solution {
public:
    struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;

        for (auto &d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if (!nodes.count(parent))
                nodes[parent] = new TreeNode(parent);

            if (!nodes.count(child))
                nodes[child] = new TreeNode(child);

            if (isLeft)
                nodes[parent]->left = nodes[child];
            else
                nodes[parent]->right = nodes[child];

            children.insert(child);
        }

        for (auto &d : descriptions) {
            int parent = d[0];
            if (!children.count(parent))
                return nodes[parent];
        }

        return nullptr;
    }
};