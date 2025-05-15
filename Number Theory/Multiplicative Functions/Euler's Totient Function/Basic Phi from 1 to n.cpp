/*
Time Complexity: O(n x log(n))
*/

vector<int> phi;
void PHI(int n)
{
    phi.resize(n + 1, 0);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
            phi[j] -= phi[i];
}
