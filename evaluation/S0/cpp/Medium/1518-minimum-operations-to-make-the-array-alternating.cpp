// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of n positive integers.
//
// The array nums is called alternating if:
//
//
// 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
// 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
//
//
// In one operation, you can choose an index i and change nums[i] into any positive integer.
//
// Return the minimum number of operations required to make the array alternating.
//
// Example:
// Input: nums = [3,1,3,2,4,3]
// Output: 3
// Explanation:
// One way to make the array alternating is by converting it to [3,1,3,1,3,1].
// The number of operations required in this case is 3.
// It can be proven that it is not possible to make the array alternating in less than 3 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_map<int, int> oddCount;
        unordered_map<int, int> evenCount;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                evenCount[nums[i]]++;
            } else {
                oddCount[nums[i]]++;
            }
        }

        auto getTopTwo = [](const unordered_map<int, int>& countMap) {
            pair<int, int> top1 = {0, 0}; // {number, frequency}
            pair<int, int> top2 = {0, 0};
            for (const auto& [num, freq] : countMap) {
                if (freq > top1.second) {
                    top2 = top1;
                    top1 = {num, freq};
                } else if (freq > top2.second) {
                    top2 = {num, freq};
                }
            }
            return make_pair(top1, top2);
        };

        auto [evenTop1, evenTop2] = getTopTwo(evenCount);
        auto [oddTop1, oddTop2] = getTopTwo(oddCount);

        if (evenTop1.first != oddTop1.first) {
            return n - evenTop1.second - oddTop1.second;
        } else {
            return min(n - evenTop1.second - oddTop2.second,
                       n - evenTop2.second - oddTop1.second);
        }           
    }
};
