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
    public int superPow(int a, int[] b) {
        int mod = 1337;
        int result = 1;
        a = a % mod;

        for (int digit : b) {
            result = (pow(result, 10, mod) * pow(a, digit, mod)) % mod;
        }

        return result;          
    }
}
