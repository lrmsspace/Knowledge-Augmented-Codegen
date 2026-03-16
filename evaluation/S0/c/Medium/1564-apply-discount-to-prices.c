// Source: https://leetcode.com/problems/apply-discount-to-prices/   |   Difficulty: Medium
//
// Problem Description:
// A sentence is a string of single-space separated words where each word can contain digits, lowercase letters, and the dollar sign '$'. A word represents a price if it is a sequence of digits preceded by a dollar sign.
//
//
// 	For example, "$100", "$23", and "$6" represent prices while "100", "$", and "$1e5" do not.
//
//
// You are given a string sentence representing a sentence and an integer discount. For each word representing a price, apply a discount of discount% on the price and update the word in the sentence. All updated prices should be represented with exactly two decimal places.
//
// Return a string representing the modified sentence.
//
// Note that all prices will contain at most 10 digits.
//
// Example:
// Input: sentence = "there are $1 $2 and 5$ candies in the shop", discount = 50
// Output: "there are $0.50 $1.00 and 5$ candies in the shop"
// Explanation: 
// The words which represent prices are "$1" and "$2". 
// - A 50% discount on "$1" yields "$0.50", so "$1" is replaced by "$0.50".
// - A 50% discount on "$2" yields "$1". Since we need to have exactly 2 decimal places after a price, we replace "$2" with "$1.00".
//
// Constraints:
// 1 <= sentence.length <= 105
// 	sentence consists of lowercase English letters, digits, ' ', and '$'.
// 	sentence does not have leading or trailing spaces.
// 	All words in sentence are separated by a single space.
// 	All prices will be positive numbers without leading zeros.
// 	All prices will have at most 10 digits.
// 	0 <= discount <= 100
//

char* discountPrices(char* sentence, int discount) {
    int len = strlen(sentence);
    char* result = (char*)malloc(len * 5 + 1); // Allocate enough space for the result
    int i = 0, j = 0;

    while (i < len) {
        if (sentence[i] == '$' && (i + 1 < len) && isdigit(sentence[i + 1])) {
            int start = i + 1;
            while (start < len && isdigit(sentence[start])) {
                start++;
            }
            if (start == len || sentence[start] == ' ') {
                // Valid price found
                char priceStr[12];
                strncpy(priceStr, sentence + i + 1, start - i - 1);
                priceStr[start - i - 1] = '\0';
                double price = atof(priceStr);
                double discountedPrice = price * (100 - discount) / 100.0;

                // Format the discounted price to two decimal places
                j += sprintf(result + j, "$%.2f", discountedPrice);
                i = start;
                continue;
            }
        }
        // Copy non-price characters
        result[j++] = sentence[i++];
    }
    result[j] = '\0';
    return result;      
}
