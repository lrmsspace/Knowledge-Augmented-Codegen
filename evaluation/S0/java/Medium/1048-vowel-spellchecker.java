// Source: https://leetcode.com/problems/vowel-spellchecker/   |   Difficulty: Medium
//
// Problem Description:
// Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
//
// For a given query word, the spell checker handles two categories of spelling mistakes:
//
//
// 	Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
//
// Example:
// wordlist = ["yellow"], query = "YellOw": correct = "yellow"
//
// Constraints:
// 1 <= wordlist.length, queries.length <= 5000
// 	1 <= wordlist[i].length, queries[i].length <= 7
// 	wordlist[i] and queries[i] consist only of only English letters.
//

class Solution {
    public String[] spellchecker(String[] wordlist, String[] queries) {
        Set<String> exactWords = new HashSet<>();
        Map<String, String> caseInsensitiveMap = new HashMap<>();
        Map<String, String> vowelErrorMap = new HashMap<>();

        for (String word : wordlist) {
            exactWords.add(word);

            String lowerWord = word.toLowerCase();
            caseInsensitiveMap.putIfAbsent(lowerWord, word);

            String devoweledWord = devowel(lowerWord);
            vowelErrorMap.putIfAbsent(devoweledWord, word);
        }

        String[] result = new String[queries.length];
        for (int i = 0; i < queries.length; i++) {
            String query = queries[i];

            if (exactWords.contains(query)) {
                result[i] = query;
            } else {
                String lowerQuery = query.toLowerCase();
                if (caseInsensitiveMap.containsKey(lowerQuery)) {
                    result[i] = caseInsensitiveMap.get(lowerQuery);
                } else {
                    String devoweledQuery = devowel(lowerQuery);
                    result[i] = vowelErrorMap.getOrDefault(devoweledQuery, "");
                }
            }
        }

        return result;          
    }
}
