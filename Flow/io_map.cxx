/*################################### AMD Copyright (c) 2023
###################################
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
###############################################################k##############################*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Custom hash function for tuple<int, int, int>
struct TupleHash {
  template <class... Ts>
  std::size_t operator()(const std::tuple<Ts...> &t) const {
    return hash_impl(t, std::index_sequence_for<Ts...>());
  }

private:
  template <class Tuple, size_t... Is>
  std::size_t hash_impl(const Tuple &t, std::index_sequence<Is...>) const {
    return combine_hashes(
        std::hash<typename std::tuple_element<Is, Tuple>::type>{}(
            std::get<Is>(t))...);
  }

  template <class... Hashes>
  std::size_t combine_hashes(const Hashes &...hashes) const {
    size_t result = 0;
    size_t hashes_array[] = {static_cast<size_t>(hashes)...};
    for (size_t hash : hashes_array) {
      result ^= hash + 0x9e3779b9 + (result << 6) + (result >> 2);
    }
    return result;
  }
};

int readMap(std::unordered_map<std::tuple<int, int, int>, std::string,
                               TupleHash> &dataMap) {
  // Define an unordered_map to store the mappings

  // Open the CSV file for reading
  std::ifstream inputFile("io_map.csv");
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open io_map.csv" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(line);
    std::string token;

    if (line.empty() || line[0] == '#') {
      continue;
    }

    while (std::getline(tokenStream, token, ',')) {
      tokens.push_back(token);
    }

    int col1 = std::stoi(tokens[0]), col2 = std::stoi(tokens[1]),
        col3 = std::stoi(tokens[2]);
    std::string col4(tokens[3]), col5(tokens[4]);

    // Create a tuple from the first three columns
    std::tuple<int, int, int> key = std::make_tuple(col1, col2, col3);

    // Add the mapping to the unordered_map
    dataMap[key] = col5;
  }

  // Close the input file
  inputFile.close();
#if 0
    // Access the hashmap entries
    for (const auto& entry : dataMap) {
        std::cout << std::get<0>(entry.first) << ","
                  << std::get<1>(entry.first) << ","
                  << std::get<2>(entry.first) << " -> "
                  << entry.second << std::endl;
    }
#endif
  return 0;
}

int useMap(std::unordered_map<std::tuple<int, int, int>, std::string, TupleHash>
               &dataMap) {
  // Open the design.pl file for reading
  // Format: instance_name col row offset FIXED
  //
  std::ifstream inputFile("design.pl");
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open the file." << std::endl;
    return 1;
  }

  std::cout << "place_cell { \\" << std::endl;
  std::string line;
  while (std::getline(inputFile, line)) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(line);
    std::string token;

    if (line.empty() || line[0] == '#') {
      continue;
    }

    while (std::getline(tokenStream, token, ' ')) {
      tokens.push_back(token);
    }

    std::string name = tokens[0];
    int col = std::stoi(tokens[1]), row = std::stoi(tokens[2]),
        offset = std::stoi(tokens[3]);

    // Create a tuple from the first three columns
    std::tuple<int, int, int> key = std::make_tuple(col, row, offset);

    // Add the mapping to the unordered_map
    std::cout << "  " << name << " " << dataMap[key] << " \\" << std::endl;
  }
  std::cout << "}" << std::endl;

  // Close the input file
  inputFile.close();
}

int main() {
  std::unordered_map<std::tuple<int, int, int>, std::string, TupleHash> dataMap;
  readMap(dataMap);
  useMap(dataMap);
  return 0;
}
