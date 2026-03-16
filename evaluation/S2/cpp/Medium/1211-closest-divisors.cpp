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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> closestDivisors(int num) {
        auto findClosestDivisors = [](int n) {
            int a = static_cast<int>(sqrt(n));
            while (n % a != 0) {
                --a;
            }
            return vector<int>{a, n / a};
        };

        vector<int> divisors1 = findClosestDivisors(num + 1);
        vector<int> divisors2 = findClosestDivisors(num + 2);

        int diff1 = abs(divisors1[0] - divisors1[1]);
        int diff2 = abs(divisors2[0] - divisors2[1]);

        return (diff1 <= diff2) ? divisors1 : divisors2;            
    }
};
