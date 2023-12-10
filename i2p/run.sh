# Linux
gcc ./main.c -o /tmp/out && chmod a+x /tmp/out && /tmp/out

# Compile Windows exe on Linux
x86_64-w64-mingw32-gcc main.c -o main.exe ./*.dll && wine main.exe
