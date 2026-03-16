// Source: https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.
//
// In case of a tie, return the minimum such integer.
//
// Notice that the answer is not neccesarilly a number from arr.
//
// Example:
// Input: arr = [4,9,3], target = 10
// Output: 3
// Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
//
// Constraints:
// 1 <= arr.length <= 104
// 	1 <= arr[i], target <= 105
//

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int left = 0, right = *max_element(arr.begin(), arr.end());
        int bestValue = right;
        int minDiff = INT_MAX;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long currentSum = 0;

            for (int num : arr) {
                currentSum += (num > mid) ? mid : num;
            }

            int currentDiff = abs(currentSum - target);
            if (currentDiff < minDiff || (currentDiff == minDiff && mid < bestValue)) {
                minDiff = currentDiff;
                bestValue = mid;
            }

            if (currentSum < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return bestValue;           
    }
};
