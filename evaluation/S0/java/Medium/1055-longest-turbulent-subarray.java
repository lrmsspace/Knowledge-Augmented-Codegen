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
    public int maxTurbulenceSize(int[] arr) {
        if (arr.length == 1) return 1;

        int maxLen = 1;
        int currLen = 1;
        int prevSign = 0; // 0: equal, 1: greater, -1: less

        for (int i = 1; i < arr.length; i++) {
            int currSign = Integer.compare(arr[i], arr[i - 1]);

            if (currSign == 0) {
                currLen = 1;
            } else if (currSign != prevSign) {
                currLen++;
            } else {
                currLen = 2; // reset length to 2 (current and previous)
            }

            maxLen = Math.max(maxLen, currLen);
            prevSign = currSign;
        }

        return maxLen;          
    }
}
