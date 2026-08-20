// Vec

template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
    static_assert(D >= 1, "Dimension must be positive");
    template <typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};

template <typename T>
struct Vec<1, T> : public vector<T> {
    Vec(int n = 0, T val = T()) : std::vector<T>(n, val) {}
};

// support vector

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define fd(sr, x) (lower_bound(sr.begin(), sr.end(), x) - sr.begin())
#define uq(sr) (sr).erase(unique(all((sr))), (sr).end())
#define szv(v) (int((v).size()))
