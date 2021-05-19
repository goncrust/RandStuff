#include <iostream>

int times = 0;

int staircase_count(int N)
{
    std::cout << N;
    times++;
    if (N == 0 || N == 1)
    {
        return 1;
    }

    return staircase_count(N - 1) + staircase_count(N - 2);
}

int main()
{
    int result = staircase_count(40);
    std::cout << std::endl
              << result << std::endl
              << times;
}