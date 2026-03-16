// Source: https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting only of lowercase English letters.
//
// In one move, you can select any two adjacent characters of s and swap them.
//
// Return the minimum number of moves needed to make s a palindrome.
//
// Note that the input will be generated such that s can always be converted to a palindrome.
//
// Example:
// Input: s = "aabb"
// Output: 2
// Explanation:
// We can obtain two palindromes from s, "abba" and "baab". 
// - We can obtain "abba" from s in 2 moves: "aabb" -> "abab" -> "abba".
// - We can obtain "baab" from s in 2 moves: "aabb" -> "abab" -> "baab".
// Thus, the minimum number of moves needed to make s a palindrome is 2.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists only of lowercase English letters.
// 	s can be converted to a palindrome using a finite number of moves.
//

/**
 * @param {string} s
 * @return {number}
 */
var minMovesToMakePalindrome = function(s) {
    const n = s.length;
    let moves = 0;
    const chars = s.split('');
    for (let left = 0, right = n - 1; left < right; left += 1) {
        let l = left;
        let r = right;
        while (chars[l] !== chars[r]) {
            r -= 1;
        }

        if (l === r) {
            [chars[l], chars[l + 1]] = [chars[l + 1], chars[l]];
            moves += 1;
            left -= 1;
        }
        else {
            for (let i = r; i < right; i += 1) {
                [chars[i], chars[i + 1]] = [chars[i + 1], chars[i]];
                moves += 1;
            }
        }
    }
    return moves;
};
