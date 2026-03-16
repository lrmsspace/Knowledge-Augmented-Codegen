// Source: https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
//
// Example:
// Input: arr = [5,5,4], k = 1
// Output: 1
// Explanation: Remove the single 4, only 5 is left.
//
// Constraints:
// 1 <= arr.length <= 10^5
// 	1 <= arr[i] <= 10^9
// 	0 <= k <= arr.length
//

class Solution {

    public int findLeastNumOfUniqueInts(int[] arr, int k) {

        
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : arr) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        PriorityQueue<Integer> minHeap = new PriorityQueue<>(frequencyMap.values());

        while (k > 0 && !minHeap.isEmpty()) {
            int freq = minHeap.poll();
            if (k >= freq) {
                k -= freq;
            } else {
                minHeap.offer(freq); // Put it back if we can't remove all occurrences
                break;
            }
        }

        return minHeap.size();
    }

}
