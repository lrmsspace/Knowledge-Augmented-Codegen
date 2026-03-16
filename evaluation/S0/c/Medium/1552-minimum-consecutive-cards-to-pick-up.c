// Source: https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cards where cards[i] represents the value of the ith card. A pair of cards are matching if the cards have the same value.
//
// Return the minimum number of consecutive cards you have to pick up to have a pair of matching cards among the picked cards. If it is impossible to have matching cards, return -1.
//
// Example:
// Input: cards = [3,4,2,3,4,7]
// Output: 4
// Explanation: We can pick up the cards [3,4,2,3] which contain a matching pair of cards with value 3. Note that picking up the cards [4,2,3,4] is also optimal.
//
// Constraints:
// 1 <= cards.length <= 105
// 	0 <= cards[i] <= 106
//

int minimumCardPickup(int* cards, int cardsSize) {
    int min_length = cardsSize + 1;
    int last_index[1000001];
    for (int i = 0; i <= 1000000; i++) {
        last_index[i] = -1;
    }

    for (int i = 0; i < cardsSize; i++) {
        int card_value = cards[i];
        if (last_index[card_value] != -1) {
            int current_length = i - last_index[card_value] + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
        }
        last_index[card_value] = i;
    }

    return (min_length == cardsSize + 1) ? -1 : min_length;     
}
