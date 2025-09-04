#include <bits/stdc++.h>
using namespace std;

int n, windowSize;
vector<int> arr;
multiset<int> minHalf;
multiset<int> maxHalf;

void adding(int value)
{
    int currentMedian = *minHalf.rbegin(); // current median which is largest
    if (currentMedian < value)
    {
        maxHalf.insert(value);
        // balance
        if (maxHalf.size() > windowSize / 2)
        {
            minHalf.insert(*maxHalf.begin());
            maxHalf.erase(maxHalf.find(*maxHalf.begin()));
        }
    }
    else
    {
        minHalf.insert(value);
        // balance
        if (minHalf.size() > (windowSize + 1) / 2)
        {
            maxHalf.insert(*minHalf.rbegin());
            minHalf.erase(minHalf.find(*minHalf.rbegin()));
        }
    }
}

void removing(int value)
{
    if (maxHalf.find(value) != maxHalf.end())
        maxHalf.erase(maxHalf.find(value));
    else
        minHalf.erase(minHalf.find(value));

    // lower portion has become empty
    if (minHalf.empty())
    {
        minHalf.insert(*maxHalf.begin());
        maxHalf.erase(maxHalf.find(*maxHalf.begin()));
    }
}

int main()
{
    cin >> n >> windowSize;
    int i = 0;
    while (i < n)
    {
        int input;
        cin >> input;
        arr.push_back(input);
        i++;
    }

    minHalf.insert(arr[0]);
    for (int i = 1; i < windowSize; i++)
        adding(arr[i]);

    cout << *minHalf.rbegin() << " ";

    for (int i = windowSize; i < n; i++)
    {
        if (windowSize == 1)
        {
            adding(arr[i]);
            removing(arr[i - windowSize]);
        }
        else
        {
            removing(arr[i - windowSize]);
            adding(arr[i]);
        }
        cout << *minHalf.rbegin() << " ";
    }
}