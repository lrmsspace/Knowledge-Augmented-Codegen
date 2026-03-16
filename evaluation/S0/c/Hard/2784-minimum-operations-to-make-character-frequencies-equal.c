// Source: https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s.
//
// A string t is called good if all characters of t occur the same number of times.
//
// You can perform the following operations any number of times:
//
//
//  Delete a character from s.
//  Insert a character in s.
//  Change a character in s to its next letter in the alphabet.
//
//
// Note that you cannot change 'z' to 'a' using the third operation.
//
// Return the minimum number of operations required to make s good.
//
// Example:
// Input: s = "acab"
//
// Output: 1
//
// Explanation:
//
// We can make s good by deleting one occurrence of character 'a'.
//
// Constraints:
// 3 <= s.length <= 2 * 104
//  s contains only lowercase English letters.
//

int makeStringGood(char* s) {
    int freq[26] = {0};
    for (char *p = s; *p; ++p) {
        freq[*p - 'a']++;
    }

    int counts[20001] = {0};
    int maxFreq = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            counts[freq[i]]++;
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
            }
        }
    }

    int minOps = 2000000000;
    for (int targetFreq = 1; targetFreq <= maxFreq; ++targetFreq) {
        int ops = 0;
        for (int f = 1; f <= maxFreq; ++f) {
            if (counts[f] == 0) continue;
            if (f < targetFreq) {
                ops += (targetFreq - f) * counts[f];
            } else if (f > targetFreq) {
                ops += (f - targetFreq) * counts[f];
            }
        }
        if (ops < minOps) {
            minOps = ops;
        }
    }

    return minOps;      
}
