// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

class Solution {
    public List<String> maxNumOfSubstrings(String s) {
        int n = s.length();
        int[][] intervals = new int[26][2];
        for (int i = 0; i < 26; i++) {
            intervals[i][0] = n;
            intervals[i][1] = -1;
        }
        for (int i = 0; i < n; i++) {
            int c = s.charAt(i) - 'a';
            intervals[c][0] = Math.min(intervals[c][0], i);
            intervals[c][1] = Math.max(intervals[c][1], i);
        }

        List<int[]> candidates = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            if (intervals[i][1] == -1) continue;
            int left = intervals[i][0];
            int right = intervals[i][1];
            boolean valid = true;
            for (int j = left; j <= right; j++) {
                int c = s.charAt(j) - 'a';
                if (intervals[c][0] < left) {
                    valid = false;
                    break;
                }
                right = Math.max(right, intervals[c][1]);
            }
            if (valid) {
                candidates.add(new int[]{left, right});
            }
        }

        candidates.sort(Comparator.comparingInt(a -> a[1]));

        List<String> result = new ArrayList<>();
        int prevEnd = -1;
        for (int[] interval : candidates) {
            if (interval[0] > prevEnd) {
                result.add(s.substring(interval[0], interval[1] + 1));
                prevEnd = interval[1];
            }
        }

        return result;                  
    }
}
