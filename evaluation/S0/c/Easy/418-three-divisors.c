// Source: https://leetcode.com/problems/three-divisors/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if n has exactly three positive divisors. Otherwise, return false.
//
// An integer m is a divisor of n if there exists an integer k such that n = k * m.
//
// Example:
// Input: n = 2
// Output: false
// Explantion: 2 has only two divisors: 1 and 2.
//
// Constraints:
// 1 <= n <= 104
//

bool isThree(int n) {
    if (n < 4) {
        return false;
    }
    
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (i * i != n) {
                count++;
            }
        }
        if (count > 3) {
            return false;
        }
    }
    
    return count == 3;      
}
