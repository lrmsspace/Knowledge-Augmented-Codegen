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

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        auto isDigitLog = [](const string& log) {
            int pos = log.find(' ');
            return isdigit(log[pos + 1]);
        };

        auto logComparator = [](const string& log1, const string& log2) {
            int pos1 = log1.find(' ');
            int pos2 = log2.find(' ');

            string id1 = log1.substr(0, pos1);
            string content1 = log1.substr(pos1 + 1);
            string id2 = log2.substr(0, pos2);
            string content2 = log2.substr(pos2 + 1);

            if (content1 != content2) {
                return content1 < content2;
            }
            return id1 < id2;
        };

        vector<string> letterLogs;
        vector<string> digitLogs;

        for (const string& log : logs) {
            if (isDigitLog(log)) {
                digitLogs.push_back(log);
            } else {
                letterLogs.push_back(log);
            }
        }

        sort(letterLogs.begin(), letterLogs.end(), logComparator);

        letterLogs.insert(letterLogs.end(), digitLogs.begin(), digitLogs.end());
        return letterLogs;          
    }
};
