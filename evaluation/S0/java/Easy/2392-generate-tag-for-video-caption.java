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

class Solution {
    public String generateTag(String caption) {
        StringBuilder tag = new StringBuilder("#");
        String[] words = caption.split(" ");

        for (int i = 0; i < words.length; i++) {
            if (words[i].isEmpty()) continue; // Skip empty words resulting from multiple spaces
            String word = words[i].replaceAll("[^a-zA-Z]", ""); // Remove non-letter characters
            if (word.isEmpty()) continue; // Skip if the word is empty after removing non-letters

            if (i == 0) {
                tag.append(word.toLowerCase());
            } else {
                tag.append(Character.toUpperCase(word.charAt(0)));
                tag.append(word.substring(1).toLowerCase());
            }
        }

        // Truncate to a maximum of 100 characters
        if (tag.length() > 100) {
            return tag.substring(0, 100);
        }

        return tag.toString();          
    }
}
