// Source: https://leetcode.com/problems/verifying-an-alien-dictionary/   |   Difficulty: Easy
//
// Problem Description:
// In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.
//
// Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographically in this alien language.
//
// Example:
// Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
// Output: true
// Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 20
// 	order.length == 26
// 	All characters in words[i] and order are English lowercase letters.
//

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> order_map;
        for (int i = 0; i < order.size(); ++i) {
            order_map[order[i]] = i;
        }

        for (int i = 1; i < words.size(); ++i) {
            const string& word1 = words[i - 1];
            const string& word2 = words[i];
            int min_length = min(word1.size(), word2.size());
            bool found_difference = false;

            for (int j = 0; j < min_length; ++j) {
                if (word1[j] != word2[j]) {
                    if (order_map[word1[j]] > order_map[word2[j]]) {
                        return false;
                    }
                    found_difference = true;
                    break;
                }
            }

            if (!found_difference && word1.size() > word2.size()) {
                return false;
            }
        }

        return true;            
    }
};
