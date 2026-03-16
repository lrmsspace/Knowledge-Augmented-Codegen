// Source: https://leetcode.com/problems/stamping-the-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings stamp and target. Initially, there is a string s of length target.length with all s[i] == '?'.
//
// In one turn, you can place stamp over s and replace every letter in the s with the corresponding letter from stamp.
//
//
// 	For example, if stamp = "abc" and target = "abcba", then s is "?????" initially. In one turn you can:
//
// 	
// 		place stamp at index 0 of s to obtain "abc??",
// 		place stamp at index 1 of s to obtain "?abc?", or
// 		place stamp at index 2 of s to obtain "??abc".
// 	
// 	Note that stamp must be fully contained in the boundaries of s in order to stamp (i.e., you cannot place stamp at index 3 of s).
//
//
// We want to convert s to target using at most 10 * target.length turns.
//
// Return an array of the index of the left-most letter being stamped at each turn. If we cannot obtain target from s within 10 * target.length turns, return an empty array.
//
// Example:
// Input: stamp = "abc", target = "ababc"
// Output: [0,2]
// Explanation: Initially s = "?????".
// - Place stamp at index 0 to get "abc??".
// - Place stamp at index 2 to get "ababc".
// [1,0,2] would also be accepted as an answer, as well as some other answers.
//
// Constraints:
// 1 <= stamp.length <= target.length <= 1000
// 	stamp and target consist of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* movesToStamp(char* stamp, char* target, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 0;

    int stampLen = strlen(stamp);
    int targetLen = strlen(target);
    if (stampLen == 0 || targetLen == 0 || stampLen > targetLen) return NULL;

    char *s = (char*)malloc((targetLen + 1) * sizeof(char));
    if (!s) return NULL;
    for (int i = 0; i < targetLen; ++i) s[i] = '?';
    s[targetLen] = '\0';

    int maxSteps = 10 * targetLen;
    int *res = (int*)malloc(maxSteps * sizeof(int));
    if (!res) { free(s); return NULL; }
    int resSize = 0;

    int changed;
    do {
        changed = 0;
        for (int i = 0; i <= targetLen - stampLen; ++i) {
            int canStamp = 1;
            for (int j = 0; j < stampLen; ++j) {
                if (s[i + j] != '?' && s[i + j] != stamp[j]) {
                    canStamp = 0;
                    break;
                }
            }
            if (canStamp) {
                int alreadyStamped = 1;
                for (int j = 0; j < stampLen; ++j) {
                    if (s[i + j] != '?') {
                        alreadyStamped = 0;
                        break;
                    }
                }
                if (!alreadyStamped) {
                    for (int j = 0; j < stampLen; ++j) {
                        s[i + j] = stamp[j];
                    }
                    res[resSize++] = i;
                    changed = 1;
                }
            }
        }
    } while (changed && resSize < maxSteps);

    if (strcmp(s, target) != 0) {
        free(s);
        free(res);
        *returnSize = 0;
        return NULL;
    }

    free(s);

    /* reverse the result */
    for (int i = 0; i < resSize / 2; ++i) {
        int temp = res[i];
        res[i] = res[resSize - 1 - i];
        res[resSize - 1 - i] = temp;
    }

    *returnSize = resSize;
    return res;
}
