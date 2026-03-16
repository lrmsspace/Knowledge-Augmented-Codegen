// Source: https://leetcode.com/problems/partition-labels/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part. For example, the string "ababcc" can be partitioned into ["abab", "cc"], but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.
//
// Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.
//
// Return a list of integers representing the size of these parts.
//
// Example:
// Input: s = "ababcbacadefegdehijhklij"
// Output: [9,7,8]
// Explanation:
// The partition is "ababcbaca", "defegde", "hijhklij".
// This is a partition so that each letter appears in at most one part.
// A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

class Solution {
    public List<Integer> partitionLabels(String s) {
        List<Integer> result = new ArrayList<>();
        int[] lastIndex = new int[26];

        // Record the last index of each character in the string
        for (int i = 0; i < s.length(); i++) {
            lastIndex[s.charAt(i) - 'a'] = i;
        }

        int partitionStart = 0;
        int partitionEnd = 0;

        // Iterate through the string to determine partitions
        for (int i = 0; i < s.length(); i++) {
            partitionEnd = Math.max(partitionEnd, lastIndex[s.charAt(i) - 'a']);

            // If the current index reaches the partition end, we found a partition
            if (i == partitionEnd) {
                result.add(partitionEnd - partitionStart + 1);
                partitionStart = i + 1;
            }
        }

        return result;          
    }
}
