// Source: https://leetcode.com/problems/group-anagrams/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
//
// Example:
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
//
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Explanation:
//
//
// 	There is no string in strs that can be rearranged to form "bat".
// 	The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
// 	The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
//
// Constraints:
// 1 <= strs.length <= 104
// 	0 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - bucket-sort (array, linked-list, bucket-sort)
//   • When to use: Use when sorting elements, especially floating-point numbers, that are uniformly distributed over a range. It offers linear time complexity on average for such distributions.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually using another sorting algorithm, and then concatenates the sorted buckets. It achieves an average time complexity of O(N+K), where N is the number of elements and K is the number of buckets.
//   • Invariants: Before sorting any bucket, all elements are correctly placed in their respective buckets based on their range.; After sorting each individual bucket, all elements within that bucket are in sorted order.
//   • Tips: Use a stable sorting algorithm like Insertion Sort for individual buckets to maintain overall stability.; The number of buckets should be chosen carefully, often proportional to N, to optimize performance.
//   • Pitfalls: Performance degrades significantly with non-uniform data distributions, potentially becoming O(N^2).; Requires extra space for the buckets, which can be substantial for many buckets or large elements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} strs
 * @return {string[][]}
 */
var groupAnagrams = function(strs) {
    const map = new Map();
    for (const str of strs) {
        const key = str.split('').sort().join('');
        if (!map.has(key)) {
            map.set(key, []);
        }
        map.get(key).push(str);
    }
    return Array.from(map.values());
};
