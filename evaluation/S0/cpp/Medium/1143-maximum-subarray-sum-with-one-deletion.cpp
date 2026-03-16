// Source: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
//
// Note that the subarray needs to be non-empty after deleting one element.
//
// Example:
// Input: arr = [1,-2,0,3]
// Output: 4
// Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
//
// Constraints:
// 1 <= arr.length <= 105
// 	-104 <= arr[i] <= 104
//

class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp_no_delete(n, 0);  // Max sum subarray ending at i without deletion
        vector<int> dp_one_delete(n, 0); // Max sum subarray ending at i with one deletion

        dp_no_delete[0] = arr[0];
        dp_one_delete[0] = INT_MIN; // Cannot delete the only element

        int max_sum = arr[0];

        for (int i = 1; i < n; ++i) {
            dp_no_delete[i] = max(arr[i], dp_no_delete[i - 1] + arr[i]);
            dp_one_delete[i] = max(dp_one_delete[i - 1] + arr[i], dp_no_delete[i - 1]);
            max_sum = max(max_sum, max(dp_no_delete[i], dp_one_delete[i]));
        }

        return max_sum;         
    }
};
