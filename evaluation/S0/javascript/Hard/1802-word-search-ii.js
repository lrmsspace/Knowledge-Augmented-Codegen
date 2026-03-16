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

/**
 * @param {character[][]} board
 * @param {string[]} words
 * @return {string[]}
 */
var findWords = function(board, words) {
    


    let m = board.length;
    let n = board[0].length;
    let trie = {};
    for (let word of words) {
        let node = trie;
        for (let char of word) {
            if (!node[char]) {
                node[char] = {};
            }
            node = node[char];
        }
        node.isWord = true;
    }

    let result = new Set();
    let directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];

    function dfs(x, y, node, path) {
        if (node.isWord) {
            result.add(path);
            node.isWord = false; // Avoid duplicates
        }
        if (x < 0 || x >= m || y < 0 || y >= n || !node[board[x][y]]) {
            return;
        }
        let char = board[x][y];
        board[x][y] = '#';
        for (let [dx, dy] of directions) {
            dfs(x + dx, y + dy, node[char], path + char);
        }
        board[x][y] = char;
    }
    
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            dfs(i, j, trie, "");
        }
    }

    return Array.from(result);
};
