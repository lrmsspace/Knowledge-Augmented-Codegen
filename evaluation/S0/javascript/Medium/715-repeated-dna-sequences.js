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

/**
 * @param {string} s
 * @return {string[]}
 */
var findRepeatedDnaSequences = function(s) {
    const seen = new Set();
    const repeated = new Set();

    for (let i = 0; i <= s.length - 10; i++) {
        const sequence = s.substring(i, i + 10);
        if (seen.has(sequence)) {
            repeated.add(sequence);
        } else {
            seen.add(sequence);
        }
    }

    return Array.from(repeated);
};