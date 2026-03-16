// Source: https://leetcode.com/problems/number-of-unique-good-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string binary. A subsequence of binary is considered good if it is not empty and has no leading zeros (with the exception of "0").
//
// Find the number of unique good subsequences of binary.
//
//
// 	For example, if binary = "001", then all the good subsequences are ["0", "0", "1"], so the unique good subsequences are "0" and "1". Note that subsequences "00", "01", and "001" are not good because they have leading zeros.
//
//
// Return the number of unique good subsequences of binary. Since the answer may be very large, return it modulo 109 + 7.
//
// A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: binary = "001"
// Output: 2
// Explanation: The good subsequences of binary are ["0", "0", "1"].
// The unique good subsequences are "0" and "1".
//
// Constraints:
// 1 <= binary.length <= 105
// 	binary consists of only '0's and '1's.
//

int numberOfUniqueGoodSubsequences(char* binary) {
    const int MOD = 1000000007;
    int hasZero = 0;
    int dp0 = 0; /* count of unique good subsequences ending with '0' */
    int dp1 = 0; /* count of unique good subsequences ending with '1' */
    for (int i = 0; binary[i]; i++) {
        if (binary[i] == '0') {
            hasZero = 1;
            dp0 = (dp0 + dp1) % MOD;
        } else { /* binary[i] == '1' */
            dp1 = (dp0 + dp1 + 1) % MOD;
        }
    }
    return (dp0 + dp1 + hasZero) % MOD;     
}
