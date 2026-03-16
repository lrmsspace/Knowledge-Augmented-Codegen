// Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and m that consist of the same number of digits.
//
// You can perform the following operations any number of times:
//
//
// 	Choose any digit from n that is not 9 and increase it by 1.
// 	Choose any digit from n that is not 0 and decrease it by 1.
//
//
// The integer n must not be a prime number at any point, including its original value and after each operation.
//
// The cost of a transformation is the sum of all values that n takes throughout the operations performed.
//
// Return the minimum cost to transform n into m. If it is impossible, return -1.
//
// Example:
// Input: n = 10, m = 12
//
// Output: 85
//
// Explanation:
//
// We perform the following operations:
//
//
// 	Increase the first digit, now n = 20.
// 	Increase the second digit, now n = 21.
// 	Increase the second digit, now n = 22.
// 	Decrease the first digit, now n = 12.
//
// Constraints:
// 1 <= n, m < 104
// 	n and m consist of the same number of digits.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(int n, int m) {
        // Precompute primes up to 9999 using Sieve of Eratosthenes
        const int MAX_NUM = 9999;
        bool is_prime[MAX_NUM + 1];
        for (int i = 0; i <= MAX_NUM; ++i) is_prime[i] = true;
        is_prime[0] = is_prime[1] = false;
        for (int p = 2; p * p <= MAX_NUM; ++p) {
            if (is_prime[p]) {
                for (int multiple = p * p; multiple <= MAX_NUM; multiple += p) {
                    is_prime[multiple] = false;
                }
            }
        }

        // Digit DP to find minimum cost
        string str_n = to_string(n);
        string str_m = to_string(m);
        int len = str_n.length();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(2, vector<int>(MAX_NUM + 1, -1)));

        function<int(int, int, int)> dfs = [&](int idx, int tight, int curr_num) -> int {
            if (idx == len) {
                return (curr_num == m) ? 0 : INT_MAX;
            }
            if (dp[idx][tight][curr_num] != -1) {
                return dp[idx][tight][curr_num];
            }

            int limit = tight ? (str_n[idx] - '0') : 9;
            int min_cost = INT_MAX;

            for (int digit = 0; digit <= limit; ++digit) {
                int next_num = curr_num * 10 + digit;
                if (!is_prime[next_num]) {
                    int cost = next_num;
                    int next_tight = tight && (digit == limit);
                    int sub_cost = dfs(idx + 1, next_tight, next_num);
                    if (sub_cost != INT_MAX) {
                        min_cost = min(min_cost, cost + sub_cost);
                    }
                }
            }

            dp[idx][tight][curr_num] = min_cost;
            return min_cost;
        };

        int result = dfs(0, 1, 0);
        return (result == INT_MAX) ? -1 : result;           
    }
};
