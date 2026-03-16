// Source: https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the maximum number of occurrences of any substring under the following rules:
//
//
// 	The number of unique characters in the substring must be less than or equal to maxLetters.
// 	The substring size must be between minSize and maxSize inclusive.
//
// Example:
// Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
// Output: 2
// Explanation: Substring "aab" has 2 occurrences in the original string.
// It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= maxLetters <= 26
// 	1 <= minSize <= maxSize <= min(26, s.length)
// 	s consists of only lowercase English letters.
//

class Solution {
    public int maxFreq(String s, int maxLetters, int minSize, int maxSize) {
        Map<String, Integer> substringCount = new HashMap<>();
        int maxOccurrences = 0;

        for (int i = 0; i <= s.length() - minSize; i++) {
            String substring = s.substring(i, i + minSize);
            Set<Character> uniqueChars = new HashSet<>();

            for (char c : substring.toCharArray()) {
                uniqueChars.add(c);
            }

            if (uniqueChars.size() <= maxLetters) {
                substringCount.put(substring, substringCount.getOrDefault(substring, 0) + 1);
                maxOccurrences = Math.max(maxOccurrences, substringCount.get(substring));
            }
        }

        return maxOccurrences;          
    }
}
