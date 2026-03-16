// Source: https://leetcode.com/problems/count-of-range-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.
//
// Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.
//
// Example:
// Input: nums = [-2,5,-1], lower = -2, upper = 2
// Output: 3
// Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
// 	-105 <= lower <= upper <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> prefixSums(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }
        
        function<int(int, int)> countWhileMergeSort = [&](int left, int right) {
            if (right - left <= 1) return 0;
            int mid = left + (right - left) / 2;
            int count = countWhileMergeSort(left, mid) + countWhileMergeSort(mid, right);
            int j = mid, k = mid, t = mid;
            vector<long long> temp(right - left);
            for (int i = left, r = 0; i < mid; i++, r++) {
                while (k < right && prefixSums[k] - prefixSums[i] < lower) k++;
                while (j < right && prefixSums[j] - prefixSums[i] <= upper) j++;
                while (t < right && prefixSums[t] < prefixSums[i]) temp[r++] = prefixSums[t++];
                temp[r] = prefixSums[i];
                count += j - k;
            }
            copy(temp.begin(), temp.begin() + (t - left), prefixSums.begin() + left);
            return count;
        };
        
        return countWhileMergeSort(0, n + 1);           
    }
};
