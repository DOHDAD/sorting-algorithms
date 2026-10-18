#include "natural_merge_sort.h"
#include "file_helpers.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

void naturalMergeSort(const std::string& inputPath, const std::string& outputPath) {
    auto data = file_helpers::read_file(inputPath);

    // Находим естественные серии (уже отсортированные последовательности)
    std::vector<std::vector<int>> naturalSeries;
    std::vector<int> currentSeries;

    if (!data.empty()) {
        currentSeries.push_back(data[0]);

        for (size_t i = 1; i < data.size(); ++i) {
            if (data[i] >= data[i - 1]) {
                // Продолжаем текущую серию
                currentSeries.push_back(data[i]);
            }
            else {
                // Начинаем новую серию
                naturalSeries.push_back(currentSeries);
                currentSeries.clear();
                currentSeries.push_back(data[i]);
            }
        }
        naturalSeries.push_back(currentSeries);
    }

    // Сливаем все естественные серии в один выходной файл
    struct SeriesEntry {
        int value;
        size_t seriesIndex;
        size_t elementIndex;
        bool operator>(const SeriesEntry& other) const {
            return value > other.value;
        }
    };

    std::priority_queue<SeriesEntry, std::vector<SeriesEntry>, std::greater<SeriesEntry>> pq;

    for (size_t i = 0; i < naturalSeries.size(); ++i) {
        if (!naturalSeries[i].empty()) {
            pq.push({ naturalSeries[i][0], i, 0 });
        }
    }

    std::ofstream out(outputPath);
    std::vector<size_t> currentIndex(naturalSeries.size(), 0);

    while (!pq.empty()) {
        auto [value, seriesIdx, elemIdx] = pq.top();
        pq.pop();

        out << value << "\n";

        currentIndex[seriesIdx]++;
        if (currentIndex[seriesIdx] < naturalSeries[seriesIdx].size()) {
            pq.push({ naturalSeries[seriesIdx][currentIndex[seriesIdx]], seriesIdx, currentIndex[seriesIdx] });
        }
    }

    out.close();
}