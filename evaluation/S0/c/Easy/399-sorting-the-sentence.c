// Source: https://leetcode.com/problems/sorting-the-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of lowercase and uppercase English letters.
//
// A sentence can be shuffled by appending the 1-indexed word position to each word then rearranging the words in the sentence.
//
//
// 	For example, the sentence "This is a sentence" can be shuffled as "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".
//
//
// Given a shuffled sentence s containing no more than 9 words, reconstruct and return the original sentence.
//
// Example:
// Input: s = "is2 sentence4 This1 a3"
// Output: "This is a sentence"
// Explanation: Sort the words in s to their original positions "This1 is2 a3 sentence4", then remove the numbers.
//
// Constraints:
// 2 <= s.length <= 200
// 	s consists of lowercase and uppercase English letters, spaces, and digits from 1 to 9.
// 	The number of words in s is between 1 and 9.
// 	The words in s are separated by a single space.
// 	s contains no leading or trailing spaces.
//



char * sortSentence(char * s){
    char *words[9] = {0};
    char *token = strtok(s, " ");
    while (token) {
        int len = strlen(token);
        int pos = token[len - 1] - '1';
        token[len - 1] = '\0';  // Remove the position digit
        words[pos] = token;
        token = strtok(NULL, " ");
    }

    // Calculate the total length needed for the result string
    int total_len = 0;
    for (int i = 0; i < 9; i++) {
        if (words[i]) {
            total_len += strlen(words[i]) + 1; // +1 for space or null terminator
        }
    }

    char *result = (char *)malloc(total_len);
    result[0] = '\0'; // Initialize as empty string

    for (int i = 0; i < 9; i++) {
        if (words[i]) {
            strcat(result, words[i]);
            strcat(result, " ");
        }
    }

    // Remove the trailing space
    if (total_len > 0) {
        result[total_len - 2] = '\0'; // Replace last space with null terminator
    }

    return result;
}
