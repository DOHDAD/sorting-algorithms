#include "one_phase_merge_sort.h"
#include "file_helpers.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

void onePhaseMergeSort(const std::string& inputPath, const std::string& outputPath, size_t seriesSize) {
    auto data = file_helpers::read_file(inputPath);

    // Разбиваем на серии и сортируем каждую
    std::vector<std::vector<int>> series;
    for (size_t i = 0; i < data.size(); i += seriesSize) {
        size_t end = std::min(i + seriesSize, data.size());
        std::vector<int> series_data(data.begin() + i, data.begin() + end);
        std::sort(series_data.begin(), series_data.end());
        series.push_back(series_data);
    }

    // Сливаем все серии в один выходной файл
    struct SeriesEntry {
        int value;
        size_t seriesIndex;
        size_t elementIndex;
        bool operator>(const SeriesEntry& other) const {
            return value > other.value;
        }
    };

    std::priority_queue<SeriesEntry, std::vector<SeriesEntry>, std::greater<SeriesEntry>> pq;

    for (size_t i = 0; i < series.size(); ++i) {
        if (!series[i].empty()) {
            pq.push({ series[i][0], i, 0 });
        }
    }

    std::ofstream out(outputPath);
    std::vector<size_t> currentIndex(series.size(), 0);

    while (!pq.empty()) {
        auto [value, seriesIdx, elemIdx] = pq.top();
        pq.pop();

        out << value << "\n";

        currentIndex[seriesIdx]++;
        if (currentIndex[seriesIdx] < series[seriesIdx].size()) {
            pq.push({ series[seriesIdx][currentIndex[seriesIdx]], seriesIdx, currentIndex[seriesIdx] });
        }
    }

    out.close();
}