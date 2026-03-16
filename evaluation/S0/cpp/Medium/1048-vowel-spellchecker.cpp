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
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> exactWords(wordlist.begin(), wordlist.end());
        unordered_map<string, string> caseInsensitiveMap;
        unordered_map<string, string> vowelErrorMap;

        for (const string& word : wordlist) {
            string lowerWord = toLower(word);
            if (caseInsensitiveMap.find(lowerWord) == caseInsensitiveMap.end()) {
                caseInsensitiveMap[lowerWord] = word;
            }
            string devoweledWord = devowel(lowerWord);
            if (vowelErrorMap.find(devoweledWord) == vowelErrorMap.end()) {
                vowelErrorMap[devoweledWord] = word;
            }
        }

        vector<string> result;
        for (const string& query : queries) {
            if (exactWords.count(query)) {
                result.push_back(query);
                continue;
            }
            string lowerQuery = toLower(query);
            if (caseInsensitiveMap.count(lowerQuery)) {
                result.push_back(caseInsensitiveMap[lowerQuery]);
                continue;
            }
            string devoweledQuery = devowel(lowerQuery);
            if (vowelErrorMap.count(devoweledQuery)) {
                result.push_back(vowelErrorMap[devoweledQuery]);
                continue;
            }
            result.push_back("");
        }

        return result;          
    }
};
