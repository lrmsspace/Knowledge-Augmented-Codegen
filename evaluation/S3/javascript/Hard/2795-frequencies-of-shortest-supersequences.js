// Source: https://leetcode.com/problems/frequencies-of-shortest-supersequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words. Find all shortest common supersequences (SCS) of words that are not permutations of each other.
//
// A shortest common supersequence is a string of minimum length that contains each string in words as a subsequence.
//
// Return a 2D array of integers freqs that represent all the SCSs. Each freqs[i] is an array of size 26, representing the frequency of each letter in the lowercase English alphabet for a single SCS. You may return the frequency arrays in any order.
//
// Example:
// Input: words = ["ab","ba"]
//
// Output: [[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
//
// Explanation:
//
// The two SCSs are "aba" and "bab". The output is the letter frequencies for each one.
//
// Constraints:
// 1 <= words.length <= 256
// 	words[i].length == 2
// 	All strings in words will altogether be composed of no more than 16 unique lowercase letters.
// 	All strings in words are unique.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} words
 * @return {number[][]}
 */
var supersequences = function(words) {
    const uniqueChars = new Set();
    for (const word of words) {
        for (const char of word) {
            uniqueChars.add(char);
        }
    }
    const charArray = Array.from(uniqueChars);
    const charIndex = {};
    charArray.forEach((char, index) => {
        charIndex[char] = index;
    });

    const n = words.length;
    const m = charArray.length;
    const freqMap = new Array(n).fill(0).map(() => new Array(m).fill(0));
    
    for (let i = 0; i < n; i++) {
        for (const char of words[i]) {
            freqMap[i][charIndex[char]]++;
        }
    }

    const maxFreq = new Array(m).fill(0);
    for (let j = 0; j < m; j++) {
        let maxCount = 0;
        for (let i = 0; i < n; i++) {
            maxCount = Math.max(maxCount, freqMap[i][j]);
        }
        maxFreq[j] = maxCount;
    }

    const resultFreqs = [];
    function backtrack(index, currentFreq) {
        if (index === m) {
            resultFreqs.push([...currentFreq]);
            return;
        }
        for (let count = 0; count <= maxFreq[index]; count++) {
            currentFreq[index] = count;
            backtrack(index + 1, currentFreq);
        }
    }

    backtrack(0, new Array(m).fill(0));
    
    return resultFreqs;
};
