// Source: https://leetcode.com/problems/longest-turbulent-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the length of a maximum size turbulent subarray of arr.
//
// A subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.
//
// More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said to be turbulent if and only if:
//
//
// 	For i <= k < j:
//
// 	
// 		arr[k] > arr[k + 1] when k is odd, and
// 		arr[k] < arr[k + 1] when k is even.
// 	
// 	
// 	Or, for i <= k < j:
// 	
// 		arr[k] > arr[k + 1] when k is even, and
// 		arr[k] < arr[k + 1] when k is odd.
//
// Example:
// Input: arr = [9,4,2,10,7,8,8,1,9]
// Output: 5
// Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
//
// Constraints:
// 1 <= arr.length <= 4 * 104
// 	0 <= arr[i] <= 109
//

class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 1;

        int maxLength = 1;
        int left = 0;

        for (int right = 1; right < n; ++right) {
            if (arr[right] == arr[right - 1]) {
                left = right;
            } else if (right == n - 1 || (arr[right] > arr[right + 1]) == (arr[right] > arr[right - 1])) {
                maxLength = max(maxLength, right - left + 1);
                left = right;
            }
        }

        return maxLength;           
    }
};
