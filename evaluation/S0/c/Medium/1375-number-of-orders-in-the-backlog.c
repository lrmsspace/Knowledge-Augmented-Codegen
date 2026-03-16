// Source: https://leetcode.com/problems/number-of-orders-in-the-backlog/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array orders, where each orders[i] = [pricei, amounti, orderTypei] denotes that amounti orders have been placed of type orderTypei at the price pricei. The orderTypei is:
//
//
// 	0 if it is a batch of buy orders, or
// 	1 if it is a batch of sell orders.
//
//
// Note that orders[i] represents a batch of amounti independent orders with the same price and order type. All orders represented by orders[i] will be placed before all orders represented by orders[i+1] for all valid i.
//
// There is a backlog that consists of orders that have not been executed. The backlog is initially empty. When an order is placed, the following happens:
//
//
// 	If the order is a buy order, you look at the sell order with the smallest price in the backlog. If that sell order's price is smaller than or equal to the current buy order's price, they will match and be executed, and that sell order will be removed from the backlog. Else, the buy order is added to the backlog.
// 	Vice versa, if the order is a sell order, you look at the buy order with the largest price in the backlog. If that buy order's price is larger than or equal to the current sell order's price, they will match and be executed, and that buy order will be removed from the backlog. Else, the sell order is added to the backlog.
//
//
// Return the total amount of orders in the backlog after placing all the orders from the input. Since this number can be large, return it modulo 109 + 7.
//
// Example:
// Input: orders = [[10,5,0],[15,2,1],[25,1,1],[30,4,0]]
// Output: 6
// Explanation: Here is what happens with the orders:
// - 5 orders of type buy with price 10 are placed. There are no sell orders, so the 5 orders are added to the backlog.
// - 2 orders of type sell with price 15 are placed. There are no buy orders with prices larger than or equal to 15, so the 2 orders are added to the backlog.
// - 1 order of type sell with price 25 is placed. There are no buy orders with prices larger than or equal to 25 in the backlog, so this order is added to the backlog.
// - 4 orders of type buy with price 30 are placed. The first 2 orders are matched with the 2 sell orders of the least price, which is 15 and these 2 sell orders are removed from the backlog. The 3rd order is matched with the sell order of the least price, which is 25 and this sell order is removed from the backlog. Then, there are no more sell orders in the backlog, so the 4th order is added to the backlog.
// Finally, the backlog has 5 buy orders with price 10, and 1 buy order with price 30. So the total number of orders in the backlog is 6.
//
// Constraints:
// 1 <= orders.length <= 105
// 	orders[i].length == 3
// 	1 <= pricei, amounti <= 109
// 	orderTypei is either 0 or 1.
//



int getNumberOfBacklogOrders(int** orders, int ordersSize, int* ordersColSize){
    #define MOD 1000000007

    typedef struct {
        long price;
        long amount;
    } Order;

    typedef struct {
        Order* data;
        int size;
        int capacity;
        int (*cmp)(Order*, Order*);
    } Heap;

    Heap* createHeap(int capacity, int (*cmp)(Order*, Order*)) {
        Heap* heap = (Heap*)malloc(sizeof(Heap));
        heap->data = (Order*)malloc(sizeof(Order) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        heap->cmp = cmp;
        return heap;
    }

    void swap(Order* a, Order* b) {
        Order temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(Heap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->cmp(&heap->data[index], &heap->data[parent]) > 0) {
                swap(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(Heap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (heap->cmp(&heap->data[left], &heap->data[largest]) > 0) {
                largest = left;
            }
            if (right < heap->size && heap->cmp(&heap->data[right], &heap->data[largest]) > 0) {
                largest = right;
            }
            if (largest != index) {
                swap(&heap->data[index], &heap->data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    void push(Heap* heap, long price, long amount) {
        if (heap->size == heap->capacity) return; // Heap is full
        heap->data[heap->size].price = price;
        heap->data[heap->size].amount = amount;
        heapifyUp(heap, heap->size);
        heap->size++;
    }
    Order pop(Heap* heap) {
        Order ret = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return ret;
    }
    int buyCmp(Order* a, Order* b) {
        return (a->price > b->price) ? 1 : ((a->price < b->price) ? -1 : 0);
    }
    int sellCmp(Order* a, Order* b) {
        return (a->price < b->price) ? 1 : ((a->price > b->price) ? -1 : 0);
    }
    Heap* buyHeap = createHeap(ordersSize, buyCmp);
    Heap* sellHeap = createHeap(ordersSize, sellCmp);
    for (int i = 0; i < ordersSize; i++) {
        long price = orders[i][0];
        long amount = orders[i][1];
        int orderType = orders[i][2];

        if (orderType == 0) { // Buy order
            while (amount > 0 && sellHeap->size > 0 && sellHeap->data[0].price <= price) {
                Order sellOrder = pop(sellHeap);
                if (sellOrder.amount > amount) {
                    sellOrder.amount -= amount;
                    push(sellHeap, sellOrder.price, sellOrder.amount);
                    amount = 0;
                } else {
                    amount -= sellOrder.amount;
                }
            }
            if (amount > 0) {
                push(buyHeap, price, amount);
            }
        } else { // Sell order
            while (amount > 0 && buyHeap->size > 0 && buyHeap->data[0].price >= price) {
                Order buyOrder = pop(buyHeap);
                if (buyOrder.amount > amount) {
                    buyOrder.amount -= amount;
                    push(buyHeap, buyOrder.price, buyOrder.amount);
                    amount = 0;
                } else {
                    amount -= buyOrder.amount;
                }
            }
            if (amount > 0) {
                push(sellHeap, price, amount);
            }
        }
    }
    long totalOrders = 0;
    for (int i = 0; i < buyHeap->size; i++) {
        totalOrders = (totalOrders + buyHeap->data[i].amount) % MOD;
    }
    for (int i = 0; i < sellHeap->size; i++) {
        totalOrders = (totalOrders + sellHeap->data[i].amount) % MOD;
    }
    // Free heaps
    free(buyHeap->data);
    free(buyHeap);
    free(sellHeap->data);
    free(sellHeap);
    return (int)totalOrders;
}
