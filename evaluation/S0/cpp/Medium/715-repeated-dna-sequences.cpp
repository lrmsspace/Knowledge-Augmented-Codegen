// Source: https://leetcode.com/problems/repeated-dna-sequences/   |   Difficulty: Medium
//
// Problem Description:
// The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
//
//
// 	For example, "ACGAATTCCG" is a DNA sequence.
//
//
// When studying DNA, it is useful to identify repeated sequences within the DNA.
//
// Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.
//
// Example:
// Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
// Output: ["AAAAACCCCC","CCCCCAAAAA"]
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either 'A', 'C', 'G', or 'T'.
//

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_set<string> seen;
        unordered_set<string> repeated;
        vector<string> result;

        for (size_t i = 0; i + 10 <= s.length(); ++i) {
            string substring = s.substr(i, 10);
            if (seen.count(substring)) {
                repeated.insert(substring);
            } else {
                seen.insert(substring);
            }
        }

        for (const auto& seq : repeated) {
            result.push_back(seq);
        }

        return result;          
    }
};
