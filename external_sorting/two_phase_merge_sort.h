#ifndef TWO_PHASE_MERGE_SORT_H
#define TWO_PHASE_MERGE_SORT_H

#include <string>

// Двухфазная сортировка слиянием с использованием файлов
// Фаза 1: разбивает входной файл на отсортированные блоки и записывает во временные файлы
// Фаза 2: сливает временные файлы в один выходной файл
void twoPhaseMergeSort(const std::string& inputPath, const std::string& outputPath,
    size_t blockSize = 1000);

#endif // TWO_PHASE_MERGE_SORT_H