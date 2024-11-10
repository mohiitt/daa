#include <iostream>
#include <algorithm>  // Include this for 'sort'
#include <chrono>     // For measuring execution time
#include <iomanip>    // For formatting output

using namespace std;

struct Item {
    int value;
    int weight;
};

class Solution {
public:
    static bool comp(Item a, Item b) { 
        double r1 = static_cast<double>(a.value) / static_cast<double>(a.weight);  
        double r2 = static_cast<double>(b.value) / static_cast<double>(b.weight);  
        return r1 > r2;  // Sort in descending order of value-to-weight ratio
    }

    double fractionalKnapsack(int W, Item arr[], int n) { 
        sort(arr, arr + n, comp);  // Sort items by value/weight ratio

        int curWeight = 0;          // Current weight of knapsack
        double finalValue = 0.0;    // Total value in the knapsack

        for (int i = 0; i < n; i++) {
            if (curWeight + arr[i].weight <= W) { 
                // Take the full item
                curWeight += arr[i].weight;
                finalValue += arr[i].value;
            } else { 
                // Take only the fraction of the remaining item
                int remain = W - curWeight;
                finalValue += (arr[i].value / static_cast<double>(arr[i].weight)) * static_cast<double>(remain);
                break;  // Knapsack is full, exit the loop
            }
        }
        return finalValue; 
    }
};

int main() {
    int n; // Number of items
    int weight; // Capacity of the knapsack

    // User input for number of items and knapsack capacity
    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the capacity of the knapsack: ";
    cin >> weight;

    Item arr[n]; // Create an array of items

    // User input for values and weights
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight for item " << i + 1 << " (value weight): ";
        cin >> arr[i].value >> arr[i].weight;
    }

    Solution obj; 
    auto start_time = chrono::high_resolution_clock::now();  // Start timer
    double ans = obj.fractionalKnapsack(weight, arr, n);  // Call fractional knapsack function
    auto end_time = chrono::high_resolution_clock::now();  // End timer

    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time); // Calculate elapsed time

    // Output results
    cout << "The maximum value is " << fixed << setprecision(2) << ans << endl; 
    cout << "Elapsed Time: " << duration.count() << " microseconds" << endl;

    return 0; 
}
