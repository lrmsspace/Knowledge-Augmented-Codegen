// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, m and k, and an integer array nums.
// A sequence of integers seq is called magical if:
//
//
// 	seq has a size of m.
// 	0 <= seq[i] < nums.length
// 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
//
//
// The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
//
// Return the sum of the array products for all valid magical sequences.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A set bit refers to a bit in the binary representation of a number that has a value of 1.
//
// Example:
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
//
// Output: 991600007
//
// Explanation:
//
// All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
//
// Constraints:
// 1 <= k <= m <= 30
// 	1 <= nums.length <= 50
// 	1 <= nums[i] <= 108
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int magicalSum(int m, int k, int* nums, int numsSize) {
    // Precompute factorials and their modular inverses for binomial coefficients
    int mod = 1000000007;
    long long fact[31], invFact[31];
    fact[0] = 1;
    for (int i = 1; i <= m; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[m] = powMod(fact[m], mod - 2, mod);
    for (int i = m - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }

    // Calculate the sum of products for all magical sequences
    long long result = 0;
    for (int mask = 0; mask < (1 << numsSize); mask++) {
        if (__builtin_popcount(mask) == k) {
            long long product = 1;
            for (int j = 0; j < numsSize; j++) {
                if (mask & (1 << j)) {
                    product = (product * nums[j]) % mod;
                }
            }
            result = (result + product) % mod;
        }
    }

    return result;      
}
