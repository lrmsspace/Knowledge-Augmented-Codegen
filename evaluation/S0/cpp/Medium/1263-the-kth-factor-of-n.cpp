// Source: https://leetcode.com/problems/the-kth-factor-of-n/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and k. A factor of an integer n is defined as an integer i where n % i == 0.
//
// Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.
//
// Example:
// Input: n = 12, k = 3
// Output: 3
// Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.
//
// Constraints:
// 1 <= k <= n <= 1000
//
//
//  
// Follow up:
//
// Could you solve this problem in less than O(n) complexity?
//

class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> smallFactors;
        vector<int> largeFactors;

        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                smallFactors.push_back(i);
                if (i != n / i) {
                    largeFactors.push_back(n / i);
                }
            }
        }

        int totalFactors = smallFactors.size() + largeFactors.size();
        if (k > totalFactors) {
            return -1;
        }

        if (k <= smallFactors.size()) {
            return smallFactors[k - 1];
        } else {
            return largeFactors[largeFactors.size() - (k - smallFactors.size())];
        }           
    }
};
