// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
//
// Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// Example:
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
//
// Output: [2,3]
//
// Explanation:
//
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
//
// Constraints:
// 1 <= intevals.length <= 5 * 104
// 	intervals[i].length == 3
// 	intervals[i] = [li, ri, weighti]
// 	1 <= li <= ri <= 109
// 	1 <= weighti <= 109
//

class Solution {
    public int[] maximumWeight(List<List<Integer>> intervals) {
        int n = intervals.size();
        int[][] dp = new int[n + 1][5];
        int[][] next = new int[n + 1][5];
        int[][] sortedIntervals = new int[n][4];

        for (int i = 0; i < n; i++) {
            sortedIntervals[i][0] = intervals.get(i).get(0);
            sortedIntervals[i][1] = intervals.get(i).get(1);
            sortedIntervals[i][2] = intervals.get(i).get(2);
            sortedIntervals[i][3] = i;
        }

        Arrays.sort(sortedIntervals, Comparator.comparingInt(a -> a[0]));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 1; j <= 4; j++) {
                int skipWeight = dp[i + 1][j];
                int takeWeight = sortedIntervals[i][2];
                int nextIndex = binarySearch(sortedIntervals, sortedIntervals[i][1]);

                if (nextIndex < n) {
                    takeWeight += dp[nextIndex][j - 1];
                }

                if (takeWeight > skipWeight) {
                    dp[i][j] = takeWeight;
                    next[i][j] = nextIndex;
                } else {
                    dp[i][j] = skipWeight;
                    next[i][j] = -1;
                }
            }
        }

        List<Integer> result = new ArrayList<>();
        int index = 0;
        for (int j = 4; j >= 1; j--) {
            if (next[index][j] != -1 || dp[index][j] > dp[index + 1][j]) {
                result.add(sortedIntervals[index][3]);
                index = next[index][j];
            } else {
                index++;
            }
        }

        Collections.sort(result);
        return result.stream().mapToInt(i -> i).toArray();          
    }
}
