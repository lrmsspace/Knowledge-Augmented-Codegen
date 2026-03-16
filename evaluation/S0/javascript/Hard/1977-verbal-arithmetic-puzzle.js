// Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// Given an equation, represented by words on the left side and the result on the right side.
//
// You need to check if the equation is solvable under the following rules:
//
//
// 	Each character is decoded as one digit (0 - 9).
// 	No two characters can map to the same digit.
// 	Each words[i] and result are decoded as one number without leading zeros.
// 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
//
//
// Return true if the equation is solvable, otherwise return false.
//
// Example:
// Input: words = ["SEND","MORE"], result = "MONEY"
// Output: true
// Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
// Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
//
// Constraints:
// 2 <= words.length <= 5
// 	1 <= words[i].length, result.length <= 7
// 	words[i], result contain only uppercase English letters.
// 	The number of different characters used in the expression is at most 10.
//

/**
 * @param {string[]} words
 * @param {string} result
 * @return {boolean}
 */
var isSolvable = function(words, result) {
    const uniqueChars = new Set();
    for (const word of words) {
        for (const char of word) {
            uniqueChars.add(char);
        }
    }
    for (const char of result) {
        uniqueChars.add(char);
    }   
    if (uniqueChars.size > 10) {
        return false;
    }
    const charArray = Array.from(uniqueChars);
    const charToDigit = {};
    const usedDigits = new Set();
    const backtrack = (index) => {
        if (index === charArray.length) {
            const wordValues = words.map(word => {
                let value = 0;
                for (const char of word) {
                    value = value * 10 + charToDigit[char];
                }
                return value;
            });
            let resultValue = 0;
            for (const char of result) {
                resultValue = resultValue * 10 + charToDigit[char];
            }
            const sum = wordValues.reduce((a, b) => a + b, 0);
            return sum === resultValue;
        }
        const char = charArray[index];
        for (let digit = 0; digit <= 9; digit++) {
            if (!usedDigits.has(digit)) {
                charToDigit[char] = digit;
                usedDigits.add(digit);  
                if (backtrack(index + 1)) {
                    return true;
                }
                usedDigits.delete(digit);
                delete charToDigit[char];
            }
        }
        return false;
    }
    return backtrack(0);    
};
