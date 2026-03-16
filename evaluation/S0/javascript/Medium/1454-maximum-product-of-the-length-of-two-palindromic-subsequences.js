// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find two disjoint palindromic subsequences of s such that the product of their lengths is maximized. The two subsequences are disjoint if they do not both pick a character at the same index.
//
// Return the maximum possible product of the lengths of the two palindromic subsequences.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: s = "leetcodecom"
// Output: 9
// Explanation: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
// The product of their lengths is: 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 12
// 	s consists of lowercase English letters only.
//

/**
 * @param {string} s
 * @return {number}
 */
var maxProduct = function(s) {
    const n = s.length;
    const palindromicSubsequences = [];

    // Function to check if a string is a palindrome
    const isPalindrome = (str) => {
        let left = 0;
        let right = str.length - 1;
            
        while (left < right) {
            if (str[left] !== str[right]) {
                return false;
            }
            left++; 
            right--;
        }
        return true;
    };

    // Generate all subsequences using bitmasking
    for (let mask = 1; mask < (1 << n); mask++) {
        let subsequence = '';
        for (let i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsequence += s[i];
            }
        }
        if (isPalindrome(subsequence)) {
            palindromicSubsequences.push({ subsequence, mask });
        }
    }

    let maxProduct = 0;
    const len = palindromicSubsequences.length;

    // Check all pairs of palindromic subsequences
    for (let i = 0; i < len; i++) {
        for (let j = i + 1; j < len; j++) {
            const sub1 = palindromicSubsequences[i];
            const sub2 = palindromicSubsequences[j];
            // Check if they are disjoint
            if ((sub1.mask & sub2.mask) === 0) {
                const product = sub1.subsequence.length * sub2.subsequence.length;
                maxProduct = Math.max(maxProduct, product);
            }
        }
    }
    return maxProduct;  
};
