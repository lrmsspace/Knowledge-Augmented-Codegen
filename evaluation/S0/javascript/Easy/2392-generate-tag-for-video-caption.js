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

/**
 * @param {string} caption
 * @return {string}
 */
var generateTag = function(caption) {
    const words = caption.split(' ').filter(word => word.length > 0);
    let tag = '#';
    for (let i = 0; i < words.length; i++) {
        if (i === 0) {
            tag += words[i].toLowerCase();
        } else {
            tag += words[i][0].toUpperCase() + words[i].slice(1).toLowerCase();
        }
    }
    tag = tag.replace(/[^a-zA-Z#]/g, '');
    return tag.length > 100 ? tag.slice(0, 100) : tag;
};