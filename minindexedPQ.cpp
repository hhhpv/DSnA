#include <bits/stdc++.h>
using namespace std;
class MinIndexedPQ
{
    int n = 0, sz = 0, *pm, *im, *values;

public:
    MinIndexedPQ(int n)
    {
        if (n <= 0)
            cerr << "Queue size less than zero";
        pm = new int[n + 1];
        im = new int[n + 1];
        values = new int[n + 1];
        sz = 0;
    }
    void swap(int i, int j)
    {
        pm[im[i]] = j;
        pm[im[j]] = i;
        int tmp = im[i];
        im[i] = im[j];
        im[j] = tmp;
    }
    void swim(int i)
    {
        for (int j = (i - 1) / 2; (i > 0) && (values[im[i]] < values[im[j]]);)
        {
            swap(i, j);
            i = j;
            j = (i - 1) / 2;
        }
    }
    void sink(int i)
    {
        while (true)
        {
            int left = (2 * i) + 1;
            int right = (2 * i) + 2;
            int smallest = left;
            if (right < sz && (values[im[right]] < values[im[left]]))
            {
                smallest = right;
            }
            if (left >= sz || (values[im[i]] <= values[im[smallest]]))
            {
                break;
            }
            swap(smallest, i);
            i = smallest;
        }
    }
    void insert(int ki, int value)
    {
        values[ki] = value;
        pm[ki] = sz;
        im[sz] = ki;
        swim(sz++);
    }
    void remove(int ki)
    {
        if (pm[ki] == -1)
        {
            cerr << "Key not present";
            return;
        }
        int i = pm[ki];
        swap(i, --sz);
        sink(i);
        swim(i);
        values[ki] = NULL;
        pm[ki] = -1;
        im[sz] = -1;
    }
    void update(int ki, int value)
    {
        int i = pm[ki];
        values[ki] = value;
        sink(i);
        swim(i);
    }
    void decreaseKey(int ki, int value)
    {
        if (value < values[ki])
        {
            values[ki] = value;
            swim(pm[ki]);
        }
    }
    void increaseKey(int ki, int value)
    {
        if (values[ki] < value)
        {
            values[ki] = value;
            sink(pm[ki]);
        }
    }
    int top()
    {
        return values[im[0]];
    }
    void pop()
    {
        remove(im[0]);
    }
    int size()
    {
        return sz;
    }
};
int main()
{
    MinIndexedPQ pq(6);
    cout << "\n\n\n";
    pq.insert(1, 10);
    pq.insert(2, -20);
    pq.update(1, -30);
    pq.insert(3, 40);
    cout << "\nNew Size" << pq.size();
    cout << "\n"
         << pq.top() << " Expected -30";
    cout << "\nPopping";
    pq.pop();
    cout << "\nNew Size" << pq.size();
    cout << "\nTop " << pq.top() << " Expected -20";
    pq.pop();
    cout << "\nPopping";
    cout << "\n"
         << pq.top() << " top expected 40";
    pq.pop();
    cout << "\nSize after final pop() " << pq.size() << "\n";

    MinIndexedPQ k(5);
    k.insert(1, 20);
    k.insert(2, 25);
    cout << "\nAfter increasing to a lower value than the present value";
    k.increaseKey(1, 19);
    cout << "\nTop " << k.top() << " expected 20";
    k.decreaseKey(2, -25);
    cout << "\nTop" << k.top() << " expected -25";
    k.decreaseKey(2, -19);
    cout << "\nAfter Decreasing";
    cout << "\nTop" << k.top() << " expected -25";
    k.pop();
    cout << "\nafter popping"
         << "\n";
    cout << "\ntop " << k.top() << "Expected 20";
    k.pop();
    cout << "\nFinal Size after popping all elements " << k.size();
    return 0;
}