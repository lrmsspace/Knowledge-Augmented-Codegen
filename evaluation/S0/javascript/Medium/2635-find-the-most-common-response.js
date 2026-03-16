// Source: https://leetcode.com/problems/find-the-most-common-response/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D string array responses where each responses[i] is an array of strings representing survey responses from the ith day.
//
// Return the most common response across all days after removing duplicate responses within each responses[i]. If there is a tie, return the lexicographically smallest response.
//
// Example:
// Input: responses = [["good","ok","good","ok"],["ok","bad","good","ok","ok"],["good"],["bad"]]
//
// Output: "good"
//
// Explanation:
//
//
// 	After removing duplicates within each list, responses = [["good", "ok"], ["ok", "bad", "good"], ["good"], ["bad"]].
// 	"good" appears 3 times, "ok" appears 2 times, and "bad" appears 2 times.
// 	Return "good" because it has the highest frequency.
//
// Constraints:
// 1 <= responses.length <= 1000
// 	1 <= responses[i].length <= 1000
// 	1 <= responses[i][j].length <= 10
// 	responses[i][j] consists of only lowercase English letters
//

/**
 * @param {string[][]} responses
 * @return {string}
 */
var findCommonResponse = function(responses) {
    const frequencyMap = new Map();
    for (const dailyResponses of responses) {
        const uniqueResponses = new Set(dailyResponses);
        for (const response of uniqueResponses) {
            frequencyMap.set(response, (frequencyMap.get(response) || 0) + 1);
        }
    }
    let mostCommonResponse = '';
    let maxFrequency = 0;
    for (const [response, frequency] of frequencyMap.entries()) {
        if (frequency > maxFrequency || (frequency === maxFrequency && response < mostCommonResponse)) {
            mostCommonResponse = response;
            maxFrequency = frequency;
        }
    }
    return mostCommonResponse;  
};
