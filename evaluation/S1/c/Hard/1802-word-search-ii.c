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
// Helpful references (internal KB):
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use when you need to explore all reachable vertices from a starting point or systematically visit all nodes in a graph or tree. It's suitable for problems requiring full exploration of a branch before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically using a stack (explicit or implicit via recursion).
//   • Invariants: Every node `v` in the graph is either visited or not yet visited.; The recursion stack (or explicit stack) always contains a path from the source node to the current node being explored.
//   • Tips: Use a `visited` array or set to prevent cycles and redundant work.; Recursion is often cleaner for implementation, but iterative DFS with an explicit stack avoids recursion depth limits.
//   • Pitfalls: Stack overflow can occur with deep recursion on large graphs.; Forgetting to mark nodes as visited leads to infinite loops in cyclic graphs.
// - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
//   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
//   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
//   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
//   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize) {
    // Trie node structure
    typedef struct TrieNode {
        struct TrieNode* children[26];
        bool isEndOfWord;
    } TrieNode;

    // Create a new trie node
    TrieNode* createTrieNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        return node;
    }

    // Insert a word into the trie
    void insertWord(TrieNode* root, const char* word) {
        TrieNode* curr = root;
        while (*word) {
            int index = *word - 'a';
            if (!curr->children[index]) {
                curr->children[index] = createTrieNode();
            }
            curr = curr->children[index];
            word++;
        }
        curr->isEndOfWord = true;
    }

    // DFS to find words in the board
  
    void dfs(char** board, int boardSize, int* boardColSize, int x, int y, TrieNode* node, char* path, int pathLen, bool** visited, char** result, int* resultSize) {
        if (node->isEndOfWord) {
            path[pathLen] = '\0';
            result[(*resultSize)++] = strdup(path);
            node->isEndOfWord = false; // Avoid duplicates
        }

        if (x < 0 || x >= boardSize || y < 0 || y >= boardColSize[0] || visited[x][y]) {
            return;
        }

        char ch = board[x][y];
        int index = ch - 'a';
        if (!node->children[index]) {
            return;
        }

        visited[x][y] = true;
        path[pathLen] = ch;

        // Explore neighbors
        dfs(board, boardSize, boardColSize, x + 1, y, node->children[index], path, pathLen + 1, visited, result, resultSize);
        dfs(board, boardSize, boardColSize, x - 1, y, node->children[index], path, pathLen + 1, visited, result, resultSize);
        dfs(board, boardSize, boardColSize, x, y + 1, node->children[index], path, pathLen + 1, visited, result, resultSize);
        dfs(board, boardSize, boardColSize, x, y - 1, node->children[index], path, pathLen + 1, visited, result, resultSize);

        visited[x][y] = false;
    }
    // Build the trie
    TrieNode* root = createTrieNode();
    for (int i = 0; i < wordsSize; i++) {
        insertWord(root, words[i]);
    }
    // Prepare for DFS
    bool** visited = (bool**)malloc(boardSize * sizeof(bool*));
    for (int i = 0; i < boardSize; i++) {
        visited[i] = (bool*)calloc(boardColSize[0], sizeof(bool));
    }
    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int resultSizeLocal = 0;
    char* path = (char*)malloc(11 * sizeof(char)); // Max word length is 10
    // Start DFS from each cell
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[0]; j++) {
            dfs(board, boardSize, boardColSize, i, j, root, path, 0, visited, result, &resultSizeLocal);
        }
    }
    // Cleanup
    for (int i = 0; i < boardSize; i++) {
        free(visited[i]);
    }
    free(visited);
    free(path);
    *returnSize = resultSizeLocal;
    return result;
}
