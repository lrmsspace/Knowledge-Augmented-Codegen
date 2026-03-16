// Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of lowercase English letters, an integer t representing the number of transformations to perform, and an array nums of size 26. In one transformation, every character in s is replaced according to the following rules:
//
//
// 	Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in the alphabet. For example, if s[i] = 'a' and nums[0] = 3, the character 'a' transforms into the next 3 consecutive characters ahead of it, which results in "bcd".
// 	The transformation wraps around the alphabet if it exceeds 'z'. For example, if s[i] = 'y' and nums[24] = 3, the character 'y' transforms into the next 3 consecutive characters ahead of it, which results in "zab".
//
//
// Return the length of the resulting string after exactly t transformations.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
//
// Output: 7
//
// Explanation:
//
//
// 	
// 	First Transformation (t = 1):
//
// 	
// 		'a' becomes 'b' as nums[0] == 1
// 		'b' becomes 'c' as nums[1] == 1
// 		'c' becomes 'd' as nums[2] == 1
// 		'y' becomes 'z' as nums[24] == 1
// 		'y' becomes 'z' as nums[24] == 1
// 		String after the first transformation: "bcdzz"
// 	
// 	
// 	
// 	Second Transformation (t = 2):
//
// 	
// 		'b' becomes 'c' as nums[1] == 1
// 		'c' becomes 'd' as nums[2] == 1
// 		'd' becomes 'e' as nums[3] == 1
// 		'z' becomes 'ab' as nums[25] == 2
// 		'z' becomes 'ab' as nums[25] == 2
// 		String after the second transformation: "cdeabab"
// 	
// 	
// 	
// 	Final Length of the string: The string is "cdeabab", which has 7 characters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
// 	1 <= t <= 109
// 	nums.length == 26
// 	1 <= nums[i] <= 25
//
// Helpful references (internal KB):
// - Fibonacci Numbers (matrix, matrix-exp)
//   • When to use: Use when needing to compute the N-th Fibonacci number or similar linear recurrence relations for very large N efficiently, typically in logarithmic time.
//   • Idea: This method computes the N-th Fibonacci number by transforming the linear recurrence into a matrix multiplication, then using binary exponentiation (matrix exponentiation) to raise the transformation matrix to the N-th power. It achieves O(log N) time complexity.
//   • Invariants: The base matrix M = [[1, 1], [1, 0]] correctly transforms (F_k, F_{k-1}) to (F_{k+1}, F_k).; After k matrix multiplications, the accumulated matrix represents M^k.
//   • Tips: Understand binary exponentiation for matrices to efficiently compute powers.; The base transformation matrix for Fibonacci is typically [[1, 1], [1, 0]].
//   • Pitfalls: Incorrectly setting up the base matrix or initial vector.; Forgetting to apply modulo operations, leading to integer overflow for large numbers.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Discrete Logarithm (array, number, binary-search, mod-exp)
//   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
//   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
//   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
//   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
//   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number} t
 * @param {number[]} nums
 * @return {number}
 */
var lengthAfterTransformations = function(s, t, nums) {
    const mod = 1e9 + 7;
    const count = Array(26).fill(0);
    
    for (const char of s) {
        count[char.charCodeAt(0) - 97]++;
    }
    
    const fibCache = new Map();
    
    const fib = (n) => {
        if (n === 0) return 1;
        if (n === 1) return 1;
        if (fibCache.has(n)) {
            return fibCache.get(n);
        }
        const a = fib(Math.floor(n / 2));
        const b = fib(Math.ceil(n / 2));
        const result = (a * b + a * a) % mod;
        fibCache.set(n, result);
        return result;
    };
    
    let result = 0;
    for (let i = 0; i < 26; i++) {
        if (count[i] > 0) {
            result = (result + count[i] * fib(nums[i] * t)) % mod;
        }
    }
    
    return result;
};
