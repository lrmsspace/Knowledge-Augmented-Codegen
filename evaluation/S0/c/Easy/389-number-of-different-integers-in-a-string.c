// Source: https://leetcode.com/problems/number-of-different-integers-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word that consists of digits and lowercase English letters.
//
// You will replace every non-digit character with a space. For example, "a123bc34d8ef34" will become " 123  34 8  34". Notice that you are left with some integers that are separated by at least one space: "123", "34", "8", and "34".
//
// Return the number of different integers after performing the replacement operations on word.
//
// Two integers are considered different if their decimal representations without any leading zeros are different.
//
// Example:
// Input: word = "a123bc34d8ef34"
// Output: 3
// Explanation: The three different integers are "123", "34", and "8". Notice that "34" is only counted once.
//
// Constraints:
// 1 <= word.length <= 1000
// 	word consists of digits and lowercase English letters.
//

int numDifferentIntegers(char* word) {
    char buffer[1001];
    int buf_index = 0;
    char* p = word;
    char* end;
    int count = 0;

    // Using a simple array to store unique integers as strings
    char unique_numbers[1000][1001];
    int unique_count = 0;

    while (*p) {
        if ((*p >= '0' && *p <= '9')) {
            buffer[buf_index++] = *p;
        } else {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                // Remove leading zeros
                char* num_start = buffer;
                while (*num_start == '0' && *(num_start + 1) != '\0') {
                    num_start++;
                }
                // Check if this number is already in unique_numbers
                int found = 0;
                for (int i = 0; i < unique_count; i++) {
                    if (strcmp(unique_numbers[i], num_start) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(unique_numbers[unique_count++], num_start);
                }
                buf_index = 0; // Reset buffer index
            }
        }
        p++;
    }

    // Check for any remaining number in the buffer
    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        char* num_start = buffer;
        while (*num_start == '0' && *(num_start + 1) != '\0') {
            num_start++;
        }
        int found = 0;
        for (int i = 0; i < unique_count; i++) {
            if (strcmp(unique_numbers[i], num_start) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(unique_numbers[unique_count++], num_start);
        }
    }

    return unique_count;        
}
