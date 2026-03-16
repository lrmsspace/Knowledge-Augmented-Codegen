// Source: https://leetcode.com/problems/minimum-array-changes-to-make-differences-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n where n is even, and an integer k.
//
// You can perform some changes on the array, where in one change you can replace any element in the array with any integer in the range from 0 to k.
//
// You need to perform some changes (possibly none) such that the final array satisfies the following condition:
//
//
// 	There exists an integer X such that abs(a[i] - a[n - i - 1]) = X for all (0 <= i < n).
//
//
// Return the minimum number of changes required to satisfy the above condition.
//
// Example:
// Input: nums = [1,0,1,2,4,3], k = 4
//
// Output: 2
//
// Explanation:
// We can perform the following changes:
//
//
// 	Replace nums[1] by 2. The resulting array is nums = [1,2,1,2,4,3].
// 	Replace nums[3] by 3. The resulting array is nums = [1,2,1,3,4,3].
//
//
// The integer X will be 2.
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	n is even.
// 	0 <= nums[i] <= k <= 105
//

class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> diffCount(k + 2, 0);
        int totalPairs = n / 2;

        for (int i = 0; i < n / 2; ++i) {
            int a = nums[i];
            int b = nums[n - i - 1];
            int low = min(a, b) + 1;
            int high = max(a, b) + k + 1;
            int d = abs(a - b);

            diffCount[0] += 2; // Assume both need to change
            diffCount[low] -= 1; // One change possible
            diffCount[d] -= 1; // No change needed
            diffCount[d + 1] += 1; // No change needed ends
            diffCount[high] += 1; // One change possible ends
        }

        int minChanges = totalPairs;
        int currentChanges = 0;

        for (int x = 0; x <= k; ++x) {
            currentChanges += diffCount[x];
            minChanges = min(minChanges, currentChanges);
        }

        return minChanges;          
    }
};
