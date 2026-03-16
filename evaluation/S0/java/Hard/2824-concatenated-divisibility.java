// Source: https://leetcode.com/problems/concatenated-divisibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k.
//
// A permutation of nums is said to form a divisible concatenation if, when you concatenate the decimal representations of the numbers in the order specified by the permutation, the resulting number is divisible by k.
//
// Return the lexicographically smallest permutation (when considered as a list of integers) that forms a divisible concatenation. If no such permutation exists, return an empty list.
//
// Example:
// Input: nums = [3,12,45], k = 5
//
// Output: [3,12,45]
//
// Explanation:
//
//
// 	
// 		
// 			Permutation
// 			Concatenated Value
// 			Divisible by 5
// 		
// 	
// 	
// 		
// 			[3, 12, 45]
// 			31245
// 			Yes
// 		
// 		
// 			[3, 45, 12]
// 			34512
// 			No
// 		
// 		
// 			[12, 3, 45]
// 			12345
// 			Yes
// 		
// 		
// 			[12, 45, 3]
// 			12453
// 			No
// 		
// 		
// 			[45, 3, 12]
// 			45312
// 			No
// 		
// 		
// 			[45, 12, 3]
// 			45123
// 			No
// 		
// 	
//
//
// The lexicographically smallest permutation that forms a divisible concatenation is [3,12,45].
//
// Constraints:
// 1 <= nums.length <= 13
// 	1 <= nums[i] <= 105
// 	1 <= k <= 100
//

class Solution {
    public int[] concatenatedDivisibility(int[] nums, int k) {
        int n = nums.length;
        int[][] mod = new int[n][101];
        int[] pow10 = new int[6];
        pow10[0] = 1;
        for (int i = 1; i < 6; i++) {
            pow10[i] = (pow10[i - 1] * 10) % k;
        }
        for (int i = 0; i < n; i++) {
            int len = Integer.toString(nums[i]).length();
            for (int j = 0; j < k; j++) {
                mod[i][j] = (j * pow10[len] + nums[i]) % k;
            }
        }

        PriorityQueue<State> pq = new PriorityQueue<>();
        pq.offer(new State(0, 0, new ArrayList<>()));
        boolean[][] visited = new boolean[1 << n][k];

        while (!pq.isEmpty()) {
            State curr = pq.poll();
            if (curr.mask == (1 << n) - 1 && curr.mod == 0) {
                return curr.path.stream().mapToInt(i -> i).toArray();
            }
            if (visited[curr.mask][curr.mod]) continue;
            visited[curr.mask][curr.mod] = true;

            for (int i = 0; i < n; i++) {
                if ((curr.mask & (1 << i)) == 0) {
                    List<Integer> newPath = new ArrayList<>(curr.path);
                    newPath.add(nums[i]);
                    pq.offer(new State(curr.mask | (1 << i), mod[i][curr.mod], newPath));
                }
            }
        }
        return new int[0];          
    }
}
