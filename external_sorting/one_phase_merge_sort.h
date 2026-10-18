#ifndef ONE_PHASE_MERGE_SORT_H
#define ONE_PHASE_MERGE_SORT_H

#include <string>

// Однофазная сортировка слиянием с использованием файлов
// Читает файл, разбивает на серии фиксированного размера, сразу сливает их в выходной файл
void onePhaseMergeSort(const std::string& inputPath, const std::string& outputPath,
    size_t seriesSize = 1000);

#endif // ONE_PHASE_MERGE_SORT_H