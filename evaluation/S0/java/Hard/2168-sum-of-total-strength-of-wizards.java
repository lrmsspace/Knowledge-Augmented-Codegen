// Source: https://leetcode.com/problems/sum-of-total-strength-of-wizards/   |   Difficulty: Hard
//
// Problem Description:
// As the ruler of a kingdom, you have an army of wizards at your command.
//
// You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard. For a contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength), the total strength is defined as the product of the following two values:
//
//
// 	The strength of the weakest wizard in the group.
// 	The total of all the individual strengths of the wizards in the group.
//
//
// Return the sum of the total strengths of all contiguous groups of wizards. Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: strength = [1,3,1,2]
// Output: 44
// Explanation: The following are all the contiguous groups of wizards:
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
// - [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
// - [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
// - [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
// - [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
// - [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
// - [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
// The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
//
// Constraints:
// 1 <= strength.length <= 105
// 	1 <= strength[i] <= 109
//

class Solution {
    public int totalStrength(int[] strength) {
        int n = strength.length;
        long mod = 1_000_000_007;

        // Prefix sums
        long[] prefixSum = new long[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = (prefixSum[i] + strength[i]) % mod;
        }

        // Prefix of prefix sums
        long[] prefixOfPrefixSum = new long[n + 2];
        for (int i = 0; i <= n; i++) {
            prefixOfPrefixSum[i + 1] = (prefixOfPrefixSum[i] + prefixSum[i]) % mod;
        }

        // Next smaller element to the right
        int[] nextSmaller = new int[n];
        Stack<Integer> stack = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && strength[stack.peek()] >= strength[i]) {
                stack.pop();
            }
            nextSmaller[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }

        // Previous smaller element to the left
        int[] prevSmaller = new int[n];
        stack.clear();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && strength[stack.peek()] > strength[i]) {
                stack.pop();
            }
            prevSmaller[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }

        // Calculate the total strength
        long totalStrength = 0;
        for (int i = 0; i < n; i++) {
            int left = prevSmaller[i];
            int right = nextSmaller[i];

            long leftCount = i - left;
            long rightCount = right - i;

            long sumRight = (prefixOfPrefixSum[right + 1] - prefixOfPrefixSum[i + 1] + mod) % mod;
            long sumLeft = (prefixOfPrefixSum[i + 1] - prefixOfPrefixSum[left + 1] + mod) % mod;

            long totalSum = (sumRight * leftCount % mod - sumLeft * rightCount % mod + mod) % mod;

            totalStrength = (totalStrength + strength[i] * totalSum) % mod;
            
        }
        return (int) totalStrength;
    }
}
