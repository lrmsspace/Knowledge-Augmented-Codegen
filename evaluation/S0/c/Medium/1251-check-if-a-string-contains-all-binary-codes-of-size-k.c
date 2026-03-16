// Source: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
//
// Example:
// Input: s = "00110110", k = 2
// Output: true
// Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s[i] is either '0' or '1'.
// 	1 <= k <= 20
//

bool hasAllCodes(char* s, int k) {
    int needed = 1 << k;
    int len = strlen(s);
    if (len < k + needed - 1) {
        return false;
    }

    int hash = 0;
    int allOnes = needed - 1;
    bool *seen = (bool *)calloc(needed, sizeof(bool));
    for (int i = 0; i < len; i++) {
        hash = ((hash << 1) & allOnes) | (s[i] - '0');
        if (i >= k - 1 && !seen[hash]) {
            seen[hash] = true;
            needed--;
            if (needed == 0) {
                free(seen);
                return true;
            }
        }
    }

    free(seen);
    return false;       
}
