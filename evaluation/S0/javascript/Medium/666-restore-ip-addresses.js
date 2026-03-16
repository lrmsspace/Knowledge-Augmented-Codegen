// Source: https://leetcode.com/problems/restore-ip-addresses/   |   Difficulty: Medium
//
// Problem Description:
// A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
//
//
// 	For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
//
//
// Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.
//
// Example:
// Input: s = "25525511135"
// Output: ["255.255.11.135","255.255.111.35"]
//
// Constraints:
// 1 <= s.length <= 20
// 	s consists of digits only.
//

/**
 * @param {string} s
 * @return {string[]}
 */
var restoreIpAddresses = function(s) {
    const result = [];

    const backtrack = (start, path) => {
        if (path.length === 4 && start === s.length) {
            result.push(path.join('.'));
            return;
        }
        if (path.length === 4 || start === s.length) {
            return;
        }
        for (let len = 1; len <= 3; len++) {
            if (start + len > s.length) break;
            const segment = s.substring(start, start + len);
            if ((segment.startsWith('0') && segment.length > 1) || Number(segment) > 255) continue;
            path.push(segment);
            backtrack(start + len, path);
            path.pop();
        }
    };

    backtrack(0, []);
    return result;
};