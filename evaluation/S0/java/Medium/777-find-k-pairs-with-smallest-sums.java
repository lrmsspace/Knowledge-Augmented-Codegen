// Source: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 sorted in non-decreasing order and an integer k.
//
// Define a pair (u, v) which consists of one element from the first array and one element from the second array.
//
// Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.
//
// Example:
// Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
// Output: [[1,2],[1,4],[1,6]]
// Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	-109 <= nums1[i], nums2[i] <= 109
// 	nums1 and nums2 both are sorted in non-decreasing order.
// 	1 <= k <= 104
// 	k <= nums1.length * nums2.length
//

class Solution {
    public List<List<Integer>> kSmallestPairs(int[] nums1, int[] nums2, int k) {
        List<List<Integer>> result = new ArrayList<>();
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0] + a[1]));

        for (int i = 0; i < Math.min(nums1.length, k); i++) {
            minHeap.offer(new int[]{nums1[i], nums2[0], 0});
        }

        while (k > 0 && !minHeap.isEmpty()) {
            int[] current = minHeap.poll();
            result.add(Arrays.asList(current[0], current[1]));
            k--;

            if (current[2] + 1 < nums2.length) {
                minHeap.offer(new int[]{current[0], nums2[current[2] + 1], current[2] + 1});
            }
        }

        return result;          
    }
}
