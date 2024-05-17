#pragma once

template <class T>
struct pair {
    T first;
    T second;
};

template <class T>
pair<T> minmax(T a, T b) {
    T min = a < b ? a : b;
    T max = a > b ? a : b;
    return {min, max};
}

template <class T>
T min(T a, T b) {
    return a < b ? a : b;
}

template <class T>
T max(T a, T b) {
    return a > b ? a : b;
}
