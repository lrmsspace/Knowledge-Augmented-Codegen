// Source: https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers m, n, and k.
//
// There is a rectangular grid of size m × n containing k identical pieces. Return the sum of Manhattan distances between every pair of pieces over all valid arrangements of pieces.
//
// A valid arrangement is a placement of all k pieces on the grid with at most one piece per cell.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
//
// Example:
// Input: m = 2, n = 2, k = 2
//
// Output: 8
//
// Explanation:
//
// The valid arrangements of pieces on the board are:
//
//
//
//
// 	In the first 4 arrangements, the Manhattan distance between the two pieces is 1.
// 	In the last 2 arrangements, the Manhattan distance between the two pieces is 2.
//
//
// Thus, the total Manhattan distance across all valid arrangements is 1 + 1 + 1 + 1 + 2 + 2 = 8.
//
// Constraints:
// 1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	2 <= k <= m * n
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int distanceSum(int m, int n, int k) {
        final int MOD = 1_000_000_007;

        // Precompute factorials and modular inverses for binomial coefficients
        int max = m * n;
        long[] fact = new long[max + 1];
        long[] invFact = new long[max + 1];
        fact[0] = 1;
        for (int i = 1; i <= max; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[max] = modInverse(fact[max], MOD);
        for (int i = max - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // Function to compute binomial coefficient C(n, k) % MOD
        java.util.function.BiFunction<Integer, Integer, Long> binom = (a, b) -> {
            if (b > a || b < 0) return 0L;
            return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
        };

        // Calculate total Manhattan distance sum
        long totalDistance = 0;

        // Horizontal distances
        for (int dist = 1; dist < n; dist++) {
            long countPairs = (long)(n - dist) * m * m % MOD;
            totalDistance = (totalDistance + dist * countPairs) % MOD;
        }

        // Vertical distances
        for (int dist = 1; dist < m; dist++) {
            long countPairs = (long)(m - dist) * n * n % MOD;
            totalDistance = (totalDistance + dist * countPairs) % MOD;
        }

        // Multiply by the number of ways to choose remaining pieces
        long arrangements = binom.apply(m * n - 2, k - 2);
        totalDistance = totalDistance * arrangements % MOD;

        return (int) totalDistance;         
    }
}
