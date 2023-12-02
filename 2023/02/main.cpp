#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

std::vector<std::string> find_substrings(const std::string &str, std::string delimiter)
{
	std::vector<std::string> result;

	size_t prev = 0;
	size_t pos = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		result.push_back(str.substr(prev, pos - prev));
		prev = pos + 2;
	}

	result.push_back(str.substr(prev, pos - prev));
	return result;
}

bool is_game_valid(const std::vector<std::string>& sets, const std::map<std::string, int>& color_limits)
{
	for (int i = 0; i < sets.size(); i++)
	{
		std::string set = sets[i];
		std::vector<std::string> cubes = find_substrings(set, ",");
		for (int j = 0; j < cubes.size(); j++)
		{
			std::string cube = cubes[j];
			size_t cube_delimiter_pos = cube.find(" ");
			int value = std::stoi(cube.substr(0, cube_delimiter_pos));
			std::string color = cube.substr(cube_delimiter_pos + 1);

			int cmp = color_limits.at(color);
			if (value > cmp) {
				return false;
			}
		}
	}

	return true;
}

int calculate_game_power(const std::vector<std::string>& sets)
{
	std::map<std::string, int> color_min_count {
		{"red", 0},
		{"green", 0},
		{"blue", 0}
	};

	for (int i = 0; i < sets.size(); i++)
	{
		std::string set = sets[i];
		std::vector<std::string> cubes = find_substrings(set, ",");
		for (int j = 0; j < cubes.size(); j++)
		{
			std::string cube = cubes[j];
			size_t cube_delimiter_pos = cube.find(" ");
			int value = std::stoi(cube.substr(0, cube_delimiter_pos));
			std::string color = cube.substr(cube_delimiter_pos + 1);

			if (color_min_count.at(color) < value) {
				color_min_count[color] = value;
			}
		}
	}

	return color_min_count.at("red") * color_min_count.at("green") * color_min_count.at("blue");
}

int main()
{
	int ids_sum = 0;
	int power_sum = 0;

	const std::map<std::string, int> color_limits {
		{"red", 12},
		{"green", 13},
		{"blue", 14}
	};

	std::string line;
	std::ifstream infile("input.txt");
	while (std::getline(infile, line))
	{
		size_t game_delimiter = line.find(":");
		std::string game_str = line.substr(0, game_delimiter);
		int game_id = std::stoi(game_str.substr(game_str.find(" ") + 1));

		std::vector<std::string> sets = find_substrings(line.substr(game_delimiter + 2), ";");
		if (is_game_valid(sets, color_limits)) {
			ids_sum += game_id;
		}

		power_sum += calculate_game_power(sets);
	}

	std::cout << ids_sum << std::endl;
	std::cout << power_sum << std::endl;
	return 0;
}
