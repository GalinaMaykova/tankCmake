# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)


# название проекта, можно использовать при обращении к основной папке include_directories(${tankCmake_SOURCE_DIR}/Core)
project ("tankCmake")

# стандарт с++ - понятно
set(CMAKE_CXX_STANDARD 17)
# дирректория в которой создавать результат  (почему-то студия ничего там не создает, где вообще лежит мой exe-шник)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

#добавляем поддерикторию - это понятно
add_subdirectory(Tests)

#зачем это?
enable_testing()
