// Source: https://leetcode.com/problems/capitalize-the-title/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string title consisting of one or more words separated by a single space, where each word consists of English letters. Capitalize the string by changing the capitalization of each word such that:
//
//
// 	If the length of the word is 1 or 2 letters, change all letters to lowercase.
// 	Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
//
//
// Return the capitalized title.
//
// Example:
// Input: title = "capiTalIze tHe titLe"
// Output: "Capitalize The Title"
// Explanation:
// Since all the words have a length of at least 3, the first letter of each word is uppercase, and the remaining letters are lowercase.
//
// Constraints:
// 1 <= title.length <= 100
// 	title consists of words separated by a single space without any leading or trailing spaces.
// 	Each word consists of uppercase and lowercase English letters and is non-empty.
//

char* capitalizeTitle(char* title) {
    char* p = title;
    int start = 0, end = 0;
    while (*p) {
        if (*p == ' ' || *(p + 1) == '\0') {
            end = ( *(p + 1) == '\0' ) ? (p - title) : (p - title - 1);
            int len = end - start + 1;
            if (len <= 2) {
                for (int i = start; i <= end; i++) {
                    if (title[i] >= 'A' && title[i] <= 'Z') {
                        title[i] += 32;
                    }
                }
            } else {
                if (title[start] >= 'a' && title[start] <= 'z') {
                    title[start] -= 32;
                }
                for (int i = start + 1; i <= end; i++) {
                    if (title[i] >= 'A' && title[i] <= 'Z') {
                        title[i] += 32;
                    }
                }
            }
            start = end + 2;
        }
        p++;
    }
    return title;       
}
