// Source: https://leetcode.com/problems/nth-magical-number/   |   Difficulty: Hard
//
// Problem Description:
// A positive integer is magical if it is divisible by either a or b.
//
// Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 1, a = 2, b = 3
// Output: 2
//
// Constraints:
// 1 <= n <= 109
// 	2 <= a, b <= 4 * 104
//

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        const int MOD = 1e9 + 7;
        
        // Function to compute gcd
        auto gcd = [](int x, int y) {
            while (y != 0) {
                int temp = y;
                y = x % y;
                x = temp;
            }
            return x;
        };
        
        int lcm = (a / gcd(a, b)) * b;  // Least common multiple of a and b
        
        long long left = 1, right = 1e18;  // Search space for nth magical number
        long long answer = 0;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            
            // Count how many magical numbers are <= mid
            long long count = mid / a + mid / b - mid / lcm;
            
            if (count >= n) {
                answer = mid;  // Potential answer
                right = mid - 1;  // Try to find a smaller one
            } else {
                left = mid + 1;  // Increase search space
            }
        }
        
        return answer % MOD;            
    }
};
