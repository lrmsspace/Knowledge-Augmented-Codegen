// Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n represented as a string, return the smallest good base of n.
//
// We call k >= 2 a good base of n, if all digits of n base k are 1's.
//
// Example:
// Input: n = "13"
// Output: "3"
// Explanation: 13 base 3 is 111.
//
// Constraints:
// n is an integer in the range [3, 1018].
// 	n does not contain any leading zeros.
//

class Solution {
public:
    string smallestGoodBase(string n) {
        long long num = stoll(n);
        
        for (int m = 63; m >= 2; m--) {
            long long left = 2, right = pow(num, 1.0 / (m - 1)) + 1;
            
            while (left <= right) {
                long long mid = left + (right - left) / 2;
                
                // Calculate sum = 1 + mid + mid^2 + ... + mid^(m-1)
                long long sum = 1;
                long long term = 1;
                for (int i = 1; i < m; i++) {
                    term *= mid;
                    if (term > num) {
                        sum = num + 1; // Exceed num
                        break;
                    }
                    sum += term;
                }
                
                if (sum == num) {
                    return to_string(mid);
                } else if (sum < num) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return to_string(num - 1); // Fallback to base n-1          
    }
};
