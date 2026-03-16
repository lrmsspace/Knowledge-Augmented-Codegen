// Source: https://leetcode.com/problems/closest-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.
//
// Return the two integers in any order.
//
// Example:
// Input: num = 8
// Output: [3,3]
// Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
//
// Constraints:
// 1 <= num <= 10^9
//

class Solution {
public:
    vector<int> closestDivisors(int num) {
        auto findClosestDivisors = [](int n) {
            int sqrtN = static_cast<int>(sqrt(n));
            for (int i = sqrtN; i >= 1; --i) {
                if (n % i == 0) {
                    return vector<int>{i, n / i};
                }
            }
            return vector<int>{1, n}; // Fallback, should not reach here for n >= 1
        };

        vector<int> divisors1 = findClosestDivisors(num + 1);
        vector<int> divisors2 = findClosestDivisors(num + 2);

        int diff1 = abs(divisors1[0] - divisors1[1]);
        int diff2 = abs(divisors2[0] - divisors2[1]);

        return (diff1 <= diff2) ? divisors1 : divisors2;            
    }
};
