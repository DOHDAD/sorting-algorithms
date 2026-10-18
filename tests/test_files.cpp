#include <catch.hpp>
#include "file_helpers.h"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Write and read file with specific array", "[external][file_helpers]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string filePath = testDir + "/test_specific_array.txt";

    // Ваш массив
    std::vector<int> original = { 5, 10, 18, 0, 2, 7, 11, 14 };

    // Записываем файл
    file_helpers::write_file(filePath, original);

    // Читаем файл
    auto loaded = file_helpers::read_file(filePath);

    // Проверяем, что данные совпадают
    REQUIRE(loaded == original);
    REQUIRE(loaded.size() == 8);

    fs::remove(filePath);
}

TEST_CASE("Generate random file and verify content", "[external][file_helpers]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string filePath = testDir + "/test_random.txt";

    // Генерируем файл с 100 числами
    file_helpers::generate_random_file(filePath, 100, 0, 1000);

    // Читаем файл и проверяем количество элементов
    auto data = file_helpers::read_file(filePath);
    REQUIRE(data.size() == 100);

    // Проверяем, что все числа в диапазоне
    for (int value : data) {
        REQUIRE(value >= 0);
        REQUIRE(value <= 1000);
    }

    fs::remove(filePath);
}

TEST_CASE("Files equal comparison", "[external][file_helpers]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string file1 = testDir + "/test_equal1.txt";
    std::string file2 = testDir + "/test_equal2.txt";

    std::vector<int> data = { 1, 2, 3, 4, 5 };

    file_helpers::write_file(file1, data);
    file_helpers::write_file(file2, data);

    REQUIRE(file_helpers::files_equal(file1, file2));

    fs::remove(file1);
    fs::remove(file2);
}

TEST_CASE("Is sorted file check", "[external][file_helpers]") {
    std::string testDir = "test_data";
    fs::create_directories(testDir);

    std::string sortedFile = testDir + "/test_sorted.txt";
    std::string unsortedFile = testDir + "/test_unsorted.txt";

    file_helpers::write_file(sortedFile, { 1, 2, 3, 4, 5 });
    file_helpers::write_file(unsortedFile, { 5, 3, 1, 4, 2 });

    REQUIRE(file_helpers::is_sorted_file(sortedFile));
    REQUIRE_FALSE(file_helpers::is_sorted_file(unsortedFile));

    fs::remove(sortedFile);
    fs::remove(unsortedFile);
}