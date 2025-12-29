#include <iostream>

using namespace std;

int main() {
    // We use long long because the values in the sequence 
    // can exceed the range of a 32-bit integer (2^31 - 1).
    long long n;
    
    // Read the input value
    if (!(cin >> n)) return 0;

    // Print the starting value
    cout << n;

    // Continue the loop until n reaches 1
    while (n != 1) {
        if (n % 2 == 0) {
            // If even, divide by 2
            n /= 2;
        } else {
            // If odd, multiply by 3 and add 1
            n = 3 * n + 1;
        }
        // Print the next value in the sequence with a space
        cout << " " << n;
    }

    cout << endl;
    return 0;
}