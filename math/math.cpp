// math

vector <Modular> fact, ifact;

void math(int n){
    fact.resize(n + 1, 1), ifact.resize(n + 1, 1);
    for (int i = 1; i <= n; ++ i) fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n - 1; i >= 0; -- i) ifact[i] = ifact[i + 1] * (i + 1);
}

Modular C(int k, int n){ // choose k in n
    return fact[n] * ifact[k] * ifact[n - k];
}

vector <Modular> fib, cat;

void specNum(int n){
    fib.resize(n + 1, 0); fib[1] = 1;
    for (int i = 2; i <= n; ++ i) fib[i] = fib[i - 1] + fib[i - 2];

    cat.resize(n + 1, 0); // math must size >= 2 * n
    for (int i = 0; i <= n; ++ i) {
        Modular k = i + 1;
        cat[i] = k.inv() * C(i, 2 * i);
    }
}
