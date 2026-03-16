// Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of unique strings words.
//
// A palindrome pair is a pair of integers (i, j) such that:
//
//
//  0 <= i, j < words.length,
//  i != j, and
//  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
//
//
// Return an array of all the palindrome pairs of words.
//
// You must write an algorithm with O(sum of words[i].length) runtime complexity.
//
// Example:
// Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
// Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
//
// Constraints:
// 1 <= words.length <= 5000
//  0 <= words[i].length <= 300
//  words[i] consists of lowercase English letters.
//

class Solution {
    public List<List<Integer>> palindromePairs(String[] words) {
        List<List<Integer>> result = new ArrayList<>();
        Map<String, Integer> map = new HashMap<>();

        for (int i = 0; i < words.length; i++) {
            map.put(words[i], i);
        }

        for (int i = 0; i < words.length; i++) {
            String word = words[i];
            for (int j = 0; j <= word.length(); j++) {
                String left = word.substring(0, j);
                String right = word.substring(j);

                if (isPalindrome(left)) {
                    String reversedRight = new StringBuilder(right).reverse().toString();
                    if (map.containsKey(reversedRight) && map.get(reversedRight) != i) {
                        result.add(Arrays.asList(map.get(reversedRight), i));
                    }
                }

                if (isPalindrome(right) && right.length() != 0) {
                    String reversedLeft = new StringBuilder(left).reverse().toString();
                    if (map.containsKey(reversedLeft) && map.get(reversedLeft) != i) {
                        result.add(Arrays.asList(i, map.get(reversedLeft)));
                    }
                }
            }
        }

        return result;          
    }
}
