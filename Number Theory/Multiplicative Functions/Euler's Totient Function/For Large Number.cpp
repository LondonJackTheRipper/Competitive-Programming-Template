/*
For n around 10^14
The time complexity is log(n)
*/

vector<int> isprime, primes;
void Sieve(int n)
{
    isprime.resize(n + 1, 1);
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i * i <= n; i++)
        if (isprime[i])
            for (int j = i * i; j <= n; j += i)
                isprime[j] = 0;
    for (int i = 2; i <= n; i++)
        if (isprime[i])
            primes.push_back(i);
}

ll phi(ll n)
{
    ll res = n;
    for (int i = 0; i < (int)primes.size() && 1ll * primes[i] * primes[i] <= n; i++)
    {
        int p = primes[i];
        if (n % p == 0)
        {
            res -= res / p;
            while (n % p == 0)
                n /= p;
        }
    }
    if (n != 1)
        res -= res / n;
    return res;
}
