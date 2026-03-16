// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct integers.
//
// In one operation, you can swap any two adjacent elements in the array.
//
// An arrangement of the array is considered valid if the parity of adjacent elements alternates, meaning every pair of neighboring elements consists of one even and one odd number.
//
// Return the minimum number of adjacent swaps required to transform nums into any valid arrangement.
//
// If it is impossible to rearrange nums such that no two adjacent elements have the same parity, return -1.
//
// Example:
// Input: nums = [2,4,6,5,7]
//
// Output: 3
//
// Explanation:
//
// Swapping 5 and 6, the array becomes [2,4,5,6,7]
//
// Swapping 5 and 4, the array becomes [2,5,4,6,7]
//
// Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid arrangement. Thus, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements in nums are distinct.
//

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> evenIndices, oddIndices;
        for (int i = 0; i < n; ++i) {
            if (nums[i] % 2 == 0) {
                evenIndices.push_back(i);
            } else {
                oddIndices.push_back(i);
            }
        }

        int evenCount = evenIndices.size();
        int oddCount = oddIndices.size();

        if (abs(evenCount - oddCount) > 1) {
            return -1;
        }

        auto calculateSwaps = [&](const vector<int>& targetIndices, bool startWithEven) {
            int swaps = 0;
            for (int i = 0; i < targetIndices.size(); ++i) {
                int expectedIndex = startWithEven ? i * 2 : i * 2 + 1;
                swaps += abs(targetIndices[i] - expectedIndex);
            }
            return swaps;
        };

        int minSwaps = INT_MAX;
        if (evenCount >= oddCount) {
            minSwaps = min(minSwaps, calculateSwaps(evenIndices, true));
        }
        if (oddCount >= evenCount) {
            minSwaps = min(minSwaps, calculateSwaps(oddIndices, false));
        }

        return minSwaps;            
    }
};
