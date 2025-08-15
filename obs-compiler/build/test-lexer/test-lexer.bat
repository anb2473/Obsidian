@echo off
echo Testing Obsidian Compiler Lexer...

REM Create directories if they don't exist
if not exist "obj-test" mkdir obj-test
if not exist "..\..\binaries" mkdir ..\..\binaries

REM Compile test lexer
echo Compiling test lexer...

REM Compile test lexer main
gcc -Wall -Wextra -std=c99 -I../../include -c test-lexer.c -o obj-test/test-lexer.o

REM Compile lexer
gcc -Wall -Wextra -std=c99 -I../../include -c ../../src/lexer.c -o obj-test/lexer.o

REM Compile each utility source file
for %%f in (../../src/utils/*.c) do (
    gcc -Wall -Wextra -std=c99 -I../../include -c ../../src/utils/%%f -o obj-test/%%~nf.o
)

REM Compile each ICD source file
for %%f in (../../src/icds/*.c) do (
    gcc -Wall -Wextra -std=c99 -I../../include -c ../../src/icds/%%f -o obj-test/%%~nf.o
)

REM Link everything together
echo Linking test lexer...
gcc obj-test/*.o -o ..\..\binaries\test-lexer.exe

if %ERRORLEVEL% EQU 0 (
    echo Test lexer built successfully!
    echo.
    echo Running lexer test...
    echo.
    "..\..\binaries\test-lexer.exe" "..\..\..\output_target\v1\in.obs"
    echo.
    pause
) else (
    echo Build failed!
    exit /b 1
)

REM Clean up object files
echo.
echo Cleaning up...
del /Q obj-test\*.o
rmdir obj-test

echo Test completed!
