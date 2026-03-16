// Source: https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word.
//
// Return the maximum number of non-intersecting substrings of word that are at least four characters long and start and end with the same letter.
//
// Example:
// Input: word = "abcdeafdef"
//
// Output: 2
//
// Explanation:
//
// The two substrings are "abcdea" and "fdef".
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists only of lowercase English letters.
//

class Solution {
    public int maxSubstrings(String word) {
        int n = word.length();
        int[][] intervals = new int[26][2];
        for (int i = 0; i < 26; i++) {
            intervals[i][0] = n;
            intervals[i][1] = -1;
        }

        for (int i = 0; i < n; i++) {
            int c = word.charAt(i) - 'a';
            intervals[c][0] = Math.min(intervals[c][0], i);
            intervals[c][1] = Math.max(intervals[c][1], i);
        }

        List<int[]> validIntervals = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            if (intervals[i][1] - intervals[i][0] + 1 >= 4) {
                validIntervals.add(new int[]{intervals[i][0], intervals[i][1]});
            }
        }

        validIntervals.sort(Comparator.comparingInt(a -> a[1]));

        int count = 0;
        int lastEnd = -1;
        for (int[] interval : validIntervals) {
            if (interval[0] > lastEnd) {
                count++;
                lastEnd = interval[1];
            }
        }

        return count;           
    }
}
