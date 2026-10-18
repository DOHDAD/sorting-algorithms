#include "catch.hpp"
#include "natural_merge_sort.h"
#include "file_helpers.h"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("NaturalMergeSort: large random file (10000 elements)", "[external][natural][positive]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_natural_large.txt";
    std::string outputFile = testDir + "/output_natural_large.txt";

    // Генерируем большой файл с 10000 случайными числами
    file_helpers::generate_random_file(inputFile, 10000, 0, 100000);

    // Запускаем сортировку
    naturalMergeSort(inputFile, outputFile);

    // Проверяем, что выходной файл отсортирован
    REQUIRE(file_helpers::is_sorted_file(outputFile));

    // Проверяем, что количество элементов совпадает
    auto inputData = file_helpers::read_file(inputFile);
    auto outputData = file_helpers::read_file(outputFile);
    REQUIRE(inputData.size() == outputData.size());

    fs::remove(inputFile);
    fs::remove(outputFile);
}

TEST_CASE("NaturalMergeSort: small file with known data", "[external][natural][positive]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_natural_small.txt";
    std::string outputFile = testDir + "/output_natural_small.txt";
    std::string expectedFile = testDir + "/expected_natural_small.txt";

    std::vector<int> inputData = { 5, 10, 18, 0, 2, 7, 11, 14 };
    file_helpers::write_file(inputFile, inputData);

    std::vector<int> expectedData = { 0, 2, 5, 7, 10, 11, 14, 18 };
    file_helpers::write_file(expectedFile, expectedData);

    naturalMergeSort(inputFile, outputFile);

    REQUIRE(file_helpers::files_equal(outputFile, expectedFile));

    fs::remove(inputFile);
    fs::remove(outputFile);
    fs::remove(expectedFile);
}

TEST_CASE("NaturalMergeSort: empty file", "[external][natural][edge]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_natural_empty.txt";
    std::string outputFile = testDir + "/output_natural_empty.txt";

    file_helpers::write_file(inputFile, {});
    naturalMergeSort(inputFile, outputFile);

    auto outputData = file_helpers::read_file(outputFile);
    REQUIRE(outputData.empty());

    fs::remove(inputFile);
    fs::remove(outputFile);
}

TEST_CASE("NaturalMergeSort: already sorted file", "[external][natural][positive]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_natural_sorted.txt";
    std::string outputFile = testDir + "/output_natural_sorted.txt";

    std::vector<int> inputData = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    file_helpers::write_file(inputFile, inputData);

    naturalMergeSort(inputFile, outputFile);

    REQUIRE(file_helpers::files_equal(inputFile, outputFile));

    fs::remove(inputFile);
    fs::remove(outputFile);
}