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

/**
 * @param {string[]} wordlist
 * @param {string[]} queries
 * @return {string[]}
 */
var spellchecker = function(wordlist, queries) {
    const exactWords = new Set(wordlist);
    const caseInsensitiveMap = new Map();
    const vowelErrorMap = new Map();
    const vowels = new Set(['a', 'e', 'i', 'o', 'u']);
    const devowel = (word) => {
        return word
            .toLowerCase()
            .split('')
            .map(char => (vowels.has(char) ? '*' : char))
            .join('');
    }
    for (const word of wordlist) {
        const lowerWord = word.toLowerCase();
        if (!caseInsensitiveMap.has(lowerWord)) {
            caseInsensitiveMap.set(lowerWord, word);
        }
        const devoweledWord = devowel(word);
        if (!vowelErrorMap.has(devoweledWord)) {
            vowelErrorMap.set(devoweledWord, word);
        }
    }
    const result = [];
    for (const query of queries) {
        if (exactWords.has(query)) {
            result.push(query);
        } else {
            const lowerQuery = query.toLowerCase();
            if (caseInsensitiveMap.has(lowerQuery)) {
                result.push(caseInsensitiveMap.get(lowerQuery));
            }
            else {
                const devoweledQuery = devowel(query);  
                if (vowelErrorMap.has(devoweledQuery)) {
                    result.push(vowelErrorMap.get(devoweledQuery));
                }
                else {
                    result.push("");
                }
            }
        }
    }
    return result;  
            
};
