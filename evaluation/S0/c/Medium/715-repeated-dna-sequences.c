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
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findRepeatedDnaSequences(char* s, int* returnSize) {
    int len = strlen(s);
    if (len < 10) {
        *returnSize = 0;
        return NULL;
    }

    // Map to store the count of each 10-letter sequence
    #define MAX_SEQUENCES 1048576 // 4^10
    int count[MAX_SEQUENCES] = {0};
    char** result = (char**)malloc(sizeof(char*) * (len / 10));
    *returnSize = 0;

    // Function to encode a 10-letter DNA sequence into an integer
    int encode(char* str) {
        int code = 0;
        for (int i = 0; i < 10; i++) {
            code <<= 2;
            switch (str[i]) {
                case 'A': code |= 0; break;
                case 'C': code |= 1; break;
                case 'G': code |= 2; break;
                case 'T': code |= 3; break;
            }
        }
        return code;
    }

    for (int i = 0; i <= len - 10; i++) {
        int code = encode(&s[i]);
        count[code]++;
        if (count[code] == 2) { // Only add to result when it appears the second time
            result[*returnSize] = (char*)malloc(11 * sizeof(char));
            strncpy(result[*returnSize], &s[i], 10);
            result[*returnSize][10] = '\0';
            (*returnSize)++;
        }
    }

    return result;      
}
