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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        const int MOD = 1e9 + 7;

        // Precompute the transformation matrix
        vector<vector<long long>> mat(26, vector<long long>(26, 0));
        for (int i = 0; i < 26; ++i) {
            for (int j = 1; j <= nums[i]; ++j) {
                mat[i][(i + j) % 26] += 1;
            }
        }

        // Matrix multiplication
        auto matMul = [&](const vector<vector<long long>>& a, const vector<vector<long long>>& b) {
            vector<vector<long long>> res(26, vector<long long>(26, 0));
            for (int i = 0; i < 26; ++i) {
                for (int j = 0; j < 26; ++j) {
                    for (int k = 0; k < 26; ++k) {
                        res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
                    }
                }
            }
            return res;
        };

        // Matrix exponentiation
        auto matPow = [&](vector<vector<long long>> base, long long exp) {
            vector<vector<long long>> res(26, vector<long long>(26, 0));
            for (int i = 0; i < 26; ++i) res[i][i] = 1; // Identity matrix
            while (exp > 0) {
                if (exp % 2 == 1) {
                    res = matMul(res, base);
                }
                base = matMul(base, base);
                exp /= 2;
            }
            return res;
        };

        // Compute the transformation matrix raised to the power of t
        vector<vector<long long>> transMat = matPow(mat, t);
        long long result = 0;
        for (char c : s) {
            int idx = c - 'a';
            for (int j = 0; j < 26; ++j) {
                result = (result + transMat[idx][j]) % MOD;
            }
        }
        return static_cast<int>(result);
    }
};
