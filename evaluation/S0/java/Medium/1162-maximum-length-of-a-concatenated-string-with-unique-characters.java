// Source: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
//
// Return the maximum possible length of s.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = ["un","iq","ue"]
// Output: 4
// Explanation: All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.
//
// Constraints:
// 1 <= arr.length <= 16
// 	1 <= arr[i].length <= 26
// 	arr[i] contains only lowercase English letters.
//

class Solution {
    public int maxLength(List<String> arr) {
        List<Integer> masks = new ArrayList<>();
        masks.add(0);
        int maxLen = 0;

        for (String s : arr) {
            int mask = 0;
            for (char c : s.toCharArray()) {
                int bit = 1 << (c - 'a');
                if ((mask & bit) != 0) {
                    mask = 0;
                    break;
                }
                mask |= bit;
            }
            if (mask == 0) continue;

            int size = masks.size();
            for (int i = 0; i < size; i++) {
                int existingMask = masks.get(i);
                if ((existingMask & mask) == 0) {
                    int newMask = existingMask | mask;
                    masks.add(newMask);
                    maxLen = Math.max(maxLen, Integer.bitCount(newMask));
                }
            }
        }

        return maxLen;          
    }
}
