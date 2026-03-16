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

/**
 * @param {string[]} stickers
 * @param {string} target
 * @return {number}
 */
var minStickers = function(stickers, target) {
    


    let n = stickers.length;
    let stickerCounts = new Array(n).fill(0).map(() => new Array(26).fill(0));
    for (let i = 0; i < n; i++) {
        for (let char of stickers[i]) {
            stickerCounts[i][char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
        }
    }

    let targetCount = new Array(26).fill(0);
    for (let char of target) {
        targetCount[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    let memo = new Map();
    function dfs(targetCount) {
        let key = targetCount.join(',');
        if (memo.has(key)) {
            return memo.get(key);
        }
        let minStickersNeeded = Infinity;
        for (let i = 0; i < n; i++) {
            if (stickerCounts[i][targetCount.findIndex(count => count > 0)] === 0) {
                continue;
            }
            let newTargetCount = targetCount.slice();
            for (let j = 0; j < 26; j++) {
                newTargetCount[j] = Math.max(0, newTargetCount[j] - stickerCounts[i][j]);
            }
            minStickersNeeded = Math.min(minStickersNeeded, 1 + dfs(newTargetCount));
        }
        memo.set(key, minStickersNeeded);
        return minStickersNeeded;
    }
    let result = dfs(targetCount);
    return result === Infinity ? -1 : result;   
            
};
