#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void RecFibonacciSeries(int n, int a = 0, int b = 1) {
    if (n > 0) {
        cout << a << " ";
        RecFibonacciSeries(n - 1, b, a + b);
    }
}

void fibonacciIterative(int n) {
    if (n <= 0)
        return; // Handle case for non-positive numbers

    int a = 0, b = 1;  // First two Fibonacci numbers
    cout << a << " ";  // Print the first number

    if (n == 1) return; // If only one number is needed

    cout << b << " ";  // Print the second number

    for (int i = 2; i < n; ++i) {
        int result = a + b; // Calculate the next Fibonacci number
        cout << result << " "; // Print the result
        a = b; // Update for next iteration
        b = result; // Update for next iteration
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Fibonacci Series by recursive : ";

    auto start_time = high_resolution_clock::now();

    RecFibonacciSeries(n); // n-2 because 2 numbers are already printed

    auto end_time = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end_time - start_time);
    cout << "\nElapsed Time: " << duration.count() << " microseconds" << endl;
    cout << "Estimated Space Used: " << sizeof(int) * 3 * (n - 2) << " bytes" << endl;

    //-----------------------------------------------------------------------------------------

    cout << "Fibonacci Series by non-recursive method : ";

    start_time = high_resolution_clock::now();
    fibonacciIterative(n);
    end_time = high_resolution_clock::now();

    duration = duration_cast<microseconds>(end_time - start_time);
    cout << "\nElapsed Time: " << duration.count() << " microseconds" << endl;
    cout << "Estimated Space Used: O(1) (constant space)" << endl;

    return 0;
}
