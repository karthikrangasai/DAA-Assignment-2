mkdir -p build


g++ -o build/test_case_generator.o test_case_generator.cpp
echo "> Generating ./build/test_case_generator.o"

g++ -g -o build/daaaaaa main.cpp
echo "> Generating ./build/daaaaaa"

./build/test_case_generator.o 20 tests/inputs/in.txt
echo "> Generated 20 points in tests/inputs/in.txt"