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
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int lengthAfterTransformations(char* s, int t, int* nums, int numsSize) {
    long long mod = 1000000007;
    long long dp[26];
    for (int i = 0; i < 26; i++) {
        dp[i] = nums[i];
    }
    
    for (int step = 1; step < t; step++) {
        long long new_dp[26];
        for (int i = 0; i < 26; i++) {
            new_dp[i] = 0;
            for (int j = 0; j < nums[i]; j++) {
                int next_char = (i + j + 1) % 26;
                new_dp[i] = (new_dp[i] + dp[next_char]) % mod;
            }
        }
        for (int i = 0; i < 26; i++) {
            dp[i] = new_dp[i];
        }
    }
    
    long long result = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int char_index = s[i] - 'a';
        result = (result + dp[char_index]) % mod;
    }
    
    return (int)result;     
}
