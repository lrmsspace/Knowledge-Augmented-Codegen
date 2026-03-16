// Source: https://leetcode.com/problems/super-pow/   |   Difficulty: Medium
//
// Problem Description:
// Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.
//
// Example:
// Input: a = 2, b = [3]
// Output: 8
//
// Constraints:
// 1 <= a <= 231 - 1
// 	1 <= b.length <= 2000
// 	0 <= b[i] <= 9
// 	b does not contain leading zeros.
//

int superPow(int a, int* b, int bSize) {
    const int MOD = 1337;

    // Function to perform modular exponentiation
    int modExp(int base, int exp, int mod) {
        int result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }

    int result = 1;
    for (int i = 0; i < bSize; i++) {
        result = modExp(result, 10, MOD); // Raise current result to the power of 10
        result = (result * modExp(a, b[i], MOD)) % MOD; // Multiply by a^(b[i])
    }

    return result;      
}
