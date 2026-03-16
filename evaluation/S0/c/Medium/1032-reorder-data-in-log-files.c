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
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** reorderLogFiles(char** logs, int logsSize, int* returnSize) {
    // Custom comparator for sorting logs
    int cmp(const void* a, const void* b) {
        const char* log1 = *(const char**)a;
        const char* log2 = *(const char**)b;

        // Split logs into identifier and content
        const char* id1 = log1;
        while (*log1 != ' ') log1++;
        const char* content1 = log1 + 1;

        const char* id2 = log2;
        while (*log2 != ' ') log2++;
        const char* content2 = log2 + 1;

        // Check if logs are digit-logs or letter-logs
        int isDigit1 = isdigit(*content1);
        int isDigit2 = isdigit(*content2);

        // Both are letter-logs
        if (!isDigit1 && !isDigit2) {
            int cmpContent = strcmp(content1, content2);
            if (cmpContent != 0) return cmpContent;
            return strcmp(id1, id2);
        }

        // One is letter-log and the other is digit-log
        if (!isDigit1 && isDigit2) return -1; // letter-log comes before digit-log
        if (isDigit1 && !isDigit2) return 1;  // digit-log comes after letter-log

        // Both are digit-logs, maintain original order
        return 0;
    }

    // Sort logs using the custom comparator
    qsort(logs, logsSize, sizeof(char*), cmp);

    *returnSize = logsSize;
    return logs;        
}
