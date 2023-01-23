#include <iostream>
#include <random>
#include <string>
#include <bitset>

enum ComplexityLevel {
   Low = 1,
   Medium = 2,
   High = 3,
   Manual = 0
};

std::string generatePassword(int length, std::bitset<4> options, std::mt19937& generator) {
   std::array<std::string, 4> characters = { {"ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz", "0123456789", "!#$%&'()*+,-./:;<=>?@[]^_{|}~"} };
   std::string password;
   std::string allCharacters;
   for (int i = 0; i < options.size(); i++) {
      if (options[i]) {
         allCharacters += characters[i];
      }
   }
   std::uniform_int_distribution<int> distribution(0, allCharacters.size() - 1);
   for (int i = 0; i < length; i++) {
      password += allCharacters[distribution(generator)];
   }
   return password;
}

int getPasswordLength() {
   int length;
   do {
      std::cout << "Enter the desired password length: ";
      std::cin >> length;
      if (std::cin.fail() || length <= 0) {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<int>::max(), '\n');
         std::cout << "Invalid input. Please enter a positive integer for the password length: ";
      }
   } while (std::cin.fail() || length <= 0);
   return length;
}

int getComplexityLevel() {
   int complexity;
   do {
      std::cout << "Select password complexity level (1 = low, 2 = medium, 3 = high) or enter 0 for manual options: ";
      std::cin >> complexity;
      if (complexity < 0 || complexity > 3 || std::cin.fail()) {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<int>::max(), '\n');
         std::cout << "Invalid input. Select password complexity level (1 = low, 2 = medium, 3 = high) or enter 0 for manual options: ";
      }
   } while (complexity < 0 || complexity > 3 || std::cin.fail());
   return complexity;
}

std::bitset<4> getManualOptions() {
   std::bitset<4> options;
   while (options.none()) {
      for (int i = 0; i < 4; i++) {
         std::cout << "Include " << (i == 0 ? "upper case letters" : i == 1 ? "lower case letters" : i == 2 ? "numbers" : "symbols") << " in the password? (1 = yes, 0 = no): ";
         std::cin >> options[i];
      }
      if (!options.any()) {
         std::cout << "Please select at least one option before generating a password." << std::endl;
         continue;
      }
   }
   return options;
}

constexpr std::array<std::bitset<4>, 4> options = {
{1, 1, 0, 0}, // Low complexity: upper and lower case letters
{1, 1, 1, 0}, // Medium complexity: upper and lower case letters and numbers
{1, 1, 1, 1}, // High complexity: upper and lower case letters, numbers, and symbols
{0, 0, 0, 0}  // Manual complexity: no options selected
};

std::bitset<4> setOptions(ComplexityLevel level) {
   return options[level];
};

int main() {
   int length = getPasswordLength();
   ComplexityLevel level = (ComplexityLevel)getComplexityLevel();
   std::string password;
   std::random_device rd;
   std::mt19937 generator(rd());

   switch (level) {
   case Low:
      password = generatePassword(length, setOptions(Low), generator);
      break;
   case Medium:
      password = generatePassword(length, setOptions(Medium), generator);
      break;
   case High:
      password = generatePassword(length, setOptions(High), generator);
      break;
   case Manual:
      std::bitset<4> manualOptions = getManualOptions();
      password = generatePassword(length, manualOptions, generator);
      break;
   }

   std::cout << "Generated password: " << password << std::endl;
   return 0;
}
