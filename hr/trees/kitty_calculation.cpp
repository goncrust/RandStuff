// https://www.hackerrank.com/challenges/kittys-calculations-on-a-tree/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int find_path_length(vector<vector<int>> edges, int start, int destination, vector<int> last, int length)
{
    if (start == destination)
        return length;

    vector<vector<int>> possible_steps;
    for (int i = 0; i < edges.size(); i++)
    {
        if (last == edges[i])
            continue;
        for (int y = 0; y < edges[i].size(); y++)
        {
            if (edges[i][y] == start)
                possible_steps.push_back(edges[i]);
        }
    }

    if (possible_steps.size() == 0)
    {
        return 0;
    }

    for (int i = 0; i < possible_steps.size(); i++)
    {
        if (possible_steps[i][0] == start)
        {
            int next = find_path_length(edges, possible_steps[i][1], destination, possible_steps[i], length + 1);
            if (next != 0)
            {
                return next;
            }
        }
        else
        {
            int next = find_path_length(edges, possible_steps[i][0], destination, possible_steps[i], length + 1);
            if (next != 0)
            {
                return next;
            }
        }
    }

    return 0;
}

vector<int> kitty(vector<vector<int>> edges, vector<vector<int>> queries)
{
    vector<int> results;
    vector<int> null_vector;

    for (int i = 0; i < queries.size(); i++)
    {
        if (queries[i].size() == 0)
        {
            results.push_back(0);
            continue;
        }

        vector<int> to_sum;
        for (int y = 0; y < queries[i].size(); y++)
        {
            for (int u = y + 1; u < queries[i].size(); u++)
            {
                to_sum.push_back(queries[i][y] * queries[i][u] * find_path_length(edges, queries[i][y], queries[i][u], null_vector, 0));
            }
        }

        int sum_result = 0;
        for (int s = 0; s < to_sum.size(); s++)
        {
            sum_result += to_sum[s];
        }

        results.push_back(sum_result % (int)(pow(10, 9) + 7));
    }

    return results;
}

int main()
{
    int nodes = NULL;
    int queries = NULL;
    vector<vector<int>> edges;
    vector<vector<int>> sets;

    string nodes_queries;
    getline(cin, nodes_queries);

    string cache = "";
    for (int i = 0; i < nodes_queries.length(); i++)
    {
        if (nodes_queries[i] == ' ')
        {
            nodes = stoi(cache);
            cache = "";
        }
        else
        {
            cache += nodes_queries[i];
        }
    }
    queries = stoi(cache);

    for (int i = 0; i < nodes - 1; i++)
    {
        string edge;
        getline(cin, edge);
        vector<int> edge_vector;
        string cache = "";
        for (int i = 0; i < edge.length(); i++)
        {
            if (edge[i] == ' ')
            {
                edge_vector.push_back(stoi(cache));
                cache = "";
            }
            else
            {
                cache += edge[i];
            }
        }
        edge_vector.push_back(stoi(cache));

        edges.push_back(edge_vector);
    }

    for (int i = 0; i < queries; i++)
    {
        int size_set;
        string size_set_s;
        getline(cin, size_set_s);
        size_set = stoi(size_set_s);

        string set_s;
        getline(cin, set_s);
        vector<int> set;
        string cache = "";
        for (int i = 0; i < set_s.length(); i++)
        {
            if (set_s[i] == ' ')
            {
                set.push_back(stoi(cache));
                cache = "";
            }
            else
            {
                cache += set_s[i];
            }
        }
        set.push_back(stoi(cache));

        sets.push_back(set);
    }

    vector<int> results = kitty(edges, sets);
    for (int i = 0; i < results.size() - 1; i++)
        cout << results[i] << endl;
    cout << results[results.size() - 1];

    return 0;
}
