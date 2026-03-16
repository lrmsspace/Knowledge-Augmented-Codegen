// Source: https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums starting at i (inclusive) that has the maximum possible bitwise OR.
//
//
// 	In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the smallest subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n - 1.
//
//
// The bitwise OR of an array is the bitwise OR of all the numbers in it.
//
// Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray starting at i with maximum bitwise OR.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,0,2,1,3]
// Output: [3,3,2,2,1]
// Explanation:
// The maximum possible bitwise OR starting at any index is 3. 
// - Starting at index 0, the shortest subarray that yields it is [1,0,2].
// - Starting at index 1, the shortest subarray that yields the maximum bitwise OR is [0,2,1].
// - Starting at index 2, the shortest subarray that yields the maximum bitwise OR is [2,1].
// - Starting at index 3, the shortest subarray that yields the maximum bitwise OR is [1,3].
// - Starting at index 4, the shortest subarray that yields the maximum bitwise OR is [3].
// Therefore, we return [3,3,2,2,1].
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	0 <= nums[i] <= 109
//

class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        vector<int> lastSeen(32, -1); // To track the last seen index of each bit

        for (int i = n - 1; i >= 0; --i) {
            // Update last seen positions for bits set in nums[i]
            for (int bit = 0; bit < 32; ++bit) {
                if (nums[i] & (1 << bit)) {
                    lastSeen[bit] = i;
                }
            }

            // Determine the farthest index we need to reach to get max OR
            int farthestIndex = i;
            for (int bit = 0; bit < 32; ++bit) {
                if (lastSeen[bit] != -1) {
                    farthestIndex = max(farthestIndex, lastSeen[bit]);
                }
            }

            result[i] = farthestIndex - i + 1;
        }

        return result;          
    }
};
