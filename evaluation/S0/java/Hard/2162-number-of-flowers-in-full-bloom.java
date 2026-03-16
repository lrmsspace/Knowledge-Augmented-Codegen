// Source: https://leetcode.com/problems/number-of-flowers-in-full-bloom/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where people[i] is the time that the ith person will arrive to see the flowers.
//
// Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith person arrives.
//
// Example:
// Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
// Output: [1,2,2,2]
// Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
// For each person, we return the number of flowers in full bloom during their arrival.
//
// Constraints:
// 1 <= flowers.length <= 5 * 104
// 	flowers[i].length == 2
// 	1 <= starti <= endi <= 109
// 	1 <= people.length <= 5 * 104
// 	1 <= people[i] <= 109
//

class Solution {
    public int[] fullBloomFlowers(int[][] flowers, int[] people) {
        int n = people.length;
        int[] result = new int[n];

        int m = flowers.length;
        int[] startTimes = new int[m];
        int[] endTimes = new int[m];

        for (int i = 0; i < m; i++) {
            startTimes[i] = flowers[i][0];
            endTimes[i] = flowers[i][1];
        }

        Arrays.sort(startTimes);
        Arrays.sort(endTimes);

        for (int i = 0; i < n; i++) {
            int arrivalTime = people[i];
            int flowersStarted = upperBound(startTimes, arrivalTime);
            int flowersEnded = lowerBound(endTimes, arrivalTime);
            result[i] = flowersStarted - flowersEnded;
        }

        return result;          
    }
}
