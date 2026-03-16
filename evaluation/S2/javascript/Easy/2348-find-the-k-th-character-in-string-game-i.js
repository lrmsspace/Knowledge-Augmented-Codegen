// Source: https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are playing a game. Initially, Alice has a string word = "a".
//
// You are given a positive integer k.
//
// Now Bob will ask Alice to perform the following operation forever:
//
//
// 	Generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word.
//
//
// For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
//
// Return the value of the kth character in word, after enough operations have been done for word to have at least k characters.
//
// Example:
// Input: k = 5
//
// Output: "b"
//
// Explanation:
//
// Initially, word = "a". We need to do the operation three times:
//
//
// 	Generated string is "b", word becomes "ab".
// 	Generated string is "bc", word becomes "abbc".
// 	Generated string is "bccd", word becomes "abbcbccd".
//
// Constraints:
// 1 <= k <= 500
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} k
 * @return {character}
 */
var kthCharacter = function(k) {
    let word = "a";
    
    while (word.length < k) {
        let newWord = "";
        for (const char of word) {
            const nextChar = String.fromCharCode((char.charCodeAt(0) - 'a'.charCodeAt(0) + 1) % 26 + 'a'.charCodeAt(0));
            newWord += nextChar;
        }
        word += newWord;
    }
    return word[k - 1];
};
