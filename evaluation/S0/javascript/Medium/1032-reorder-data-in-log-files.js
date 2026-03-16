// Source: https://leetcode.com/problems/reorder-data-in-log-files/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of logs. Each log is a space-delimited string of words, where the first word is the identifier.
//
// There are two types of logs:
//
//
// 	Letter-logs: All words (except the identifier) consist of lowercase English letters.
// 	Digit-logs: All words (except the identifier) consist of digits.
//
//
// Reorder these logs so that:
//
//
// 	The letter-logs come before all digit-logs.
// 	The letter-logs are sorted lexicographically by their contents. If their contents are the same, then sort them lexicographically by their identifiers.
// 	The digit-logs maintain their relative ordering.
//
//
// Return the final order of the logs.
//
// Example:
// Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
// Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
// Explanation:
// The letter-log contents are all different, so their ordering is "art can", "art zero", "own kit dig".
// The digit-logs have a relative order of "dig1 8 1 5 1", "dig2 3 6".
//
// Constraints:
// 1 <= logs.length <= 100
// 	3 <= logs[i].length <= 100
// 	All the tokens of logs[i] are separated by a single space.
// 	logs[i] is guaranteed to have an identifier and at least one word after the identifier.
//

/**
 * @param {string[]} logs
 * @return {string[]}
 */
var reorderLogFiles = function(logs) {
    const isDigitLog = (log) => {
        const firstSpaceIndex = log.indexOf(' ');
        const firstCharAfterIdentifier = log[firstSpaceIndex + 1];
        return /\d/.test(firstCharAfterIdentifier);
    };

    const letterLogs = [];
    const digitLogs = [];   
    for (const log of logs) {
        if (isDigitLog(log)) {
            digitLogs.push(log);
        } else {
            letterLogs.push(log);
        }
    }

    letterLogs.sort((logA, logB) => {
        const splitA = logA.indexOf(' ');
        const splitB = logB.indexOf(' ');
        const idA = logA.slice(0, splitA);
        const idB = logB.slice(0, splitB);
        const contentA = logA.slice(splitA + 1);
        const contentB = logB.slice(splitB + 1);
        if (contentA === contentB) {
            return idA.localeCompare(idB);
        }
        return contentA.localeCompare(contentB);
    });

    return [...letterLogs, ...digitLogs];
    
};
