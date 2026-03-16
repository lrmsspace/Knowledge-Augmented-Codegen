// Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
//
// Problem Description:
// You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
//
// We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
//
// Example:
// Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
// Output: [20,24]
// Explanation: 
// List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
// List 2: [0, 9, 12, 20], 20 is in range [20,24].
// List 3: [5, 18, 22, 30], 22 is in range [20,24].
//
// Constraints:
// nums.length == k
// 	1 <= k <= 3500
// 	1 <= nums[i].length <= 50
// 	-105 <= nums[i][j] <= 105
// 	nums[i] is sorted in non-decreasing order.
//

class Solution {
    public int[] smallestRange(List<List<Integer>> nums) {
        PriorityQueue<Element> minHeap = new PriorityQueue<>((a, b) -> a.value - b.value);
        int currentMax = Integer.MIN_VALUE;

        // Initialize the heap with the first element of each list
        for (int i = 0; i < nums.size(); i++) {
            int value = nums.get(i).get(0);
            minHeap.offer(new Element(value, i, 0));
            currentMax = Math.max(currentMax, value);
        }

        int rangeStart = 0, rangeEnd = Integer.MAX_VALUE;

        while (minHeap.size() == nums.size()) {
            Element currentMin = minHeap.poll();

            // Update the range if it's smaller
            if (currentMax - currentMin.value < rangeEnd - rangeStart) {
                rangeStart = currentMin.value;
                rangeEnd = currentMax;
            }

            // If there is a next element in the same list, add it to the heap
            if (currentMin.indexInList + 1 < nums.get(currentMin.listIndex).size()) {
                int nextValue = nums.get(currentMin.listIndex).get(currentMin.indexInList + 1);
                minHeap.offer(new Element(nextValue, currentMin.listIndex, currentMin.indexInList + 1));
                currentMax = Math.max(currentMax, nextValue);
            }
        }

        return new int[]{rangeStart, rangeEnd};         
    }
}
