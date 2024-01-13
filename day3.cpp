#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

typedef map<pair<int, int>, int> map_pair_int;

bool has_sym_neighbour(pair<pair<int, int>, int> num, vector<int>& sym_list) {
	for (int sym : sym_list) {
		if (sym >= num.first.first - 1 && sym <= num.first.second + 1)
			return (true);
	}
	return (false);
}

int part1(ifstream &f) {
	int sum = 0;
	string line, next_line;
	vector<int> next_sym_list, sym_list, past_sym_list;
	map_pair_int num_list;
	bool last_line = false;
	while (1) {
		line = next_line;
		
		// break out after second failure of getline
		if (!getline(f, next_line))
		{
			next_line.clear();
			if (last_line)
				break;
			last_line = true;
		}

		string::iterator cursor = line.begin();
		// store numbers from current line and relative positions of start and end
		while (cursor != line.end()) {
			cursor = find_if(cursor, line.end(), [](char ch) {if (ch >= '0' && ch <= '9') return true; else return false;});
			if (cursor == line.end())
				break;
			int i = distance(line.begin(), cursor);
			int num = stoi(line.substr(i));
			cursor = find_if(cursor, line.end(), [](char ch){if (ch < '0' || ch > '9') return true; else return false;});
			num_list.insert({{i, distance(line.begin(), cursor) - 1}, num});
		}

		// store next line symbol positions
		cursor = next_line.begin();
		while (cursor != next_line.end()) {
			cursor = find_if(cursor, next_line.end(), [](char ch) {if (!isdigit(ch) && ch != '.') return true; return false;});
			if (cursor == next_line.end())
				break;
			next_sym_list.push_back(distance(next_line.begin(), cursor));
			cursor++;
		}

		// add numbers with neighbouring symbol to sum
 		for (auto num : num_list) {
			if (has_sym_neighbour(num, sym_list) || has_sym_neighbour(num, past_sym_list) || has_sym_neighbour(num, next_sym_list))
				sum += num.second;
		}

		past_sym_list = sym_list;
		sym_list = next_sym_list;

		num_list.clear();
		next_sym_list.clear();
	}
	return sum;
}

int get_gear_ratio(int sym, map_pair_int& past_num_list, map_pair_int& num_list, map_pair_int& next_num_list) {
	vector<int> part_nums;
	multimap<pair<int, int>, int> tmp(past_num_list.begin(), past_num_list.end());
	tmp.insert(num_list.begin(), num_list.end());
	tmp.insert(next_num_list.begin(), next_num_list.end());

	for (auto num : tmp) {
		if (sym >= num.first.first - 1 && sym <= num.first.second + 1)
			part_nums.push_back(num.second);
	}

	if (part_nums.size() == 2)
		return part_nums[0] * part_nums[1];
	return (0);
}

long part2(ifstream &f) {
	long sum = 0;
	string line, next_line;
	vector<int> sym_list;
	map_pair_int num_list, past_num_list, next_num_list;
	bool last_line = false;
	while (1) {
		
		// break out after second failure of getline
		line = next_line;
		if (!getline(f, next_line))
		{
			next_line.clear();
			if (last_line)
				break;
			last_line = true;
		}

		// store numbers on next line and relative positions of start and end
		string::iterator cursor = next_line.begin();
		while (cursor != next_line.end()) {
			cursor = find_if(cursor, next_line.end(), [](char ch) {if (ch >= '0' && ch <= '9') return true; else return false;});
			if (cursor == next_line.end())
				break;
			int i = distance(next_line.begin(), cursor);
			int num = stoi(next_line.substr(i));
			cursor = find_if(cursor, next_line.end(), [](char ch){if (ch < '0' || ch > '9') return true; else return false;});
			next_num_list.insert({{i, distance(next_line.begin(), cursor) - 1}, num});
		}

		// store current line symbol positions
		cursor = line.begin();
		while (cursor != line.end()) {
			cursor = find_if(cursor, line.end(), [](char ch) {if (ch == '*') return true; return false;});
			if (cursor == line.end())
				break;
			sym_list.push_back(distance(line.begin(), cursor));
			cursor++;
		}

		// add numbers with neighbouring symbol to sum
 		for (auto sym : sym_list)
			sum += get_gear_ratio(sym, past_num_list, num_list, next_num_list);

		past_num_list = num_list;
		num_list = next_num_list;

		sym_list.clear();
		next_num_list.clear();
	}
	return sum;
}

int main() {
	ifstream f;
	f.open("input", ios_base::openmode::_S_in);
	cout << "Part 1: " << part1(f) << endl;
	f.clear();
	f.seekg(0);
	cout << "Part 2: " << part2(f) << endl;
	f.close();
}