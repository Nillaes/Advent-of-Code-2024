#pragma once
#include <iostream>
#include <math.h>
#include <algorithm>

// this get's called with something like "679407" and returns 679407
int NumbersToInt(std::string num){
    int length = num.length();
    int number = 0;
    for (int i = 0; i < length; i++){
        if (num[i] != ' '){ // ignore spaces
        int digit = num[i] - int('0');
        number += digit * pow(10, length - i - 1);
        }
    }

    return number;
}

// Blatantly stolen sorting implementation
void count_sort(int arr[], int pos)
{
    const int n = 1024;

    // we declare a count array and initialize the array by
    // 0
    int count[10] = { 0 };

    // we count the frequency of each distinct digit at
    // given place for every element in the original array
    for (int i = 0; i < n; i++) {
        count[(arr[i] / pos) % 10]++;
    }

    // we perform prefix sum and update the count array
    for (int i = 1; i < 10; i++) {
        count[i] = count[i] + count[i - 1];
    }

    // we store our answer in the ans array
    int ans[n];
    for (int i = n - 1; i >= 0; i--) {
        ans[--count[(arr[i] / pos) % 10]] = arr[i];
    }

    // here we copy the contents of ans array to our
    // original array
    for (int i = 0; i < n; i++) {
        arr[i] = ans[i];
    }
}
// function to implement radix sort (requires array to be 1024 long)
void radix_sort(int arr[])
{
    const int n = 1024;
    // max_element() is a c++ stl function to find the
    // maximum element from an array
    int k = *std::max_element(arr, arr + n);

    for (int pos = 1; (k / pos) > 0; pos *= 10) {
        count_sort(arr, pos);
    }
}

