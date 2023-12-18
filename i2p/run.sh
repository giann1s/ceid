# Linux
gcc -Wall -Wextra -g3 ./main.c -o /tmp/out && chmod u+x /tmp/out && /tmp/out

# Compile Windows exe on Linux
x86_64-w64-mingw32-gcc -Wall -Wextra -g3 ./main.c -o main.exe ./*.dll && wine ./main.exe
