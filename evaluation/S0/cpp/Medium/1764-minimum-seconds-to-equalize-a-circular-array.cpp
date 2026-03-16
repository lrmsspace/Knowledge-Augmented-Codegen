// Source: https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums containing n integers.
//
// At each second, you perform the following operation on the array:
//
//
// 	For every index i in the range [0, n - 1], replace nums[i] with either nums[i], nums[(i - 1 + n) % n], or nums[(i + 1) % n].
//
//
// Note that all the elements get replaced simultaneously.
//
// Return the minimum number of seconds needed to make all elements in the array nums equal.
//
// Example:
// Input: nums = [1,2,1,2]
// Output: 1
// Explanation: We can equalize the array in 1 second in the following way:
// - At 1st second, replace values at each index with [nums[3],nums[1],nums[3],nums[3]]. After replacement, nums = [2,2,2,2].
// It can be proven that 1 second is the minimum amount of seconds needed for equalizing the array.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> lastOccurrence;
        int maxInterval = 0;

        for (int i = 0; i < 2 * n; ++i) {
            int num = nums[i % n];
            if (lastOccurrence.find(num) != lastOccurrence.end()) {
                int interval = i - lastOccurrence[num] - 1;
                maxInterval = max(maxInterval, interval);
            }
            lastOccurrence[num] = i;
        }

        return (maxInterval + 1) / 2;           
    }
};
