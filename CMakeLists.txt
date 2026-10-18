cmake_minimum_required(VERSION 3.20)
project(Sem1-4 LANGUAGES CXX)

# Настройки C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для корректной работы с кириллицей в Visual Studio
if(MSVC)
    add_compile_options(/utf-8)
endif()

# ============================================
# БАЗОВЫЕ СОРТИРОВКИ (sorting/)
# ============================================
set(BASIC_SORTS
    insertion_sort
    selection_sort
    exchange_sort
    bubble_sort
    optimized_bubble_sort
)

foreach(name IN LISTS BASIC_SORTS)
    add_library(${name} STATIC sorting/${name}.cpp sorting/${name}.h "external_sorting/file_helpers.cpp")
    target_include_directories(${name} PUBLIC sorting)
endforeach()

# ============================================
# УЛУЧШЕННЫЕ СОРТИРОВКИ (enhanced_sorting/)
# ============================================
set(ENHANCED_SORTS
    binary_insertion_sort
    quick_sort
    shaker_sort
    shell_sort
)

foreach(name IN LISTS ENHANCED_SORTS)
    add_library(${name} STATIC enhanced_sorting/${name}.cpp enhanced_sorting/${name}.h "external_sorting/file_helpers.cpp")
    target_include_directories(${name} PUBLIC enhanced_sorting)
endforeach()

# ============================================
# ВНЕШНИЕ СОРТИРОВКИ (external_sorting/)
# ============================================
set(EXTERNAL_SORTS
    natural_merge_sort
    one_phase_merge_sort
    two_phase_merge_sort
)

foreach(name IN LISTS EXTERNAL_SORTS)
    add_library(${name} STATIC external_sorting/${name}.cpp external_sorting/${name}.h "external_sorting/file_helpers.cpp")
    target_include_directories(${name} PUBLIC external_sorting)
endforeach()
# Вспомогательный файл для работы с файлами (добавляем в каждую библиотеку)
foreach(name IN LISTS EXTERNAL_SORTS)
    target_sources(${name} PRIVATE external_sorting/file_helpers.cpp)
endforeach()
# ============================================
# ОБЪЕДИНЯЕМ ВСЕ БИБЛИОТЕКИ
# ============================================
set(ALL_SORTS
    ${BASIC_SORTS}
    ${ENHANCED_SORTS}
    ${EXTERNAL_SORTS}
)

# ============================================
# ТЕСТЫ (ОДИН ИСПОЛНЯЕМЫЙ ФАЙЛ)
# ============================================
add_executable(AllTests
    # Тесты базовых сортировок
    tests/test_insertion_sort.cpp
    tests/test_selection_sort.cpp
    tests/test_exchange_sort.cpp
    tests/test_bubble_sort.cpp
    tests/test_optimized_bubble_sort.cpp
    
    
    # Тесты улучшенных сортировок
    tests/test_binary_insertion_sort.cpp
    tests/test_quick_sort.cpp
    tests/test_shaker_sort.cpp
    tests/test_shell_sort.cpp
    
    # Тесты внешних сортировок
    tests/test_natural_merge_sort.cpp
    tests/test_one_phase_merge_sort.cpp
    tests/test_two_phase_merge_sort.cpp
    tests/demo_files.cpp
 "external_sorting/file_helpers.cpp")

# Подключаем папки с заголовками:
# - tests/          (на всякий случай, если там что-то есть)
# - sorting/        (заголовки базовых сортировок)
# - enhanced_sorting/ (заголовки улучшенных сортировок)
# - external_sorting/ (заголовки внешних сортировок)
# - ../catch2/      (Catch2 лежит рядом с Sem1-4)
target_include_directories(AllTests PRIVATE
    tests
    sorting
    enhanced_sorting
    external_sorting
    ${CMAKE_CURRENT_SOURCE_DIR}/../catch2
)

# Линкуем тесты со всеми библиотеками сортировок
target_link_libraries(AllTests PRIVATE ${ALL_SORTS})

# ============================================
# CTEST ИНТЕГРАЦИЯ
# ============================================
enable_testing()

# Тесты по видам сортировок
add_test(NAME basic_sorts COMMAND AllTests "[basic]")
add_test(NAME enhanced_sorts COMMAND AllTests "[enhanced]")
add_test(NAME external_sorts COMMAND AllTests "[external]")

# Все тесты сразу
add_test(NAME all_tests COMMAND AllTests)