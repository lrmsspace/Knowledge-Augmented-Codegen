// Source: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
//
// Return the minimum possible absolute difference.
//
// Example:
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
//
// Constraints:
// 1 <= n <= 15
// 	nums.length == 2 * n
// 	-107 <= nums[i] <= 107
//

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size() / 2;
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // Split nums into two halves
        vector<int> left(nums.begin(), nums.begin() + n);
        vector<int> right(nums.begin() + n, nums.end());
        
        // Generate all possible sums for each half
        unordered_map<int, vector<int>> leftSums;
        unordered_map<int, vector<int>> rightSums;
        
        for (int mask = 0; mask < (1 << n); ++mask) {
            int sumLeft = 0, countLeft = 0;
            int sumRight = 0, countRight = 0;
            
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    sumLeft += left[i];
                    countLeft++;
                } else {
                    sumRight += right[i];
                    countRight++;
                }
            }
            
            leftSums[countLeft].push_back(sumLeft);
            rightSums[countRight].push_back(sumRight);
        }
        
        // Sort the sums in rightSums for binary search
        for (auto& [count, sums] : rightSums) {
            sort(sums.begin(), sums.end());
        }
        
        int minDiff = INT_MAX;
        
        // Try all combinations of counts
        for (int count = 0; count <= n; ++count) {
            for (int sumLeft : leftSums[count]) {
                int target = totalSum / 2 - sumLeft;
                
                // Binary search in rightSums[count]
                const auto& sumsRight = rightSums[n - count];
                auto it = lower_bound(sumsRight.begin(), sumsRight.end(), target);
                
                // Check the closest sums
                if (it != sumsRight.end()) {
                    int sumRight = *it;
                    int currentSum = sumLeft + sumRight;
                    minDiff = min(minDiff, abs(totalSum - 2 * currentSum));
                }
                
                if (it != sumsRight.begin()) {
                    --it;
                    int sumRight = *it;
                    int currentSum = sumLeft + sumRight;
                    minDiff = min(minDiff, abs(totalSum - 2 * currentSum));
                }
            }
        }
        
        return minDiff;         
    }
};
