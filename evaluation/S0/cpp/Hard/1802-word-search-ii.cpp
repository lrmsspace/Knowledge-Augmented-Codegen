// Source: https://leetcode.com/problems/word-search-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n board of characters and a list of strings words, return all words on the board.
//
// Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
//
// Example:
// Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
// Output: ["eat","oath"]
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 12
// 	board[i][j] is a lowercase English letter.
// 	1 <= words.length <= 3 * 104
// 	1 <= words[i].length <= 10
// 	words[i] consists of lowercase English letters.
// 	All the strings of words are unique.
//

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        struct TrieNode {
            unordered_map<char, TrieNode*> children;
            string word = "";
        };
        
        TrieNode* buildTrie(const vector<string>& words) {
            TrieNode* root = new TrieNode();
            for (const string& word : words) {
                TrieNode* node = root;
                for (char c : word) {
                    if (!node->children.count(c)) {
                        node->children[c] = new TrieNode();
                    }
                    node = node->children[c];
                }
                node->word = word;
            }
            return root;
        }
        
        void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, vector<string>& result) {
            char c = board[i][j];
            if (!node->children.count(c)) return;
            node = node->children[c];
            if (!node->word.empty()) {
                result.push_back(node->word);
                node->word = "";  // Avoid duplicates
            }
            
            board[i][j] = '#';  // Mark as visited
            vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            for (const auto& dir : directions) {
                int ni = i + dir.first, nj = j + dir.second;
                if (ni >= 0 && ni < board.size() && nj >= 0 && nj < board[0].size() && board[ni][nj] != '#') {
                    dfs(board, ni, nj, node, result);
                }
            }
            board[i][j] = c;  // Restore
        }
        
        TrieNode* root = buildTrie(words);
        vector<string> result;
        
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, i, j, root, result);
            }
        }
        
        return result;          
    }
};
