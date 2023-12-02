#include <iostream>
#include <string>
#include <regex>
#include <fstream>

int main() {
	unsigned int calibration_value = 0;

	std::regex number_regex("(?=([\\d]|one|two|three|four|five|six|seven|eight|nine))");
	std::regex_token_iterator<std::string::const_iterator> regex_iterator_end;

	const std::map<std::string, std::string> word_to_number {
		{"one", "1"},
		{"two", "2"},
		{"three", "3"},
		{"four", "4"},
		{"five", "5"},
		{"six", "6"},
		{"seven", "7"},
		{"eight", "8"},
		{"nine", "9"}
	};

	std::string line;
	std::ifstream infile("input.txt");
	while (std::getline(infile, line)) {
		std::regex_token_iterator<std::string::const_iterator> regex_iterator(line.begin(), line.end(), number_regex, 1);
		std::string first_value;
		std::string last_value;

		for (int i = 0; regex_iterator != regex_iterator_end; ++regex_iterator, ++i) {
			auto value = regex_iterator->str();
			if (i == 0) first_value = value;
			last_value = value;
		}

		if (word_to_number.contains(first_value)) first_value = word_to_number.at(first_value);
		if (word_to_number.contains(last_value)) last_value = word_to_number.at(last_value);

		calibration_value += std::stoi(first_value + last_value);
	}

	std::cout << calibration_value << std::endl;
	return 0;
}