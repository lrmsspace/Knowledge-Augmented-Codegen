// Source: https://leetcode.com/problems/length-of-the-longest-valid-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an array of strings forbidden.
//
// A string is called valid if none of its substrings are present in forbidden.
//
// Return the length of the longest valid substring of the string word.
//
// A substring is a contiguous sequence of characters in a string, possibly empty.
//
// Example:
// Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
// Output: 4
// Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
// It can be shown that all other substrings contain either "aaa" or "cb" as a substring.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= forbidden.length <= 105
// 	1 <= forbidden[i].length <= 10
// 	forbidden[i] consists only of lowercase English letters.
//

int longestValidSubstring(char* word, char** forbidden, int forbiddenSize) {
    /* build forbidden set using hash map */
    enum { BUCKETS = 10007 };
    struct Entry { char *str; struct Entry* next; };
    struct Entry **buckets = (struct Entry**)calloc(BUCKETS, sizeof(struct Entry*));
    if (!buckets) return 0;

    for (int i = 0; i < forbiddenSize; ++i) {
        unsigned long h = 5381;
        char *s = forbidden[i];
        while (*s) h = ((h << 5) + h) + (unsigned char)(*s++);
        h %= BUCKETS;

        struct Entry *ne = (struct Entry*)malloc(sizeof(struct Entry));
        if (!ne) continue; /* allocation failure, skip */
        ne->str = forbidden[i];
        ne->next = buckets[h];
        buckets[h] = ne;
    }

    int maxLen = 0;
    int n = strlen(word);
    for (int i = 0; i < n; ++i) {
        for (int len = 1; len <= 10 && i + len <= n; ++len) {
            unsigned long h = 5381;
            for (int k = 0; k < len; ++k)
                h = ((h << 5) + h) + (unsigned char)(word[i + k]);
            h %= BUCKETS;

            struct Entry *e = buckets[h];
            int found = 0;
            while (e) {
                if (strlen(e->str) == len && strncmp(e->str, word + i, len) == 0) {
                    found = 1; break;
                }
                e = e->next;
            }
            if (found) {
                maxLen = (maxLen > (len - 1)) ? maxLen : (len - 1);
                break;
            }
            if (len == 10 || i + len == n)
                maxLen = (maxLen > len) ? maxLen : len;
        }
    }

    /* free hash map entries */
    for (int i = 0; i < BUCKETS; ++i) {
        struct Entry *e = buckets[i];
        while (e) { struct Entry *t = e->next; free(e); e = t; }
    }
    free(buckets);

    return maxLen;   
}
