#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <string>
#include <vector>

namespace file_helpers {

    // Генерирует файл с count случайными числами в диапазоне [min_val, max_val]
    void generate_random_file(const std::string& path, size_t count,
        int min_val = 0, int max_val = 1000000);

    // Читает файл с числами (по одному на строку) в вектор
    std::vector<int> read_file(const std::string& path);

    // Записывает вектор чисел в файл (по одному на строку)
    void write_file(const std::string& path, const std::vector<int>& data);

    // Сравнивает два файла, возвращает true если они одинаковые
    bool files_equal(const std::string& path1, const std::string& path2);

    // Проверяет, что файл отсортирован по возрастанию
    bool is_sorted_file(const std::string& path);

} // namespace file_helpers

#endif // FILE_HELPERS_H