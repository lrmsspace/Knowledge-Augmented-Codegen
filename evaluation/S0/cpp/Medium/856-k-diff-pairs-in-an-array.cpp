// Source: https://leetcode.com/problems/k-diff-pairs-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
//
// A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
//
//
// 	0 <= i, j < nums.length
// 	i != j
// 	|nums[i] - nums[j]| == k
//
//
// Notice that |val| denotes the absolute value of val.
//
// Example:
// Input: nums = [3,1,4,1,5], k = 2
// Output: 2
// Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
// Although we have two 1s in the input, we should only return the number of unique pairs.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-107 <= nums[i] <= 107
// 	0 <= k <= 107
//

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) return 0; // No valid pairs for negative k

        unordered_map<int, int> numCount;
        for (int num : nums) {
            numCount[num]++;
        }

        int pairCount = 0;
        for (const auto& [num, count] : numCount) {
            if (k == 0) {
                // For k = 0, count pairs of identical numbers
                if (count > 1) {
                    pairCount++;
                }
            } else {
                // For k > 0, check if the complement exists
                if (numCount.find(num + k) != numCount.end()) {
                    pairCount++;
                }
            }
        }

        return pairCount;           
    }
};
