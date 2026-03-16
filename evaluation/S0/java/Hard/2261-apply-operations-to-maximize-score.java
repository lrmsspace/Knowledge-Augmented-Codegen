// Source: https://leetcode.com/problems/apply-operations-to-maximize-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers and an integer k.
//
// Initially, you start with a score of 1. You have to maximize your score by applying the following operation at most k times:
//
//
// 	Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
// 	Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements exist, choose the one with the smallest index.
// 	Multiply your score by x.
//
//
// Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r, both ends being inclusive.
//
// The prime score of an integer x is equal to the number of distinct prime factors of x. For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
//
// Return the maximum possible score after applying at most k operations.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [8,3,9,3,8], k = 2
// Output: 81
// Explanation: To get a score of 81, we can apply the following operations:
// - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
// It can be proven that 81 is the highest score one can obtain.
//
// Constraints:
// 1 <= nums.length == n <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= min(n * (n + 1) / 2, 109)
//

class Solution {
    public int maximumScore(List<Integer> nums, int k) {
        int mod = (int)1e9 + 7;
        int n = nums.size();
        int maxNum = Collections.max(nums);

        // Step 1: Calculate prime scores using Sieve of Eratosthenes
        int[] primeScores = new int[maxNum + 1];
        for (int i = 2; i <= maxNum; i++) {
            if (primeScores[i] == 0) {
                for (int j = i; j <= maxNum; j += i) {
                    primeScores[j]++;
                }
            }
        }

        // Step 2: Create pairs of (num, primeScore)
        Integer[][] pairs = new Integer[n][2];
        for (int i = 0; i < n; i++) {
            pairs[i][0] = nums.get(i);
            pairs[i][1] = primeScores[nums.get(i)];
        }

        // Step 3: Sort pairs by prime score descending, then by num descending
        Arrays.sort(pairs, (a, b) -> {
            if (!b[1].equals(a[1])) {
                return b[1] - a[1];
            }
            return b[0] - a[0];
        });

        // Step 4: Calculate left and right boundaries using monotonic stack
        int[] left = new int[n];
        int[] right = new int[n];
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && nums.get(stack.peek()) < nums.get(i)) {
                stack.pop();
            }
            left[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }

        stack.clear();

        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && nums.get(stack.peek()) <= nums.get(i)) {
                stack.pop();
            }
            right[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }

        // Step 5: Calculate maximum score
        long score = 1;
        for (Integer[] pair : pairs) {
            if (k <= 0) break;
            int num = pair[0];
            int index = nums.indexOf(num);

            long count = (long)(index - left[index]) * (right[index] - index);;
            long use = Math.min(count, k);
            score = (score * modPow(num, use, mod)) % mod;
            k -= use;
        }
        return (int) score;
    }
    private long modPow(long base, long exp, int mod) {
        long result = 1;
        base = base % mod;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
}
