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

class Solution {
public:
    string discountPrices(string sentence, int discount) {
        istringstream iss(sentence);
        ostringstream oss;
        string word;
        bool first = true;
        while (iss >> word) {
            if (word[0] == '$' && word.size() > 1 && all_of(word.begin() + 1, word.end(), ::isdigit)) {
                // Valid price
                long long price = stoll(word.substr(1));
                double discountedPrice = price * (100 - discount) / 100.0;
                if (!first) oss << " ";
                oss << "$" << fixed << setprecision(2) << discountedPrice;
            } else {
                // Not a valid price
                if (!first) oss << " ";
                oss << word;
            }
            first = false;
        }
        return oss.str();           
    }
};
