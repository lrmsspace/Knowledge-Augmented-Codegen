// Source: https://leetcode.com/problems/most-frequent-prime/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n 0-indexed 2D matrix mat. From every cell, you can create numbers in the following way:
//
//
// 	There could be at most 8 paths from the cells namely: east, south-east, south, south-west, west, north-west, north, and north-east.
// 	Select a path from them and append digits in this path to the number being formed by traveling in this direction.
// 	Note that numbers are generated at every step, for example, if the digits along the path are 1, 9, 1, then there will be three numbers generated along the way: 1, 19, 191.
//
//
// Return the most frequent prime number greater than 10 out of all the numbers created by traversing the matrix or -1 if no such prime number exists. If there are multiple prime numbers with the highest frequency, then return the largest among them.
//
// Note: It is invalid to change the direction during the move.
//
// Example:
// Input: mat = [[1,1],[9,9],[1,1]]
// Output: 19
// Explanation: 
// From cell (0,0) there are 3 possible directions and the numbers greater than 10 which can be created in those directions are:
// East: [11], South-East: [19], South: [19,191].
// Numbers greater than 10 created from the cell (0,1) in all possible directions are: [19,191,19,11].
// Numbers greater than 10 created from the cell (1,0) in all possible directions are: [99,91,91,91,91].
// Numbers greater than 10 created from the cell (1,1) in all possible directions are: [91,91,99,91,91].
// Numbers greater than 10 created from the cell (2,0) in all possible directions are: [11,19,191,19].
// Numbers greater than 10 created from the cell (2,1) in all possible directions are: [11,19,19,191].
// The most frequent prime number among all the created numbers is 19.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 6
// 	1 <= mat[i][j] <= 9
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int mostFrequentPrime(int** mat, int matSize, int* matColSize) {
    // Precompute primes up to 10^6 using Sieve of Eratosthenes
    #define MAX_NUM 1000000
    int is_prime[MAX_NUM + 1];
    for (int i = 0; i <= MAX_NUM; i++) is_prime[i] = 1;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= MAX_NUM; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_NUM; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    // Directions: E, SE, S, SW, W, NW, N, NE
    int directions[8][2] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1},
        {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };

    // Frequency map for primes
    int prime_count[MAX_NUM + 1] = {0};

    // Traverse each cell in the matrix
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[0]; j++) {
            // Explore all directions
            for (int d = 0; d < 8; d++) {
                int x = i, y = j;
                int num = 0;

                // Build numbers in the current direction
                while (x >= 0 && x < matSize && y >= 0 && y < matColSize[0]) {
                    num = num * 10 + mat[x][y];
                    if (num > 10 && num <= MAX_NUM && is_prime[num]) {
                        prime_count[num]++;
                    }
                    x += directions[d][0];
                    y += directions[d][1];
                }
            }
        }
    }

    // Find the most frequent prime greater than 10
    int max_freq = 0;
    int result = -1;
    for (int num = 11; num <= MAX_NUM; num++) {
        if (prime_count[num] > max_freq) {
            max_freq = prime_count[num];
            result = num;
        } else if (prime_count[num] == max_freq && prime_count[num] > 0) {
            if (num > result) {
                result = num;
            }
        }

}
    return result;
}