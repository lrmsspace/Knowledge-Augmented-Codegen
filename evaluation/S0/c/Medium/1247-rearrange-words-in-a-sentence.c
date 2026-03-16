// Source: https://leetcode.com/problems/rearrange-words-in-a-sentence/   |   Difficulty: Medium
//
// Problem Description:
// Given a sentence text (A sentence is a string of space-separated words) in the following format:
//
//
// 	First letter is in upper case.
// 	Each word in text are separated by a single space.
//
//
// Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.
//
// Return the new text following the format shown above.
//
// Example:
// Input: text = "Leetcode is cool"
// Output: "Is cool leetcode"
// Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
// Output is ordered by length and the new first word starts with capital letter.
//
// Constraints:
// text begins with a capital letter and then contains lowercase letters and single space between words.
// 	1 <= text.length <= 10^5
//

char* arrangeWords(char* text) {
    int n = strlen(text);
    char** words = (char**)malloc(n * sizeof(char*));
    int* lengths = (int*)malloc(n * sizeof(int));
    int word_count = 0;

    // Split the text into words
    char* token = strtok(text, " ");
    while (token != NULL) {
        words[word_count] = token;
        lengths[word_count] = strlen(token);
        word_count++;
        token = strtok(NULL, " ");
    }

    // Sort words by length using a simple bubble sort for demonstration
    for (int i = 0; i < word_count - 1; i++) {
        for (int j = 0; j < word_count - i - 1; j++) {
            if (lengths[j] > lengths[j + 1]) {
                // Swap lengths
                int temp_len = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = temp_len;

                // Swap words
                char* temp_word = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp_word;
            }
        }
    }

    // Construct the result string
    char* result = (char*)malloc(n * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < word_count; i++) {
        if (i > 0) {
            strcat(result, " ");
        }
        strcat(result, words[i]);
    }

    // Capitalize the first letter and lowercase the rest
    result[0] = toupper(result[0]);
    for (int i = 1; result[i] != '\0'; i++) {
        result[i] = tolower(result[i]);
    }

    free(words);
    free(lengths);
    return result;      
}
