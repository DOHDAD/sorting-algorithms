#include "catch.hpp"
#include "one_phase_merge_sort.h"
#include "file_helpers.h"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("OnePhaseMergeSort: large random file (10000 elements)", "[external][one_phase][positive]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_one_phase_large.txt";
    std::string outputFile = testDir + "/output_one_phase_large.txt";

    // Генерируем большой файл с 10000 случайными числами
    file_helpers::generate_random_file(inputFile, 10000, 0, 100000);

    // Запускаем сортировку
    onePhaseMergeSort(inputFile, outputFile, 1000);

    // Проверяем, что выходной файл отсортирован
    REQUIRE(file_helpers::is_sorted_file(outputFile));

    // Проверяем, что количество элементов совпадает
    auto inputData = file_helpers::read_file(inputFile);
    auto outputData = file_helpers::read_file(outputFile);
    REQUIRE(inputData.size() == outputData.size());

    fs::remove(inputFile);
    fs::remove(outputFile);
}

TEST_CASE("OnePhaseMergeSort: small file with known data", "[external][one_phase][positive]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_one_phase_small.txt";
    std::string outputFile = testDir + "/output_one_phase_small.txt";
    std::string expectedFile = testDir + "/expected_one_phase_small.txt";

    std::vector<int> inputData = { 5, 10, 18, 0, 2, 7, 11, 14 };
    file_helpers::write_file(inputFile, inputData);

    std::vector<int> expectedData = { 0, 2, 5, 7, 10, 11, 14, 18 };
    file_helpers::write_file(expectedFile, expectedData);

    onePhaseMergeSort(inputFile, outputFile, 3);

    REQUIRE(file_helpers::files_equal(outputFile, expectedFile));

    fs::remove(inputFile);
    fs::remove(outputFile);
    fs::remove(expectedFile);
}

TEST_CASE("OnePhaseMergeSort: empty file", "[external][one_phase][edge]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_one_phase_empty.txt";
    std::string outputFile = testDir + "/output_one_phase_empty.txt";

    file_helpers::write_file(inputFile, {});
    onePhaseMergeSort(inputFile, outputFile, 100);

    auto outputData = file_helpers::read_file(outputFile);
    REQUIRE(outputData.empty());

    fs::remove(inputFile);
    fs::remove(outputFile);
}