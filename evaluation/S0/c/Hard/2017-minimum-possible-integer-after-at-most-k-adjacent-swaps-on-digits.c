// Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
//
// Return the minimum integer you can obtain also as a string.
//
// Example:
// Input: num = "4321", k = 4
// Output: "1342"
// Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
//
// Constraints:
// 1 <= num.length <= 3 * 104
// 	num consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

char* minInteger(char* num, int k) {
    int n = strlen(num);
    int *pos[10];
    int posSize[10];
    int posCap[10];
    for (int d = 0; d < 10; d++) {
        pos[d] = (int*)malloc(n * sizeof(int));
        posSize[d] = 0;
        posCap[d] = n;
    }
    for (int i = 0; i < n; i++) {
        int d = num[i] - '0';
        pos[d][posSize[d]++] = i;
    }

    int *bit = (int*)calloc(n + 1, sizeof(int));
    int bitUpdate(int idx, int delta) {
        for (idx++; idx <= n; idx += idx & -idx) bit[idx] += delta;
        return 0;
    }
    int bitQuery(int idx) {
        int sum = 0;
        for (idx++; idx > 0; idx -= idx & -idx) sum += bit[idx];
        return sum;
    }

    char *result = (char*)malloc((n + 1) * sizeof(char));
    int resIdx = 0;
    for (int i = 0; i < n; i++) {
        for (int d = 0; d < 10; d++) {
            if (posSize[d] == 0) continue;
            int origIdx = pos[d][0];
            int movedLeft = bitQuery(origIdx - 1);
            int currIdx = origIdx - movedLeft;
            int cost = currIdx - i;
            if (cost <= k) {
                k -= cost;
                result[resIdx++] = (char)(d + '0');
                bitUpdate(origIdx, 1);
                memmove(pos[d], pos[d] + 1, (posSize[d] - 1) * sizeof(int));
                posSize[d]--;
                break;
            }
        }
    }
    result[resIdx] = '\0';

    for (int d = 0; d < 10; d++) {
        free(pos[d]);
    }
    free(bit);
    return result;      
}
