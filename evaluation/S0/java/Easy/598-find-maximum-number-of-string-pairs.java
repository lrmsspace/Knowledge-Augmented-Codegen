// Source: https://leetcode.com/problems/find-maximum-number-of-string-pairs/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array words consisting of distinct strings.
//
// The string words[i] can be paired with the string words[j] if:
//
//
// 	The string words[i] is equal to the reversed string of words[j].
// 	0 <= i < j < words.length.
//
//
// Return the maximum number of pairs that can be formed from the array words.
//
// Note that each string can belong in at most one pair.
//
// Example:
// Input: words = ["cd","ac","dc","ca","zz"]
// Output: 2
// Explanation: In this example, we can form 2 pair of strings in the following way:
// - We pair the 0th string with the 2nd string, as the reversed string of word[0] is "dc" and is equal to words[2].
// - We pair the 1st string with the 3rd string, as the reversed string of word[1] is "ca" and is equal to words[3].
// It can be proven that 2 is the maximum number of pairs that can be formed.
//
// Constraints:
// 1 <= words.length <= 50
// 	words[i].length == 2
// 	words consists of distinct strings.
// 	words[i] contains only lowercase English letters.
//

class Solution {
    public int maximumNumberOfStringPairs(String[] words) {
        int count = 0;
        Set<String> seen = new HashSet<>();

        for (String word : words) {
            String reversed = new StringBuilder(word).reverse().toString();
            if (seen.contains(reversed)) {
                count++;
                seen.remove(reversed); // Remove to ensure each string is used at most once
            } else {
                seen.add(word);
            }
        }

        return count;           
    }
}
