// Source: https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums, an integer k, and an integer multiplier.
//
// You need to perform k operations on nums. In each operation:
//
//
// 	Find the minimum value x in nums. If there are multiple occurrences of the minimum value, select the one that appears first.
// 	Replace the selected minimum value x with x * multiplier.
//
//
// After the k operations, apply modulo 109 + 7 to every value in nums.
//
// Return an integer array denoting the final state of nums after performing all k operations and then applying the modulo.
//
// Example:
// Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
//
// Output: [8,4,6,5,6]
//
// Explanation:
//
//
// 	
// 		
// 			Operation
// 			Result
// 		
// 		
// 			After operation 1
// 			[2, 2, 3, 5, 6]
// 		
// 		
// 			After operation 2
// 			[4, 2, 3, 5, 6]
// 		
// 		
// 			After operation 3
// 			[4, 4, 3, 5, 6]
// 		
// 		
// 			After operation 4
// 			[4, 4, 6, 5, 6]
// 		
// 		
// 			After operation 5
// 			[8, 4, 6, 5, 6]
// 		
// 		
// 			After applying modulo
// 			[8, 4, 6, 5, 6]
//
// Constraints:
// 1 <= nums.length <= 104
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
// 	1 <= multiplier <= 106
//

class Solution {
    public int[] getFinalState(int[] nums, int k, int multiplier) {
        int n = nums.length;
        PriorityQueue<int[]> minHeap = new PriorityQueue<>((a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            }
            return Integer.compare(a[1], b[1]);
        });

        for (int i = 0; i < n; i++) {
            minHeap.offer(new int[]{nums[i], i});
        }

        for (int i = 0; i < k; i++) {
            int[] curr = minHeap.poll();
            curr[0] *= multiplier;
            minHeap.offer(curr);
        }

        int MOD = 1_000_000_007;
        int[] result = new int[n];
        while (!minHeap.isEmpty()) {
            int[] curr = minHeap.poll();
            result[curr[1]] = curr[0] % MOD;
        }

        return result;          
    }
}
