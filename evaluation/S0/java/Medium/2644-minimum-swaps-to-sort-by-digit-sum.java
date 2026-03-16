// Source: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct positive integers. You need to sort the array in increasing order based on the sum of the digits of each number. If two numbers have the same digit sum, the smaller number appears first in the sorted order.
//
// Return the minimum number of swaps required to rearrange nums into this sorted order.
//
// A swap is defined as exchanging the values at two distinct positions in the array.
//
// Example:
// Input: nums = [37,100]
//
// Output: 1
//
// Explanation:
//
//
// 	Compute the digit sum for each integer: [3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]
// 	Sort the integers based on digit sum: [100, 37]. Swap 37 with 100 to obtain the sorted order.
// 	Thus, the minimum number of swaps required to rearrange nums is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums consists of distinct positive integers.
//

class Solution {
    public int minSwaps(int[] nums) {
        int n = nums.length;
        int[][] arr = new int[n][2];

        for (int i = 0; i < n; i++) {
            arr[i][0] = digitSum(nums[i]);
            arr[i][1] = nums[i];
        }

        Arrays.sort(arr, (a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            } else {
                return Integer.compare(a[1], b[1]);
            }
        });

        boolean[] visited = new boolean[n];
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || arr[i][1] == nums[i]) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = indexOf(nums, arr[j][1]);
                cycleSize++;
            }

            if (cycleSize > 0) {
                swaps += (cycleSize - 1);
            }
        }

        return swaps;           
    }
}
