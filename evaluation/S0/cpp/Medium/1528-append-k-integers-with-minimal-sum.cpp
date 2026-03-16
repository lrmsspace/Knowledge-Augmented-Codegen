// Source: https://leetcode.com/problems/append-k-integers-with-minimal-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Append k unique positive integers that do not appear in nums to nums such that the resulting total sum is minimum.
//
// Return the sum of the k integers appended to nums.
//
// Example:
// Input: nums = [1,4,25,10,25], k = 2
// Output: 5
// Explanation: The two unique positive integers that do not appear in nums which we append are 2 and 3.
// The resulting sum of nums is 1 + 4 + 25 + 10 + 25 + 2 + 3 = 70, which is the minimum.
// The sum of the two integers appended is 2 + 3 = 5, so we return 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 108
//

class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        long long result = 0;
        long long nextNum = 1;
        for (int num : nums) {
            if (k <= 0) break;
            if (num < nextNum) continue;
            long long count = min((long long)k, num - nextNum);
            result += (nextNum + nextNum + count - 1) * count / 2;
            k -= count;
            nextNum = (long long)num + 1;
        }
        if (k > 0) {
            result += (nextNum + nextNum + k - 1) * k / 2;
        }
        return result;          
    }
};
