// Source: https://leetcode.com/problems/largest-merge-of-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2. You want to construct a string merge in the following way: while either word1 or word2 are non-empty, choose one of the following options:
//
//
// 	If word1 is non-empty, append the first character in word1 to merge and delete it from word1.
//
// 	
// 		For example, if word1 = "abc" and merge = "dv", then after choosing this operation, word1 = "bc" and merge = "dva".
// 	
// 	
// 	If word2 is non-empty, append the first character in word2 to merge and delete it from word2.
// 	
// 		For example, if word2 = "abc" and merge = "", then after choosing this operation, word2 = "bc" and merge = "a".
// 	
// 	
//
//
// Return the lexicographically largest merge you can construct.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b. For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: word1 = "cabaa", word2 = "bcaaa"
// Output: "cbcabaaaaa"
// Explanation: One way to get the lexicographically largest merge is:
// - Take from word1: merge = "c", word1 = "abaa", word2 = "bcaaa"
// - Take from word2: merge = "cb", word1 = "abaa", word2 = "caaa"
// - Take from word2: merge = "cbc", word1 = "abaa", word2 = "aaa"
// - Take from word1: merge = "cbca", word1 = "baa", word2 = "aaa"
// - Take from word1: merge = "cbcab", word1 = "aa", word2 = "aaa"
// - Append the remaining 5 a's from word1 and word2 at the end of merge.
//
// Constraints:
// 1 <= word1.length, word2.length <= 3000
// 	word1 and word2 consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} word1
 * @param {string} word2
 * @return {string}
 */
var largestMerge = function(word1, word2) {
    let i = 0, j = 0;
    const merge = [];
    while (i < word1.length && j < word2.length) {
        if (word1.substring(i) > word2.substring(j)) {
            merge.push(word1[i]);
            i++;
        } else {
            merge.push(word2[j]);
            j++;
        }
    }
    while (i < word1.length) {
        merge.push(word1[i]);
        i++;
    }
    while (j < word2.length) {
        merge.push(word2[j]);
        j++;
    }
    return merge.join('');
};
