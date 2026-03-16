// Source: https://leetcode.com/problems/sort-characters-by-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
//
// Return the sorted string. If there are multiple answers, return any of them.
//
// Example:
// Input: s = "tree"
// Output: "eert"
// Explanation: 'e' appears twice while 'r' and 't' both appear once.
// So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s consists of uppercase and lowercase English letters and digits.
//

char* frequencySort(char* s) {
    int freq[128] = {0};
    for (char* p = s; *p; p++) {
        freq[(int)(*p)]++;
    }

    int n = strlen(s);
    char** buckets = (char**)malloc((n + 1) * sizeof(char*));
    for (int i = 0; i <= n; i++) {
        buckets[i] = (char*)malloc((n + 1) * sizeof(char));
        buckets[i][0] = '\0';
    }

    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            char ch = (char)i;
            for (int j = 0; j < freq[i]; j++) {
                strncat(buckets[freq[i]], &ch, 1);
            }
        }
    }

    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = n; i >= 1; i--) {
        if (buckets[i][0] != '\0') {
            strcat(result, buckets[i]);
        }
    }

    for (int i = 0; i <= n; i++) {
        free(buckets[i]);
    }
    free(buckets);

    return result;      
}
