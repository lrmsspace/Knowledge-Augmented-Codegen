// Source: https://leetcode.com/problems/maximum-product-of-word-lengths/   |   Difficulty: Medium
//
// Problem Description:
// Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. If no such two words exist, return 0.
//
// Example:
// Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
// Output: 16
// Explanation: The two words can be "abcw", "xtfn".
//
// Constraints:
// 2 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	words[i] consists only of lowercase English letters.
//

class Solution {
    public int maxProduct(String[] words) {
        int n = words.length;
        int[] bitMasks = new int[n];

        for (int i = 0; i < n; i++) {
            for (char c : words[i].toCharArray()) {
                bitMasks[i] |= 1 << (c - 'a');
            }
        }

        int maxProduct = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((bitMasks[i] & bitMasks[j]) == 0) {
                    int product = words[i].length() * words[j].length();
                    maxProduct = Math.max(maxProduct, product);
                }
            }
        }

        return maxProduct;          
    }
}
