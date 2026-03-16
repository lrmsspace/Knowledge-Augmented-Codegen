// Source: https://leetcode.com/problems/can-make-palindrome-from-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and array queries where queries[i] = [lefti, righti, ki]. We may rearrange the substring s[lefti...righti] for each query and then choose up to ki of them to replace with any lowercase English letter.
//
// If the substring is possible to be a palindrome string after the operations above, the result of the query is true. Otherwise, the result is false.
//
// Return a boolean array answer where answer[i] is the result of the ith query queries[i].
//
// Note that each letter is counted individually for replacement, so if, for example s[lefti...righti] = "aaa", and ki = 2, we can only replace two of the letters. Also, note that no query modifies the initial string s.
//
// Example:
// Input: s = "abcda", queries = [[3,3,0],[1,2,0],[0,3,1],[0,3,2],[0,4,1]]
// Output: [true,false,false,true,true]
// Explanation:
// queries[0]: substring = "d", is palidrome.
// queries[1]: substring = "bc", is not palidrome.
// queries[2]: substring = "abcd", is not palidrome after replacing only 1 character.
// queries[3]: substring = "abcd", could be changed to "abba" which is palidrome. Also this can be changed to "baab" first rearrange it "bacd" then replace "cd" with "ab".
// queries[4]: substring = "abcda", could be changed to "abcba" which is palidrome.
//
// Constraints:
// 1 <= s.length, queries.length <= 105
// 	0 <= lefti <= righti < s.length
// 	0 <= ki <= s.length
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var canMakePaliQueries = function(s, queries) {
    const n = s.length;
    const prefix = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        const charCode = s.charCodeAt(i) - 97;
        prefix[i + 1] = prefix[i] ^ (1 << charCode);
    }
    const result = [];
    for (const [left, right, k] of queries) {
        const mask = prefix[right + 1] ^ prefix[left];
        let oddCount = 0;
        for (let i = 0; i < 26; i++) {
            if ((mask >> i) & 1) {
                oddCount++;
            }
        }
        const neededReplacements = Math.floor(oddCount / 2);
        result.push(neededReplacements <= k);
    }
    return result;
        
};
