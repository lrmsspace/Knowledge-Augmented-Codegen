// Source: https://leetcode.com/problems/longest-happy-string/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called happy if it satisfies the following conditions:
//
//
// 	s only contains the letters 'a', 'b', and 'c'.
// 	s does not contain any of "aaa", "bbb", or "ccc" as a substring.
// 	s contains at most a occurrences of the letter 'a'.
// 	s contains at most b occurrences of the letter 'b'.
// 	s contains at most c occurrences of the letter 'c'.
//
//
// Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = 1, b = 1, c = 7
// Output: "ccaccbcc"
// Explanation: "ccbccacc" would also be a correct answer.
//
// Constraints:
// 0 <= a, b, c <= 100
// 	a + b + c > 0
//

char* longestDiverseString(int a, int b, int c) {
    char *result = (char *)malloc(301 * sizeof(char));
    int index = 0;
    int counts[3] = {a, b, c};
    char chars[3] = {'a', 'b', 'c'};

    while (1) {
        // Sort counts and chars based on counts in descending order
        for (int i = 0; i < 2; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (counts[i] < counts[j]) {
                    int tempCount = counts[i];
                    counts[i] = counts[j];
                    counts[j] = tempCount;

                    char tempChar = chars[i];
                    chars[i] = chars[j];
                    chars[j] = tempChar;
                }
            }
        }

        bool added = false;
        for (int i = 0; i < 3; i++) {
            if (counts[i] == 0) {
                continue;
            }
            int len = index >= 2 && result[index - 1] == chars[i] && result[index - 2] == chars[i] ? 1 : 2;
            if (counts[i] >= len) {
                for (int j = 0; j < len; j++) {
                    result[index++] = chars[i];
                }
                counts[i] -= len;
                added = true;
                break;
            } else if (counts[i] > 0) {
                result[index++] = chars[i];
                counts[i]--;
                added = true;
                break;
            }
        }
        if (!added) {
            break;
        }
    }
    result[index] = '\0';
    return result;      
}
