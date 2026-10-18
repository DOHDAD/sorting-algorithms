#include "two_phase_merge_sort.h"
#include "file_helpers.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <filesystem>

namespace fs = std::filesystem;

void twoPhaseMergeSort(const std::string& inputPath, const std::string& outputPath, size_t blockSize) {
    // Создаём временную папку
    std::string tempDir = "temp_sort";
    fs::create_directories(tempDir);

    // Фаза 1: разбиваем файл на блоки, сортируем каждый блок, записываем во временные файлы
    auto data = file_helpers::read_file(inputPath);
    std::vector<std::string> tempFiles;

    for (size_t i = 0; i < data.size(); i += blockSize) {
        size_t end = std::min(i + blockSize, data.size());
        std::vector<int> block(data.begin() + i, data.begin() + end);
        std::sort(block.begin(), block.end());

        std::string tempFile = tempDir + "/block_" + std::to_string(i / blockSize) + ".txt";
        file_helpers::write_file(tempFile, block);
        tempFiles.push_back(tempFile);
    }

    // Фаза 2: сливаем все временные файлы в один выходной файл
    struct FileEntry {
        int value;
        size_t fileIndex;
        bool operator>(const FileEntry& other) const {
            return value > other.value;
        }
    };

    std::priority_queue<FileEntry, std::vector<FileEntry>, std::greater<FileEntry>> pq;
    std::vector<std::ifstream> streams(tempFiles.size());
    std::vector<int> currentValues(tempFiles.size());

    for (size_t i = 0; i < tempFiles.size(); ++i) {
        streams[i].open(tempFiles[i]);
        if (streams[i] >> currentValues[i]) {
            pq.push({ currentValues[i], i });
        }
    }

    std::ofstream out(outputPath);
    while (!pq.empty()) {
        auto [value, fileIndex] = pq.top();
        pq.pop();

        out << value << "\n";

        if (streams[fileIndex] >> currentValues[fileIndex]) {
            pq.push({ currentValues[fileIndex], fileIndex });
        }
    }

    out.close();

    // Закрываем потоки
    for (auto& stream : streams) {
        stream.close();
    }

    // Удаляем временные файлы
    for (const auto& tempFile : tempFiles) {
        fs::remove(tempFile);
    }
    fs::remove(tempDir);
}