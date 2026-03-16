# Source: https://leetcode.com/problems/word-search-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given an m x n board of characters and a list of strings words, return all words on the board.
#
# Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
#
# Example:
# Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
# Output: ["eat","oath"]
#
# Constraints:
# m == board.length
# 	n == board[i].length
# 	1 <= m, n <= 12
# 	board[i][j] is a lowercase English letter.
# 	1 <= words.length <= 3 * 104
# 	1 <= words[i].length <= 10
# 	words[i] consists of lowercase English letters.
# 	All the strings of words are unique.
#

class Solution(object):
    def findWords(self, board, words):
        """
        :type board: List[List[str]]
        :type words: List[str]
        :rtype: List[str]
        """
        ROWS, COLS = len(board), len(board[0])
        trie = {}
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = word  # End of word marker

        result = set()
        
        def backtrack(r, c, parent):
            letter = board[r][c]
            curr_node = parent[letter]
            
            if '$' in curr_node:
                result.add(curr_node['$'])
            
            board[r][c] = '#'  # Mark as visited
            
            for (dr, dc) in [(0,1), (1,0), (0,-1), (-1,0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < ROWS and 0 <= nc < COLS and board[nr][nc] in curr_node:
                    backtrack(nr, nc, curr_node)
            
            board[r][c] = letter  # Restore original letter
            
            if not curr_node:
                parent.pop(letter)
        
        for r in range(ROWS):
            for c in range(COLS):
                if board[r][c] in trie:
                    backtrack(r, c, trie)
        
        return list(result)