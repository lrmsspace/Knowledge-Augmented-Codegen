// Source: https://leetcode.com/problems/stamping-the-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings stamp and target. Initially, there is a string s of length target.length with all s[i] == '?'.
//
// In one turn, you can place stamp over s and replace every letter in the s with the corresponding letter from stamp.
//
//
// 	For example, if stamp = "abc" and target = "abcba", then s is "?????" initially. In one turn you can:
//
// 	
// 		place stamp at index 0 of s to obtain "abc??",
// 		place stamp at index 1 of s to obtain "?abc?", or
// 		place stamp at index 2 of s to obtain "??abc".
// 	
// 	Note that stamp must be fully contained in the boundaries of s in order to stamp (i.e., you cannot place stamp at index 3 of s).
//
//
// We want to convert s to target using at most 10 * target.length turns.
//
// Return an array of the index of the left-most letter being stamped at each turn. If we cannot obtain target from s within 10 * target.length turns, return an empty array.
//
// Example:
// Input: stamp = "abc", target = "ababc"
// Output: [0,2]
// Explanation: Initially s = "?????".
// - Place stamp at index 0 to get "abc??".
// - Place stamp at index 2 to get "ababc".
// [1,0,2] would also be accepted as an answer, as well as some other answers.
//
// Constraints:
// 1 <= stamp.length <= target.length <= 1000
// 	stamp and target consist of lowercase English letters.
//

class Solution {
    public int[] movesToStamp(String stamp, String target) {
        char[] S = stamp.toCharArray();
        char[] T = target.toCharArray();
        int sLen = S.length, tLen = T.length;
        boolean[] visited = new boolean[tLen];
        List<Integer> res = new ArrayList<>();
        int stars = 0;

        while (stars < tLen) {
            boolean doneReplace = false;
            for (int i = 0; i <= tLen - sLen; i++) {
                if (!visited[i] && canReplace(T, S, i)) {
                    stars += doReplace(T, sLen, i);
                    doneReplace = true;
                    visited[i] = true;
                    res.add(i);
                    if (stars == tLen) break;
                }
            }
            if (!doneReplace) return new int[0];
        }

        Collections.reverse(res);
        return res.stream().mapToInt(i -> i).toArray();         
    }
}
