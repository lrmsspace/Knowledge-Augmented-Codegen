// Source: https://leetcode.com/problems/maximal-score-after-applying-k-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.
//
// In one operation:
//
//
// 	choose an index i such that 0 <= i < nums.length,
// 	increase your score by nums[i], and
// 	replace nums[i] with ceil(nums[i] / 3).
//
//
// Return the maximum possible score you can attain after applying exactly k operations.
//
// The ceiling function ceil(val) is the least integer greater than or equal to val.
//
// Example:
// Input: nums = [10,10,10,10,10], k = 5
// Output: 50
// Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.
//
// Constraints:
// 1 <= nums.length, k <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> maxHeap;
        for (int num : nums) {
            maxHeap.push(num);
        }

        long long score = 0;
        for (int i = 0; i < k; ++i) {
            int top = maxHeap.top();
            maxHeap.pop();
            score += top;
            int newVal = (top + 2) / 3; // Equivalent to ceil(top / 3)
            maxHeap.push(newVal);
        }

        return score;           
    }
};
