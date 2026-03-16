// Source: https://leetcode.com/problems/number-of-different-integers-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word that consists of digits and lowercase English letters.
//
// You will replace every non-digit character with a space. For example, "a123bc34d8ef34" will become " 123  34 8  34". Notice that you are left with some integers that are separated by at least one space: "123", "34", "8", and "34".
//
// Return the number of different integers after performing the replacement operations on word.
//
// Two integers are considered different if their decimal representations without any leading zeros are different.
//
// Example:
// Input: word = "a123bc34d8ef34"
// Output: 3
// Explanation: The three different integers are "123", "34", and "8". Notice that "34" is only counted once.
//
// Constraints:
// 1 <= word.length <= 1000
// 	word consists of digits and lowercase English letters.
//

class Solution {
    public int numDifferentIntegers(String word) {
        String[] parts = word.replaceAll("[a-z]", " ").split(" ");
        Set<String> uniqueIntegers = new HashSet<>();

        for (String part : parts) {
            if (!part.isEmpty()) {
                // Remove leading zeros
                String normalized = part.replaceFirst("^0+", "");
                if (normalized.isEmpty()) {
                    normalized = "0"; // If all were zeros, treat as "0"
                }
                uniqueIntegers.add(normalized);
            }
        }

        return uniqueIntegers.size();           
    }
}
