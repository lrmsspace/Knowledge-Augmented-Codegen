// Source: https://leetcode.com/problems/stickers-to-spell-word/   |   Difficulty: Hard
//
// Problem Description:
// We are given n different types of stickers. Each sticker has a lowercase English word on it.
//
// You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
//
// Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.
//
// Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.
//
// Example:
// Input: stickers = ["with","example","science"], target = "thehat"
// Output: 3
// Explanation:
// We can use 2 "with" stickers, and 1 "example" sticker.
// After cutting and rearrange the letters of those stickers, we can form the target "thehat".
// Also, this is the minimum number of stickers necessary to form the target string.
//
// Constraints:
// n == stickers.length
// 	1 <= n <= 50
// 	1 <= stickers[i].length <= 10
// 	1 <= target.length <= 15
// 	stickers[i] and target consist of lowercase English letters.
//

int minStickers(char** stickers, int stickersSize, char* target) {
    int dpSize = 1 << strlen(target);
    int *dp = (int*)malloc(dpSize * sizeof(int));
    for (int i = 0; i < dpSize; i++) dp[i] = -1;
    dp[0] = 0;

    for (int mask = 0; mask < dpSize; mask++) {
        if (dp[mask] == -1) continue;
        for (int s = 0; s < stickersSize; s++) {
            int nmask = mask;
            int count[26] = {0};
            for (char *p = stickers[s]; *p; p++) count[*p - 'a']++;
            for (int i = 0; target[i]; i++) {
                if ((nmask & (1 << i)) != 0) continue;
                if (count[target[i] - 'a'] > 0) {
                    count[target[i] - 'a']--;
                    nmask |= (1 << i);
                }
            }
            if (dp[nmask] == -1 || dp[nmask] > dp[mask] + 1) {
                dp[nmask] = dp[mask] + 1;
            }
        }
    }

    int result = dp[dpSize - 1];
    free(dp);
    return result;      
}
