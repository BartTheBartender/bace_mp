rm -rf main
g++ -Wall -Wextra -Wpedantic -std=c++11 main.cpp source.cpp -o main
echo "-------------------"
echo "out:"
./main > out
cat out
echo "-------------------"
echo "correct:"
cat correct
echo "-------------------"
diff -y correct out
rm -rf out
zip source source.cpp source.h

