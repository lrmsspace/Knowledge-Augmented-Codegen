// Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
//
// Problem Description:
// A peak in an array arr is an element that is greater than its previous and next element in arr.
//
// You are given an integer array nums and a 2D integer array queries.
//
// You have to process queries of two types:
//
//
// 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
// 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
//
// Output: [0]
//
// Explanation:
//
// First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
//
// Second query: The number of peaks in the [3,1,4,4,5] is 0.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i][0] == 1 or queries[i][0] == 2
// 	For all i that:
// 	
// 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
// 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> countOfPeaks(int[] nums, int[][] queries) {
        int n = nums.length;
        FenwickTree fenwickTree = new FenwickTree(n);
        for (int i = 1; i < n - 1; i++) {
            if (isPeak(nums, i)) {
                fenwickTree.update(i, 1);
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int[] query : queries) {
            int type = query[0];
            if (type == 1) {
                int left = query[1];
                int right = query[2];
                int count = fenwickTree.query(right - 1) - fenwickTree.query(left);
                result.add(count);
            } else if (type == 2) {
                int index = query[1];
                int value = query[2];
                nums[index] = value;

                for (int i = Math.max(1, index - 1); i <= Math.min(n - 2, index + 1); i++) {
                    int currentPeak = isPeak(nums, i) ? 1 : 0;
                    int previousPeak = fenwickTree.query(i) - fenwickTree.query(i - 1);
                    if (currentPeak != previousPeak) {
                        fenwickTree.update(i, currentPeak - previousPeak);
                    }
                }
            }
        }
        return result;          
    }
}
