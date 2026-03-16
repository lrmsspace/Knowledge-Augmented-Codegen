// Source: https://leetcode.com/problems/rearrange-characters-to-make-target-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 0-indexed strings s and target. You can take some letters from s and rearrange them to form new strings.
//
// Return the maximum number of copies of target that can be formed by taking letters from s and rearranging them.
//
// Example:
// Input: s = "ilovecodingonleetcode", target = "code"
// Output: 2
// Explanation:
// For the first copy of "code", take the letters at indices 4, 5, 6, and 7.
// For the second copy of "code", take the letters at indices 17, 18, 19, and 20.
// The strings that are formed are "ecod" and "code" which can both be rearranged into "code".
// We can make at most two copies of "code", so we return 2.
//
// Constraints:
// 1 <= s.length <= 100
// 	1 <= target.length <= 10
// 	s and target consist of lowercase English letters.
//
//
//  
// Note: This question is the same as  1189: Maximum Number of Balloons.
//

class Solution {
    public int rearrangeCharacters(String s, String target) {
        int[] sCount = new int[26];
        int[] targetCount = new int[26];

        for (char c : s.toCharArray()) {
            sCount[c - 'a']++;
        }

        for (char c : target.toCharArray()) {
            targetCount[c - 'a']++;
        }

        int maxCopies = Integer.MAX_VALUE;

        for (int i = 0; i < 26; i++) {
            if (targetCount[i] > 0) {
                maxCopies = Math.min(maxCopies, sCount[i] / targetCount[i]);
            }
        }

        return maxCopies;           
    }
}
