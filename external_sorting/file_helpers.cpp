#include "file_helpers.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

namespace file_helpers {

    void generate_random_file(const std::string& path, size_t count, int min_val, int max_val) {
        std::ofstream out(path);
        if (!out.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + path);
        }

        std::random_device rd;
        std::mt19937 gen(42);  // фиксированный seed для воспроизводимости тестов
        std::uniform_int_distribution<> dis(min_val, max_val);

        for (size_t i = 0; i < count; ++i) {
            out << dis(gen) << "\n";
        }

        out.close();
    }

    std::vector<int> read_file(const std::string& path) {
        std::ifstream in(path);
        if (!in.is_open()) {
            throw std::runtime_error("Cannot open file for reading: " + path);
        }

        std::vector<int> data;
        int value;
        while (in >> value) {
            data.push_back(value);
        }

        in.close();
        return data;
    }

    void write_file(const std::string& path, const std::vector<int>& data) {
        std::ofstream out(path);
        if (!out.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + path);
        }

        for (int value : data) {
            out << value << "\n";
        }

        out.close();
    }

    bool files_equal(const std::string& path1, const std::string& path2) {
        auto data1 = read_file(path1);
        auto data2 = read_file(path2);
        return data1 == data2;
    }

    bool is_sorted_file(const std::string& path) {
        auto data = read_file(path);
        return std::is_sorted(data.begin(), data.end());
    }

} // namespace file_helpers