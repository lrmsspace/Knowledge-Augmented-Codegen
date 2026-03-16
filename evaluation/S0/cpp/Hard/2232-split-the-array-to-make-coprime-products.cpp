// Source: https://leetcode.com/problems/split-the-array-to-make-coprime-products/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n.
//
// A split at an index i where 0 <= i <= n - 2 is called valid if the product of the first i + 1 elements and the product of the remaining elements are coprime.
//
//
// 	For example, if nums = [2, 3, 3], then a split at the index i = 0 is valid because 2 and 9 are coprime, while a split at the index i = 1 is not valid because 6 and 3 are not coprime. A split at the index i = 2 is not valid because i == n - 1.
//
//
// Return the smallest index i at which the array can be split validly or -1 if there is no such split.
//
// Two values val1 and val2 are coprime if gcd(val1, val2) == 1 where gcd(val1, val2) is the greatest common divisor of val1 and val2.
//
// Example:
// Input: nums = [4,7,8,15,3,5]
// Output: 2
// Explanation: The table above shows the values of the product of the first i + 1 elements, the remaining elements, and their gcd at each index i.
// The only valid split is at index 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 104
// 	1 <= nums[i] <= 106
//

class Solution {
public:
    int findValidSplit(vector<int>& nums) {
        const int MAX_NUM = 1e6;
        vector<int> spf(MAX_NUM + 1, 0);  // smallest prime factor
        for (int i = 2; i * i <= MAX_NUM; i++) {
            if (spf[i] == 0) {
                for (int j = i * i; j <= MAX_NUM; j += i) {
                    if (spf[j] == 0) {
                        spf[j] = i;
                    }
                }
            }
        }
        for (int i = 2; i <= MAX_NUM; i++) {
            if (spf[i] == 0) spf[i] = i;
        }
        
        unordered_map<int, int> lastOccurrence;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            unordered_set<int> primes;
            while (x > 1) {
                primes.insert(spf[x]);
                x /= spf[x];
            }
            for (int p : primes) {
                lastOccurrence[p] = i;
            }
        }
        
        int maxLast = -1;
        for (int i = 0; i < nums.size() - 1; i++) {
            int x = nums[i];
            unordered_set<int> primes;
            while (x > 1) {
                primes.insert(spf[x]);
                x /= spf[x];
            }
            for (int p : primes) {
                maxLast = max(maxLast, lastOccurrence[p]);
            }
            if (i == maxLast) {
                return i;
            }
        }
        
        return -1;          
    }
};
