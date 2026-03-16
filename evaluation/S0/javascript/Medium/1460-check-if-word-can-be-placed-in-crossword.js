// Source: https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix board, representing the current state of a crossword puzzle. The crossword contains lowercase English letters (from solved words), ' ' to represent any empty cells, and '#' to represent any blocked cells.
//
// A word can be placed horizontally (left to right or right to left) or vertically (top to bottom or bottom to top) in the board if:
//
//
// 	It does not occupy a cell containing the character '#'.
// 	The cell each letter is placed in must either be ' ' (empty) or match the letter already on the board.
// 	There must not be any empty cells ' ' or other lowercase letters directly left or right of the word if the word was placed horizontally.
// 	There must not be any empty cells ' ' or other lowercase letters directly above or below the word if the word was placed vertically.
//
//
// Given a string word, return true if word can be placed in board, or false otherwise.
//
// Example:
// Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]], word = "abc"
// Output: true
// Explanation: The word "abc" can be placed as shown above (top to bottom).
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m * n <= 2 * 105
// 	board[i][j] will be ' ', '#', or a lowercase English letter.
// 	1 <= word.length <= max(m, n)
// 	word will contain only lowercase English letters.
//

/**
 * @param {character[][]} board
 * @param {string} word
 * @return {boolean}
 */
var placeWordInCrossword = function(board, word) {
    const reversedWord = word.split('').reverse().join('');
    const rows = board.length;
    const cols = board[0].length;
    const canPlace = (line, word) => {
        let i = 0;  
        while (i <= line.length - word.length) {
            if ((i === 0 || line[i - 1] === '#') &&
                (i + word.length === line.length || line[i + word.length] === '#')) {
                let canFit = true;
                for (let j = 0; j < word.length; j++) { 
                    if (line[i + j] !== ' ' && line[i + j] !== word[j]) {
                        canFit = false;
                        break;
                    }
                }
                if (canFit) return true;
            }
            i++;
        }       
        
        return false;    }  

    for (let r = 0; r < rows; r++) {
        if (canPlace(board[r], word) || canPlace(board[r], reversedWord)) {
            return true;
        }
    }

    for (let c = 0; c < cols; c++) {
        const column = [];
        for (let r = 0; r < rows; r++) {
            column.push(board[r][c]);
        }
        if (canPlace(column, word) || canPlace(column, reversedWord)) {
            return true;
        }
    }
    return false;   
};
