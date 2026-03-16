// Source: https://leetcode.com/problems/construct-target-array-with-multiple-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :
//
//
// 	let x be the sum of all elements currently in your array.
// 	choose index i, such that 0 <= i < n and set the value of arr at index i to x.
// 	You may repeat this procedure as many times as needed.
//
//
// Return true if it is possible to construct the target array from arr, otherwise, return false.
//
// Example:
// Input: target = [9,3,5]
// Output: true
// Explanation: Start with arr = [1, 1, 1] 
// [1, 1, 1], sum = 3 choose index 1
// [1, 3, 1], sum = 5 choose index 2
// [1, 3, 5], sum = 9 choose index 0
// [9, 3, 5] Done
//
// Constraints:
// n == target.length
// 	1 <= n <= 5 * 104
// 	1 <= target[i] <= 109
//

class Solution {
    public boolean isPossible(int[] target) {
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        long total = 0;
        for (int num : target) {
            pq.offer(num);
            total += num;
        }

        while (true) {
            int largest = pq.poll();
            long rest = total - largest;

            if (largest == 1 || rest == 1) {
                return true;
            }

            if (rest == 0 || largest < rest) {
                return false;
            }

            int updated = (int)(largest % rest);
            if (updated == 0) {
                return false;
            }

            pq.offer(updated);
            total = rest + updated;
        }                   
    }
}
