// Source: https://leetcode.com/problems/maximum-xor-product/   |   Difficulty: Medium
//
// Problem Description:
// Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x < 2n.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Note that XOR is the bitwise XOR operation.
//
// Example:
// Input: a = 12, b = 5, n = 4
// Output: 98
// Explanation: For x = 2, (a XOR x) = 14 and (b XOR x) = 7. Hence, (a XOR x) * (b XOR x) = 98. 
// It can be shown that 98 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.
//
// Constraints:
// 0 <= a, b < 250
// 	0 <= n <= 50
//

int maximumXorProduct(long long a, long long b, int n) {
    const long long MOD = 1e9 + 7;
    long long maxX = (1LL << n) - 1;
    long long x = 0;

    for (int i = n - 1; i >= 0; --i) {
        long long bitA = (a >> i) & 1;
        long long bitB = (b >> i) & 1;

        if (bitA == bitB) {
            // If both bits are the same, set the corresponding bit in x to 1
            x |= (1LL << i);
        }
        // If bits are different, leave the corresponding bit in x as 0
    }

    // Ensure x is within the range [0, 2^n)
    if (x > maxX) {
        x = maxX;
    }

    long long result = ((a ^ x) * (b ^ x)) % MOD;
    return (int)result;     
}
