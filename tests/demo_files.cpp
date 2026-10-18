#include "catch.hpp"
#include "two_phase_merge_sort.h"
#include "one_phase_merge_sort.h"
#include "natural_merge_sort.h"
#include "file_helpers.h"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Demo: TwoPhaseMergeSort with files", "[demo][two_phase]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/demo_two_phase_input.txt";
    std::string outputFile = testDir + "/demo_two_phase_output.txt";

    // Создаём входной файл с вашим массивом
    std::vector<int> inputData = { 5, 10, 18, 0, 2, 7, 11, 14 };
    file_helpers::write_file(inputFile, inputData);

    // Запускаем сортировку
    twoPhaseMergeSort(inputFile, outputFile, 3);

    // Файлы НЕ удаляем — оставляем для демонстрации
    SUCCEED("Files created in test_data/ folder");
}

TEST_CASE("Demo: OnePhaseMergeSort with files", "[demo][one_phase]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/demo_one_phase_input.txt";
    std::string outputFile = testDir + "/demo_one_phase_output.txt";

    std::vector<int> inputData = { 5, 10, 18, 0, 2, 7, 11, 14 };
    file_helpers::write_file(inputFile, inputData);

    onePhaseMergeSort(inputFile, outputFile, 3);

    SUCCEED("Files created in test_data/ folder");
}

TEST_CASE("Demo: NaturalMergeSort with files", "[demo][natural]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/demo_natural_input.txt";
    std::string outputFile = testDir + "/demo_natural_output.txt";

    std::vector<int> inputData = { 5, 10, 18, 0, 2, 7, 11, 14 };
    file_helpers::write_file(inputFile, inputData);

    naturalMergeSort(inputFile, outputFile);

    SUCCEED("Files created in test_data/ folder");
}

TEST_CASE("Demo: Large file generation", "[demo][large]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/demo_large_input.txt";
    std::string outputFile = testDir + "/demo_large_output.txt";

    // Генерируем большой файл с 10000 чисел
    file_helpers::generate_random_file(inputFile, 10000, 0, 100000);

    // Сортируем
    twoPhaseMergeSort(inputFile, outputFile, 1000);

    SUCCEED("Large files created in test_data/ folder");
}