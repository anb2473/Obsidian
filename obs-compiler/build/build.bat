@echo off
echo Building Obsidian Compiler...

REM Create directories if they don't exist
if not exist "obj" mkdir obj
if not exist "obj\utils" mkdir obj\utils
if not exist "obj\icds" mkdir obj\icds
if not exist "..\binaries" mkdir ..\binaries

REM Compile source files
echo Compiling source files...

REM Compile main source files
gcc -Wall -Wextra -std=c99 -I../include -c ../src/lexer.c -o obj/lexer.o
gcc -Wall -Wextra -std=c99 -I../include -c ../src/compiler.c -o obj/compiler.o
gcc -Wall -Wextra -std=c99 -I../include -c ../src/parser.c -o obj/parser.o

REM Compile utility files
gcc -Wall -Wextra -std=c99 -I../include -c ../src/utils/str-utils.c -o obj/utils/str-utils.o

REM Compile ICD files
gcc -Wall -Wextra -std=c99 -I../include -c ../src/icds/char-ptr-icd.c -o obj/icds/char-ptr-icd.o
gcc -Wall -Wextra -std=c99 -I../include -c ../src/icds/prototype-symbol-icd.c -o obj/icds/prototype-symbol-icd.o
gcc -Wall -Wextra -std=c99 -I../include -c ../src/icds/prototype-functions-icd.c -o obj/icds/prototype-functions-icd.o
gcc -Wall -Wextra -std=c99 -I../include -c ../src/icds/global-var-symbol-icd.c -o obj/icds/global-var-symbol-icd.o
gcc -Wall -Wextra -std=c99 -I../include -c ../src/icds/global-vars-icd.c -o obj/icds/global-vars-icd.o

REM Link everything together
echo Linking...
gcc obj/*.o obj/utils/*.o obj/icds/*.o -o ..\binaries\obs-compiler.exe

if %ERRORLEVEL% EQU 0 (
    echo Build successful! Binary created at ..\binaries\obs-compiler.exe
) else (
    echo Build failed!
)

REM Clean up object files
echo Cleaning up...
del /Q obj\*.o
del /Q obj\utils\*.o
del /Q obj\icds\*.o
rmdir obj\utils
rmdir obj\icds
rmdir obj

echo Done.
