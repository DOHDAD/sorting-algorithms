#include "catch.hpp"
#include "two_phase_merge_sort.h"
#include "file_helpers.h"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("TwoPhaseMergeSort: large random file (10000 elements)", "[external][two_phase][positive]") {
    // Создаём папку для тестовых данных
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_two_phase_large.txt";
    std::string outputFile = testDir + "/output_two_phase_large.txt";

    // Генерируем большой файл с 10000 случайными числами
    file_helpers::generate_random_file(inputFile, 10000, 0, 100000);

    // Запускаем сортировку
    twoPhaseMergeSort(inputFile, outputFile, 1000);

    // Проверяем, что выходной файл отсортирован
    REQUIRE(file_helpers::is_sorted_file(outputFile));

    // Проверяем, что количество элементов совпадает
    auto inputData = file_helpers::read_file(inputFile);
    auto outputData = file_helpers::read_file(outputFile);
    REQUIRE(inputData.size() == outputData.size());

    // Удаляем тестовые файлы
    fs::remove(inputFile);
    fs::remove(outputFile);
}

TEST_CASE("TwoPhaseMergeSort: small file with known data", "[external][two_phase][positive]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_two_phase_small.txt";
    std::string outputFile = testDir + "/output_two_phase_small.txt";
    std::string expectedFile = testDir + "/expected_two_phase_small.txt";

    // Создаём входной файл
    std::vector<int> inputData = { 5, 10, 18, 0, 2, 7, 11, 14 };
    file_helpers::write_file(inputFile, inputData);

    // Создаём файл с ожидаемым результатом
    std::vector<int> expectedData = { 0, 2, 5, 7, 10, 11, 14, 18 };
    file_helpers::write_file(expectedFile, expectedData);

    // Запускаем сортировку
    twoPhaseMergeSort(inputFile, outputFile, 3);

    // Сравниваем выходной файл с ожидаемым
    REQUIRE(file_helpers::files_equal(outputFile, expectedFile));

    // Удаляем тестовые файлы
    fs::remove(inputFile);
    fs::remove(outputFile);
    fs::remove(expectedFile);
}

TEST_CASE("TwoPhaseMergeSort: empty file", "[external][two_phase][edge]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string inputFile = testDir + "/input_two_phase_empty.txt";
    std::string outputFile = testDir + "/output_two_phase_empty.txt";

    // Создаём пустой файл
    file_helpers::write_file(inputFile, {});

    // Запускаем сортировку
    twoPhaseMergeSort(inputFile, outputFile, 100);

    // Проверяем, что выходной файл тоже пустой
    auto outputData = file_helpers::read_file(outputFile);
    REQUIRE(outputData.empty());

    // Удаляем тестовые файлы
    fs::remove(inputFile);
    fs::remove(outputFile);
}