// Source: https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string array words.
//
// Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:
//
//
// 	isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and false otherwise.
//
//
// For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and also a suffix, but isPrefixAndSuffix("abc", "abcd") is false.
//
// Return an integer denoting the number of index pairs (i, j) such that i < j, and isPrefixAndSuffix(words[i], words[j]) is true.
//
// Example:
// Input: words = ["a","aba","ababa","aa"]
// Output: 4
// Explanation: In this example, the counted index pairs are:
// i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
// i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
// i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
// i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
// Therefore, the answer is 4.
//
// Constraints:
// 1 <= words.length <= 105
// 	1 <= words[i].length <= 105
// 	words[i] consists only of lowercase English letters.
// 	The sum of the lengths of all words[i] does not exceed 5 * 105.
//

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        unordered_map<string, int> prefixCount;
        long long result = 0;
        
        for (const string& word : words) {
            // Count prefixes
            for (int len = 1; len <= word.length(); len++) {
                string prefix = word.substr(0, len);
                prefixCount[prefix]++;
            }
        }
        
        for (const string& word : words) {
            // Count suffixes and match with prefixes
            for (int len = 1; len <= word.length(); len++) {
                string suffix = word.substr(word.length() - len, len);
                if (prefixCount.find(suffix) != prefixCount.end()) {
                    result += prefixCount[suffix];
                    // If the suffix is the same as the word itself, decrement by 1
                    if (suffix == word) {
                        result--;
                    }
                }
            }
        }
        
        return result / 2;  // Each pair counted twice          
    }
};
