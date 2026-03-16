// Source: https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array complexity of length n.
//
// There are n locked computers in a room with labels from 0 to n - 1, each with its own unique password. The password of the computer i has a complexity complexity[i].
//
// The password for the computer labeled 0 is already decrypted and serves as the root. All other computers must be unlocked using it or another previously unlocked computer, following this information:
//
//
//  You can decrypt the password for the computer i using the password for computer j, where j is any integer less than i with a lower complexity. (i.e. j < i and complexity[j] < complexity[i])
//  To decrypt the password for computer i, you must have already unlocked a computer j such that j < i and complexity[j] < complexity[i].
//
//
// Find the number of permutations of [0, 1, 2, ..., (n - 1)] that represent a valid order in which the computers can be unlocked, starting from computer 0 as the only initially unlocked one.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note that the password for the computer with label 0 is decrypted, and not the computer with the first position in the permutation.
//
// Example:
// Input: complexity = [1,2,3]
//
// Output: 2
//
// Explanation:
//
// The valid permutations are:
//
//
//  [0, 1, 2]
//  
//   Unlock computer 0 first with root password.
//   Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
//   Unlock computer 2 with password of computer 1 since complexity[1] < complexity[2].
//  
//  
//  [0, 2, 1]
//  
//   Unlock computer 0 first with root password.
//   Unlock computer 2 with password of computer 0 since complexity[0] < complexity[2].
//   Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
//
// Constraints:
// 2 <= complexity.length <= 105
//  1 <= complexity[i] <= 109
//

class Solution {
    public int countPermutations(int[] complexity) {
        int MOD = 1_000_000_007;
        int n = complexity.length;

        // Precompute factorials and inverse factorials for combinations
        long[] fact = new long[n + 1];
        long[] invFact = new long[n + 1];
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[n] = modInverse(fact[n], MOD);
        for (int i = n - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // Helper function to compute nCr % MOD
        java.util.function.BiFunction<Integer, Integer, Long> nCr = (N, R) -> {
            if (R > N || R < 0) return 0L;
            return fact[N] * invFact[R] % MOD * invFact[N - R] % MOD;
        };

        // Recursive function to count permutations
        java.util.function.BiFunction<Integer, Integer, Long> count = new java.util.function.BiFunction<>() {
            public Long apply(int left, int right) {
                if (left >= right) return 1L;

                int rootComplexity = complexity[left];
                int mid = left + 1;

                while (mid <= right && complexity[mid] < rootComplexity) {
                    mid++;
                }

                long leftCount = this.apply(left + 1, mid - 1);
                long rightCount = this.apply(mid, right);

                int leftSize = mid - left - 1;
                int rightSize = right - mid + 1;

                long ways = nCr.apply(leftSize + rightSize, leftSize);
                return ways * leftCount % MOD * rightCount % MOD;
            }
        };

        return (int)(count.apply(0, n - 1) % MOD);          
    }
}
