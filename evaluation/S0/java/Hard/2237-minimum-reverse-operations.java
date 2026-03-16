// Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
//
//
// 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
//
//
// Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
//
// Example:
// Input: n = 4, p = 0, banned = [1,2], k = 4
//
// Output: [0,-1,-1,1]
//
// Explanation:
//
//
// 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
// 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
// 	Perform the operation of size 4 to reverse the whole array.
// 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= p <= n - 1
// 	0 <= banned.length <= n - 1
// 	0 <= banned[i] <= n - 1
// 	1 <= k <= n 
// 	banned[i] != p
// 	all values in banned are unique
//

class Solution {
    public int[] minReverseOperations(int n, int p, int[] banned, int k) {
        int[] res = new int[n];
        Arrays.fill(res, -1);
        res[p] = 0;

        TreeSet<Integer> even = new TreeSet<>();
        TreeSet<Integer> odd = new TreeSet<>();

        for (int b : banned) {
            res[b] = -2; // mark banned positions
        }

        for (int i = 0; i < n; i++) {
            if (res[i] == -1) {
                if (i % 2 == 0) {
                    even.add(i);
                } else {
                    odd.add(i);
                }
            }
        }

        Queue<Integer> queue = new LinkedList<>();
        queue.offer(p);

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            int start = Math.max(0, curr - k + 1);
            int end = Math.min(n - k, curr) + k - 1;

            int lowerBound = start + end - curr;
            int upperBound = end + start - curr;

            TreeSet<Integer> targetSet = (lowerBound % 2 == 0) ? even : odd;
            Integer nextPos = targetSet.ceiling(lowerBound);

            while (nextPos != null && nextPos <= upperBound) {
                res[nextPos] = res[curr] + 1;
                queue.offer(nextPos);
                targetSet.remove(nextPos);
                nextPos = targetSet.ceiling(lowerBound);
            }
        }

        for (int i = 0; i < n; i++) {
            if (res[i] == -2) {
                res[i] = -1; // convert banned markers back to -1
            }
        }

        return res;         
    }
}
