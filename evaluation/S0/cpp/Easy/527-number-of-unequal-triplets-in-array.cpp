// Source: https://leetcode.com/problems/number-of-unequal-triplets-in-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums. Find the number of triplets (i, j, k) that meet the following conditions:
//
//
// 	0 <= i < j < k < nums.length
// 	nums[i], nums[j], and nums[k] are pairwise distinct.
// 	
// 		In other words, nums[i] != nums[j], nums[i] != nums[k], and nums[j] != nums[k].
// 	
// 	
//
//
// Return the number of triplets that meet the conditions.
//
// Example:
// Input: nums = [4,4,2,4,3]
// Output: 3
// Explanation: The following triplets meet the conditions:
// - (0, 2, 4) because 4 != 2 != 3
// - (1, 2, 4) because 4 != 2 != 3
// - (2, 3, 4) because 2 != 4 != 3
// Since there are 3 triplets, we return 3.
// Note that (2, 0, 4) is not a valid triplet because 2 > 0.
//
// Constraints:
// 3 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//

class Solution {
public:
    int unequalTriplets(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        int result = 0;
        int n = nums.size();
        for (const auto& [num_i, count_i] : freq) {
            for (const auto& [num_j, count_j] : freq) {
                if (num_j == num_i) continue;
                for (const auto& [num_k, count_k] : freq) {
                    if (num_k == num_i || num_k == num_j) continue;
                    result += count_i * count_j * count_k;
                }
            }
        }

        // Each triplet is counted 6 times (i,j,k), (i,k,j), (j,i,k), (j,k,i), (k,i,j), (k,j,i)
        return result / 6;          
    }
};
