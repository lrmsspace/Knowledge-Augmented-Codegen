// Source: https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
//
// 	word contains the first letter of puzzle.
// 	For each letter in word, that letter is in puzzle.
// 	
// 		For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage", while
// 		invalid words are "beefed" (does not include 'a') and "based" (includes 's' which is not in the puzzle).
// 	
// 	
//
// Return an array answer, where answer[i] is the number of words in the given word list words that is valid with respect to the puzzle puzzles[i].
//
// Example:
// Input: words = ["aaaa","asas","able","ability","actt","actor","access"], puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
// Output: [1,1,3,2,4,0]
// Explanation: 
// 1 valid word for "aboveyz" : "aaaa" 
// 1 valid word for "abrodyz" : "aaaa"
// 3 valid words for "abslute" : "aaaa", "asas", "able"
// 2 valid words for "absoryz" : "aaaa", "asas"
// 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
// There are no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
//
// Constraints:
// 1 <= words.length <= 105
// 	4 <= words[i].length <= 50
// 	1 <= puzzles.length <= 104
// 	puzzles[i].length == 7
// 	words[i] and puzzles[i] consist of lowercase English letters.
// 	Each puzzles[i] does not contain repeated characters.
//

class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> freq;
        
        // Preprocess words into bitmask frequency map
        for (const string& word : words) {
            int mask = 0;
            for (char c : word) {
                mask |= (1 << (c - 'a'));
            }
            // Only consider words with up to 7 unique letters
            if (__builtin_popcount(mask) <= 7) {
                freq[mask]++;
            }
        }
        
        vector<int> result;
        
        // Process each puzzle
        for (const string& puzzle : puzzles) {
            int total = 0;
            int firstCharMask = 1 << (puzzle[0] - 'a');
            
            // Generate all subsets of the last 6 letters
            int mask = 0;
            for (int i = 1; i < 7; i++) {
                mask |= (1 << (puzzle[i] - 'a'));
            }
            
            // Iterate through all subsets of mask
            int subset = mask;
            do {
                int combinedMask = subset | firstCharMask;
                if (freq.count(combinedMask)) {
                    total += freq[combinedMask];
                }
                subset = (subset - 1) & mask; // Get next subset
            } while (subset != mask);
            
            result.push_back(total);
        }
        
        return result;          
    }
};
