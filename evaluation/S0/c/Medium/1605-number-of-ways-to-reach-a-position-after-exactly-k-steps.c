// Source: https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers startPos and endPos. Initially, you are standing at position startPos on an infinite number line. With one step, you can move either one position to the left, or one position to the right.
//
// Given a positive integer k, return the number of different ways to reach the position endPos starting from startPos, such that you perform exactly k steps. Since the answer may be very large, return it modulo 109 + 7.
//
// Two ways are considered different if the order of the steps made is not exactly the same.
//
// Note that the number line includes negative integers.
//
// Example:
// Input: startPos = 1, endPos = 2, k = 3
// Output: 3
// Explanation: We can reach position 2 from 1 in exactly 3 steps in three ways:
// - 1 -> 2 -> 3 -> 2.
// - 1 -> 2 -> 1 -> 2.
// - 1 -> 0 -> 1 -> 2.
// It can be proven that no other way is possible, so we return 3.
//
// Constraints:
// 1 <= startPos, endPos, k <= 1000
//

int numberOfWays(int startPos, int endPos, int k) {
    const int MOD = 1e9 + 7;
    int dist = abs(endPos - startPos);
    
    // If the distance is greater than k or the parity of distance and k is different, return 0
    if (dist > k || (k - dist) % 2 != 0) {
        return 0;
    }
    
    // Calculate the number of right moves needed
    int rightMoves = (k + dist) / 2;
    
    // Precompute factorials and modular inverses for combinations
    long long fact[k + 1];
    long long invFact[k + 1];
    fact[0] = 1;
    for (int i = 1; i <= k; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    invFact[k] = powMod(fact[k], MOD - 2, MOD);
    for (int i = k - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
    
    // Calculate combinations C(k, rightMoves)
    long long result = (fact[k] * invFact[rightMoves]) % MOD;
    result = (result * invFact[k - rightMoves]) % MOD;
    
    return (int)result;     
}
