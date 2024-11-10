#include <iostream>
#include <algorithm>

using namespace std;

void knapsack(int W, int weight[], int value[], int n) {
    // Create a 2D array to store the maximum value at each n and W
    int dp[n + 1][W + 1];

    // Build the dp array
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case
            } else if (weight[i - 1] <= w) {
                // Max of including or excluding the current item
                dp[i][w] = max(value[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w]; // Exclude the current item
            }
        }
    }

    // The maximum value obtainable
    int maxProfit = dp[n][W];
    cout << "The maximum value obtainable: " << maxProfit << endl;

    // To find which items are included
    cout << "Items included in the knapsack:\n";
    int w = W;
    for (int i = n; i > 0 && maxProfit > 0; i--) {
        // If the item is included
        if (maxProfit != dp[i - 1][w]) {
            cout << "Item " << i << " (Weight: " << weight[i - 1] << ", Value: " << value[i - 1] << ")\n";
            // Since this weight is included, subtract it from the total weight and value
            maxProfit -= value[i - 1];
            w -= weight[i - 1];
        }
    }
}

int main() {
    int n; // Number of items
    int W; // Capacity of the knapsack

    // User input for number of items and knapsack capacity
    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    int weight[n]; // Create an array for weights
    int value[n];  // Create an array for values

    // User input for weights and values
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and value for item " << i + 1 << " (weight value): ";
        cin >> weight[i] >> value[i];
    }

    knapsack(W, weight, value, n); // Solve using dynamic programming

    return 0;
}
