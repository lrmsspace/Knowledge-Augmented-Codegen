// Source: https://leetcode.com/problems/make-number-of-distinct-characters-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings word1 and word2.
//
// A move consists of choosing two indices i and j such that 0 <= i < word1.length and 0 <= j < word2.length and swapping word1[i] with word2[j].
//
// Return true if it is possible to get the number of distinct characters in word1 and word2 to be equal with exactly one move. Return false otherwise.
//
// Example:
// Input: word1 = "ac", word2 = "b"
// Output: false
// Explanation: Any pair of swaps would yield two distinct characters in the first string, and one in the second string.
//
// Constraints:
// 1 <= word1.length, word2.length <= 105
// 	word1 and word2 consist of only lowercase English letters.
//

bool isItPossible(char* word1, char* word2) {
    int count1[26] = {0}, count2[26] = {0};
    int distinct1 = 0, distinct2 = 0;

    for (int i = 0; word1[i]; i++) {
        if (count1[word1[i] - 'a']++ == 0) {
            distinct1++;
        }
    }

    for (int i = 0; word2[i]; i++) {
        if (count2[word2[i] - 'a']++ == 0) {
            distinct2++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (count1[i] == 0) continue;
        for (int j = 0; j < 26; j++) {
            if (count2[j] == 0) continue;

            int newDistinct1 = distinct1;
            int newDistinct2 = distinct2;

            if (i != j) {
                if (count1[j] == 0) newDistinct1++;
                if (count2[i] == 0) newDistinct2++;

                if (--count1[i] == 0) newDistinct1--;
                if (--count2[j] == 0) newDistinct2--;
            }

            if (newDistinct1 == newDistinct2) {
                return true;
            }

            // Restore counts
            count1[i]++;
            count2[j]++;
        }
    }

    return false;       
}
