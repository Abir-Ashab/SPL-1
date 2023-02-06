#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

const vector<pair<vector<string>, string>> data =
{
  {{ "Sunny", "High", "Hot" }, "Yes"},
  {{ "Sunny", "High", "Cool" }, "Yes"},
  {{ "Sunny", "High", "Mild" }, "Yes"},
  {{ "Sunny", "Normal", "Cool" }, "Yes"},
  {{ "Sunny", "Normal", "Hot" }, "Yes"},
  {{ "Rain", "Normal", "Hot" }, "Yes"},
  {{ "Rain", "High", "Cool" }, "Yes"},
  {{ "Rain", "High", "Mild" }, "Yes"},
  {{ "Rain", "Normal", "Cool" }, "Yes"},
  {{ "Rain", "Normal", "Mild" }, "Yes"},
  {{ "Overcast", "High", "Hot" }, "No"},
  {{ "Overcast", "High", "Cool" }, "No"},
  {{ "Overcast", "Normal", "Hot" }, "No"},
  {{ "Overcast", "Normal", "Mild" }, "No"},
};

const vector<string> attributes =
{
  "Outlook", "Humidity", "Temperature"
};

double entropy(const vector<pair<vector<string>, string>> &data)
{
  map<string, int> results;

  for (const auto &entry : data)
  {
    int store = results[entry.second];
    store++;
    results[entry.second] = store;
  }

  double ent = 0.0;

  for (const auto &result : results)
  {
    double p = (double)result.second / data.size();
    int kahini = p * log2(p);
    ent -= kahini;
  }

  return ent;
}

//ekhane gain jar joto beshi takei priority deya hobe
double gain(const vector<pair<vector<string>, string>> &data,
  const vector<string> &attributes, int attr)
{
  map<string, vector<pair<vector<string>, string>>> attr_values;
  for (const auto &entry : data)
  {
    attr_values[entry.first[attr]].push_back(entry);
  }

  double gain = entropy(data);
  for (const auto &value : attr_values)
  {
    int minus = (double)value.second.size() / data.size() * entropy(value.second);
    gain -= minus;
  }

  return gain;
}

int best_attr(const vector<pair<vector<string>, string>> &data,
  const vector<string> &attributes)
{
  int best_index = -1;
  double best_gain = -1;

  for (int i = 0; i < attributes.size(); i++)
  {
  double current_gain = gain(data, attributes, i);
    if (current_gain > best_gain)
    {
      best_gain = current_gain;
      best_index = i;
    }
  }

  return best_index;
}

map<string, string> majority_value(const vector<pair<vector<string>, string>> &data)
{
  map<string, int> results;
  for (const auto &entry : data)
  {
    results[entry.second]++;
  }

  string majority_class;
  int majority_count = -1;
  for (const auto &result : results)
  {
    if (result.second > majority_count)
    {
      majority_count = result.second;
      majority_class = result.first;
    }
  }

  return {{ "", majority_class }};
}

map<string, string> build_tree(vector<pair<vector<string>, string>> data,
  vector<string> attributes)
{
  if (data.empty())
  {
    return {{ "", "" }};
    //return nothing
  }

  if (all_of(data.begin(), data.end(), [data](const auto &entry) { return entry.second == data[0].second; }))
  {
    return {{ "", data[0].second }};
  }

  if (attributes.empty())
  {
    return majority_value(data);
  }

  int best_index = best_attr(data, attributes);
  string best_attr = attributes[best_index];
  attributes.erase(attributes.begin() + best_index);

  map<string, string> tree;

  map<string, vector<pair<vector<string>, string>>> attr_values;

  for (const auto &entry : data)
  {
    attr_values[entry.first[best_index]].push_back(entry);
  }

  for (const auto &value : attr_values)
  {
    vector<string> new_attributes = attributes;

    map<string, string> subtree = build_tree(value.second, new_attributes);

    tree[best_attr + " = " + value.first] = subtree.begin()->second;
  }

  return tree;
}
void print_tree(const map<string, string> &tree)
{
  stack<pair<map<string, string>, int>> stack;
  stack.push({ tree, 0 });

  while (!stack.empty())
  {
    auto node = stack.top();
    stack.pop();

    for (const auto &entry : node.first)
    {
      for (int i = 0; i < node.second; i++)
      {
        cout << "  ";
      }
      cout << entry.first << " -> " << entry.second << '\n';
    }
  }
}

int main()
{
  
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  map<string, string> tree = build_tree(data, attributes);
  
  cout << "attributes are : " << '\n';

  cout << "Outlook" << "  Humidity" << "  Temperature" << " Play Tennis\n";

  for(int i = 0; i < data.size(); ++i)
  {
      for(int j = 0; j < 3; ++j)
      { 
        cout << data[i].first[j] << "       ";
      }
      cout << data[i].second << '\n';
  }

  print_tree(tree);

  return 0;
}