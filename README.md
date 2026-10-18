# Sem1-4: Алгоритмы сортировки

Проект содержит реализацию алгоритмов сортировки трёх видов:

## Базовые сортировки (sorting/)
- Insertion Sort
- Selection Sort
- Exchange Sort
- Bubble Sort
- Optimized Bubble Sort

## Улучшенные сортировки (enhanced_sorting/)
- Binary Insertion Sort
- Quick Sort
- Shaker Sort
- Shell Sort

## Внешние сортировки (external_sorting/)
- Natural Merge Sort
- One Phase Merge Sort
- Two Phase Merge Sort

## Сборка

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug