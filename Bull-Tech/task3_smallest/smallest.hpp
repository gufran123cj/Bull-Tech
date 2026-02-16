#ifndef SMALLEST_HPP
#define SMALLEST_HPP

#if defined(__GNUC__) || defined(__clang__)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define PTR_RESTRICT __restrict__
#else
#define UNLIKELY(x) (x)
#define PTR_RESTRICT
#endif

template <typename T>
inline int smallest(const T* PTR_RESTRICT start, int length) {
    if (UNLIKELY(!start || length <= 0)) return -1;
    int idx = 0;
    for (int i = 1; i < length; ++i)
        idx = (start[i] < start[idx]) ? i : idx;
    return idx;
}

#undef UNLIKELY
#undef PTR_RESTRICT

#endif
