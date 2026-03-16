// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s and are tasked with finding two non-intersecting palindromic substrings of odd length such that the product of their lengths is maximized.
//
// More formally, you want to choose four integers i, j, k, l such that 0 <= i <= j < k <= l < s.length and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths. s[i...j] denotes a substring from index i to index j inclusive.
//
// Return the maximum possible product of the lengths of the two non-intersecting palindromic substrings.
//
// A palindrome is a string that is the same forward and backward. A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "ababbb"
// Output: 9
// Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 105
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var maxProduct = function(s) {
    const n = s.length;
    const left = new Array(n).fill(0);
    const right = new Array(n).fill(0);
    for (let center = 0; center < n; center++) {
        let leftPtr = center, rightPtr = center;
        while (leftPtr >= 0 && rightPtr < n && s[leftPtr] === s[rightPtr]) {
            left[center] = Math.max(left[center], rightPtr - leftPtr + 1);
            leftPtr--;
            rightPtr++;
        }
        leftPtr = center - 1;
        rightPtr = center + 1;
        while (leftPtr >= 0 && rightPtr < n && s[leftPtr] === s[rightPtr]) {
            left[center] = Math.max(left[center], rightPtr - leftPtr + 1);
            leftPtr--;
            rightPtr++;
        }
    }
    for (let center = n - 1; center >= 0; center--) {
        let leftPtr = center, rightPtr = center;
        while (leftPtr >= 0 && rightPtr < n && s[leftPtr] === s[rightPtr]) {
            right[center] = Math.max(right[center], rightPtr - leftPtr + 1);
            leftPtr--;
            rightPtr++;
        }
        leftPtr = center - 1;
        rightPtr = center + 1;
        while (leftPtr >= 0 && rightPtr < n && s[leftPtr] === s[rightPtr]) {
            right[center] = Math.max(right[center], rightPtr - leftPtr + 1);
            leftPtr--;
            rightPtr++;
        }
    }
    let maxProduct = 0;
    for (let i = 0; i < n - 1; i++) {
        maxProduct = Math.max(maxProduct, left[i] * right[i + 1]);
    }
    return maxProduct;  
};
