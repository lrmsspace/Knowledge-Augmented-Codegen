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

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = stickers.size();
        vector<vector<int>> stickerCounts(n, vector<int>(26, 0));
        for (int i = 0; i < n; i++) {
            for (char c : stickers[i]) {
                stickerCounts[i][c - 'a']++;
            }
        }
        
        unordered_map<string, int> memo;
        function<int(string)> dfs = [&](string t) {
            if (t.empty()) return 0;
            if (memo.count(t)) return memo[t];
            
            vector<int> targetCount(26, 0);
            for (char c : t) {
                targetCount[c - 'a']++;
            }
            
            int res = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (stickerCounts[i][t[0] - 'a'] == 0) continue; // optimization
                
                string newTarget;
                for (int j = 0; j < 26; j++) {
                    if (targetCount[j] > stickerCounts[i][j]) {
                        newTarget += string(targetCount[j] - stickerCounts[i][j], 'a' + j);
                    }
                }
                
                int tmp = dfs(newTarget);
                if (tmp != -1) {
                    res = min(res, 1 + tmp);
                }
            }
            
            memo[t] = (res == INT_MAX) ? -1 : res;
            return memo[t];
        };
        
        return dfs(target);         
    }
};
