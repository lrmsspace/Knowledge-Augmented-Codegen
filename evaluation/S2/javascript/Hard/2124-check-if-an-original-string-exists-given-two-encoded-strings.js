// Source: https://leetcode.com/problems/check-if-an-original-string-exists-given-two-encoded-strings/   |   Difficulty: Hard
//
// Problem Description:
// An original string, consisting of lowercase English letters, can be encoded by the following steps:
//
//
// 	Arbitrarily split it into a sequence of some number of non-empty substrings.
// 	Arbitrarily choose some elements (possibly none) of the sequence, and replace each with its length (as a numeric string).
// 	Concatenate the sequence as the encoded string.
//
//
// For example, one way to encode an original string "abcdefghijklmnop" might be:
//
//
// 	Split it as a sequence: ["ab", "cdefghijklmn", "o", "p"].
// 	Choose the second and third elements to be replaced by their lengths, respectively. The sequence becomes ["ab", "12", "1", "p"].
// 	Concatenate the elements of the sequence to get the encoded string: "ab121p".
//
//
// Given two encoded strings s1 and s2, consisting of lowercase English letters and digits 1-9 (inclusive), return true if there exists an original string that could be encoded as both s1 and s2. Otherwise, return false.
//
// Note: The test cases are generated such that the number of consecutive digits in s1 and s2 does not exceed 3.
//
// Example:
// Input: s1 = "internationalization", s2 = "i18n"
// Output: true
// Explanation: It is possible that "internationalization" was the original string.
// - "internationalization" 
//   -> Split:       ["internationalization"]
//   -> Do not replace any element
//   -> Concatenate:  "internationalization", which is s1.
// - "internationalization"
//   -> Split:       ["i", "nternationalizatio", "n"]
//   -> Replace:     ["i", "18",                 "n"]
//   -> Concatenate:  "i18n", which is s2
//
// Constraints:
// 1 <= s1.length, s2.length <= 40
// 	s1 and s2 consist of digits 1-9 (inclusive), and lowercase English letters only.
// 	The number of consecutive digits in s1 and s2 does not exceed 3.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var possiblyEquals = function(s1, s2) {
    const memo = new Map();
    
    function helper(i, j, diff) {
        const key = `${i},${j},${diff}`;
        if (memo.has(key)) return memo.get(key);
        if (i === s1.length && j === s2.length) return diff === 0;
        if (i > s1.length || j > s2.length) return false;
        if (s1[i] === s2[j]) {
            const result = helper(i + 1, j + 1, diff);
            memo.set(key, result);
            return result;
        }
        if (s1[i] >= '0' && s1[i] <= '9') {
            let num = 0;
            let k = i;
            while (k < s1.length && s1[k] >= '0' && s1[k] <= '9') {
                num = num * 10 + parseInt(s1[k]);
                k++;
                const result = helper(k, j, diff - num);
                memo.set(key, result);
                if (result) return true;
            }
        }
        if (s2[j] >= '0' && s2[j] <= '9') {
            let num = 0;
            let k = j;
            while (k < s2.length && s2[k] >= '0' && s2[k] <= '9') {
                num = num * 10 + parseInt(s2[k]);
                k++;
                const result = helper(i, k, diff + num);
                memo.set(key, result);
                if (result) return true;
            }
        }
        memo.set(key, false);
        return false;
    }
    return helper(0, 0, 0);
};