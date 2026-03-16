// Source: https://leetcode.com/problems/generate-tag-for-video-caption/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string caption representing the caption for a video.
//
// The following actions must be performed in order to generate a valid tag for the video:
//
//
// 	
// 	Combine all words in the string into a single camelCase string prefixed with '#'. A camelCase string is one where the first letter of all words except the first one is capitalized. All characters after the first character in each word must be lowercase.
// 	
// 	
// 	Remove all characters that are not an English letter, except the first '#'.
// 	
// 	
// 	Truncate the result to a maximum of 100 characters.
// 	
//
//
// Return the tag after performing the actions on caption.
//
// Example:
// Input: caption = "Leetcode daily streak achieved"
//
// Output: "#leetcodeDailyStreakAchieved"
//
// Explanation:
//
// The first letter for all words except "leetcode" should be capitalized.
//
// Constraints:
// 1 <= caption.length <= 150
// 	caption consists only of English letters and ' '.
//

char* generateTag(char* caption) {
    char* result = (char*)malloc(102 * sizeof(char));
    int index = 0;
    int isFirstWord = 1;
    int i = 0;

    result[index++] = '#';

    while (caption[i] != '\0' && index < 101) {
        // Skip spaces
        while (caption[i] == ' ') {
            i++;
        }

        if (caption[i] == '\0') {
            break;
        }

        // Process the word
        if (isFirstWord) {
            // First word: all lowercase
            while (caption[i] != ' ' && caption[i] != '\0' && index < 101) {
                if ((caption[i] >= 'A' && caption[i] <= 'Z') || (caption[i] >= 'a' && caption[i] <= 'z')) {
                    result[index++] = (caption[i] >= 'A' && caption[i] <= 'Z') ? caption[i] + 32 : caption[i];
                }
                i++;
            }
            isFirstWord = 0;
        } else {
            // Subsequent words: first letter uppercase, rest lowercase
            if ((caption[i] >= 'A' && caption[i] <= 'Z') || (caption[i] >= 'a' && caption[i] <= 'z')) {
                result[index++] = (caption[i] >= 'a' && caption[i] <= 'z') ? caption[i] - 32 : caption[i];
                i++;
            }
            while (caption[i] != ' ' && caption[i] != '\0' && index < 101) {
                if ((caption[i] >= 'A' && caption[i] <= 'Z') || (caption[i] >= 'a' && caption[i] <= 'z')) {
                    result[index++] = (caption[i] >= 'A' && caption[i] <= 'Z') ? caption[i] + 32 : caption[i];
                }
                i++;
            }
        }
    }

    result[index] = '\0';
    return result;      
}
