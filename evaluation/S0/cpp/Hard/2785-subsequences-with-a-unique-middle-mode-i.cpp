// Source: https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, find the number of subsequences of size 5 of nums with a unique middle mode.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A mode of a sequence of numbers is defined as the element that appears the maximum number of times in the sequence.
//
// A sequence of numbers contains a unique mode if it has only one mode.
//
// A sequence of numbers seq of size 5 contains a unique middle mode if the middle element (seq[2]) is a unique mode.
//
// Example:
// Input: nums = [1,1,1,1,1,1]
//
// Output: 6
//
// Explanation:
//
// [1, 1, 1, 1, 1] is the only subsequence of size 5 that can be formed, and it has a unique middle mode of 1. This subsequence can be formed in 6 different ways, so the output is 6.
//
// Constraints:
// 5 <= nums.length <= 1000
//  -109 <= nums[i] <= 109
//

class Solution {
public:
    int subsequencesWithMiddleMode(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long result = 0;

        for (int mid = 2; mid <= n - 3; mid++) {
            unordered_map<int, int> leftCount, rightCount;
            for (int i = 0; i < mid; i++) {
                leftCount[nums[i]]++;
            }
            for (int i = mid + 1; i < n; i++) {
                rightCount[nums[i]]++;
            }

            for (const auto& [num, countMid] : unordered_map<int, int>{{nums[mid], 1}}) {
                long long leftWays = 0, rightWays = 0;

                for (const auto& [leftNum, leftCnt] : leftCount) {
                    if (leftNum != num) {
                        leftWays = (leftWays + leftCnt) % MOD;
                    }
                }

                for (const auto& [rightNum, rightCnt] : rightCount) {
                    if (rightNum != num) {
                        rightWays = (rightWays + rightCnt) % MOD;
                    }
                }

                result = (result + (leftWays * rightWays) % MOD) % MOD;
            }

            leftCount[nums[mid]]--;
            if (leftCount[nums[mid]] == 0) {
                leftCount.erase(nums[mid]);
            }
        }

        return (int)result;         
    }
};
