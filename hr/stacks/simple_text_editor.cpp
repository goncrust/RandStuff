#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int main()
{
    int Q;
    string Q_s;
    getline(cin, Q_s);
    Q = stoi(Q_s);

    vector<pair<int, string>> ops;

    while (Q--)
    {
        pair<int, string> op;
        string op_s;
        getline(cin, op_s);
        op.first = stoi(op_s.substr(0, 1));
        if (op.first != 4)
        {
            op.second = op_s.substr(2, op_s.size() - 2);
        }
        ops.push_back(op);
    }

    string S;
    stack<pair<int, string>> lastOps;

    for (pair<int, string> op : ops)
    {
        if (op.first == 1)
        {
            S += op.second;
            lastOps.push(pair<int, string>(1, to_string(op.second.size())));
        }
        else if (op.first == 2)
        {
            int k = stoi(op.second);
            string remove = S.substr(S.size() - k, k);
            S = S.substr(0, S.size() - k);
            lastOps.push(pair<int, string>(2, remove));
        }
        else if (op.first == 3)
        {
            int k = stoi(op.second);
            cout << S[k - 1] << endl;
        }
        else if (op.first == 4)
        {
            pair<int, string> lop = lastOps.top();
            lastOps.pop();

            if (lop.first == 1)
            {
                int k = stoi(lop.second);
                S = S.substr(0, S.size() - k);
            }
            else if (lop.first == 2)
            {
                S += lop.second;
            }
        }
    }

    return 0;
}
