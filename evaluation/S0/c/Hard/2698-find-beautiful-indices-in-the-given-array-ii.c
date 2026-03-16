// Source: https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s, a string a, a string b, and an integer k.
//
// An index i is beautiful if:
//
//
// 	0 <= i <= s.length - a.length
// 	s[i..(i + a.length - 1)] == a
// 	There exists an index j such that:
// 	
// 		0 <= j <= s.length - b.length
// 		s[j..(j + b.length - 1)] == b
// 		|j - i| <= k
// 	
// 	
//
//
// Return the array that contains beautiful indices in sorted order from smallest to largest.
//
// Example:
// Input: s = "isawsquirrelnearmysquirrelhouseohmy", a = "my", b = "squirrel", k = 15
// Output: [16,33]
// Explanation: There are 2 beautiful indices: [16,33].
// - The index 16 is beautiful as s[16..17] == "my" and there exists an index 4 with s[4..11] == "squirrel" and |16 - 4| <= 15.
// - The index 33 is beautiful as s[33..34] == "my" and there exists an index 18 with s[18..25] == "squirrel" and |33 - 18| <= 15.
// Thus we return [16,33] as the result.
//
// Constraints:
// 1 <= k <= s.length <= 5 * 105
// 	1 <= a.length, b.length <= 5 * 105
// 	s, a, and b contain only lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* beautifulIndices(char* s, char* a, char* b, int k, int* returnSize) {
    if (!s || !a || !b || !returnSize) return NULL;
    int sLen = strlen(s);
    int aLen = strlen(a);
    int bLen = strlen(b);
    if (sLen < aLen || sLen < bLen) {
        *returnSize = 0;
        return NULL;
    }

    int *res = (int*)malloc(sLen * sizeof(int));
    if (!res) {
        *returnSize = 0;
        return NULL;
    }
    int resSize = 0;

    int *bIndices = (int*)malloc(sLen * sizeof(int));
    if (!bIndices) {
        free(res);
        *returnSize = 0;
        return NULL;
    }
    int bCount = 0;

    for (int i = 0; i <= sLen - bLen; ++i) {
        if (strncmp(&s[i], b, bLen) == 0) {
            bIndices[bCount++] = i;
        }
    }

    for (int i = 0; i <= sLen - aLen; ++i) {
        if (strncmp(&s[i], a, aLen) == 0) {
            for (int j = 0; j < bCount; ++j) {
                if (abs(bIndices[j] - i) <= k) {
                    res[resSize++] = i;
                    break;
                }
            }
        }
    }

    free(bIndices);
    *returnSize = resSize;
    return res;     
}
