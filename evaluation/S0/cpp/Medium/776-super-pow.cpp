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

class Solution {
public:
    int superPow(int a, vector<int>& b) {
        const int MOD = 1337;

        // Function to perform modular exponentiation
        auto modExp = [&](int base, int exp) {
            int result = 1;
            base %= MOD;
            while (exp > 0) {
                if (exp % 2 == 1) {
                    result = (result * base) % MOD;
                }
                base = (base * base) % MOD;
                exp /= 2;
            }
            return result;
        };

        int result = 1;
        for (int digit : b) {
            result = modExp(result, 10); // Raise current result to the power of 10
            result = (result * modExp(a, digit)) % MOD; // Multiply by a^digit
        }

        return result;          
    }
};
