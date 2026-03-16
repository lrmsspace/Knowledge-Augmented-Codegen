// Source: https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, return the number of distinct prime factors in the product of the elements of nums.
//
// Note that:
//
//
// 	A number greater than 1 is called prime if it is divisible by only 1 and itself.
// 	An integer val1 is a factor of another integer val2 if val2 / val1 is an integer.
//
// Example:
// Input: nums = [2,4,3,7,10,6]
// Output: 4
// Explanation:
// The product of all the elements in nums is: 2 * 4 * 3 * 7 * 10 * 6 = 10080 = 25 * 32 * 5 * 7.
// There are 4 distinct prime factors so we return 4.
//
// Constraints:
// 1 <= nums.length <= 104
// 	2 <= nums[i] <= 1000
//

class Solution {
public:
    int distinctPrimeFactors(vector<int>& nums) {
        unordered_set<int> primeFactors;

        for (int num : nums) {
            int n = num;
            for (int i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    primeFactors.insert(i);
                    while (n % i == 0) {
                        n /= i;
                    }
                }
            }
            if (n > 1) {
                primeFactors.insert(n);
            }
        }

        return primeFactors.size();         
    }
};
