// Source: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Starting with score = 0, apply the following algorithm:
//
//
// 	Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
// 	Add the value of the chosen integer to score.
// 	Mark the chosen element and its two adjacent elements if they exist.
// 	Repeat until all the array elements are marked.
//
//
// Return the score you get after applying the above algorithm.
//
// Example:
// Input: nums = [2,1,3,4,5,2]
// Output: 7
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
// - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
// - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
// Our score is 1 + 2 + 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

class Solution {
public:
    long long findScore(vector<int>& nums) {
        int n = nums.size();
        vector<bool> marked(n, false);
        vector<pair<int, int>> numIndexPairs;
        
        for (int i = 0; i < n; ++i) {
            numIndexPairs.emplace_back(nums[i], i);
        }
        
        sort(numIndexPairs.begin(), numIndexPairs.end());
        
        long long score = 0;
        
        for (const auto& [num, index] : numIndexPairs) {
            if (!marked[index]) {
                score += num;
                marked[index] = true;
                if (index > 0) {
                    marked[index - 1] = true;
                }
                if (index < n - 1) {
                    marked[index + 1] = true;
                }
            }
        }
        
        return score;           
    }
};
