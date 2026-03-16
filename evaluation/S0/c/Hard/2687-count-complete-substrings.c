// Source: https://leetcode.com/problems/count-complete-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an integer k.
//
// A substring s of word is complete if:
//
//
// 	Each character in s occurs exactly k times.
// 	The difference between two adjacent characters is at most 2. That is, for any two adjacent characters c1 and c2 in s, the absolute difference in their positions in the alphabet is at most 2.
//
//
// Return the number of complete substrings of word.
//
// A substring is a non-empty contiguous sequence of characters in a string.
//
// Example:
// Input: word = "igigee", k = 2
// Output: 3
// Explanation: The complete substrings where each character appears exactly twice and the difference between adjacent characters is at most 2 are: igigee, igigee, igigee.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= k <= word.length
//

int countCompleteSubstrings(char* word, int k) {
    int n = strlen(word);
    int res = 0;
    for (int i = 0; i < n; i++) {
        int count[26] = {0};
        int unique = 0;
        for (int j = i; j < n; j++) {
            int idx = word[j] - 'a';
            if (j > i) {
                int prevIdx = word[j - 1] - 'a';
                if (abs(idx - prevIdx) > 2) break;
            }
            if (count[idx] == 0) unique++;
            count[idx]++;
            if (count[idx] > k) break;
            if (count[idx] == k) {
                int allK = 1;
                for (int c = 0; c < 26; c++) {
                    if (count[c] != 0 && count[c] != k) {
                        allK = 0;
                        break;
                    }
                }
                if (allK) res++;
            }
        }
    }
    return res;     
}
