# Algunas notas para el trabajo
## Tutorial on how to make makefiles:

1. Create a file called `Makefile` in the same directory as your source code.
2. The first line of the file should be the following:
```
# This is a makefile
```

3. The next line should be the following:
```
.PHONY: all clean
```

This line tells make that the targets `all` and `clean` are not actual files, but rather special targets that perform certain tasks.

4. The `all` target is the default target. This means that if you run `make` without any arguments, make will build the target `all`.

5. The `clean` target is used to clean up the project. This typically involves removing all the compiled binaries and object files.

6. Now you can start adding rules to your makefile. A rule is an instruction for building one or more output files from one or more input files.

7. The general syntax of a rule is as follows:
```
target: prerequisites
commands
```
The `target` is the name of the output file. The `prerequisites` are the files that the output file depends on. The `commands` are the shell commands that are used to build the output file.

8. For example, the following rule builds the executable file `myprogram` from the source file `myprogram.c`:
```
myprogram: myprogram.c
gcc myprogram.c -o myprogram
```
9. You can also have multiple targets in a makefile. For example, the following makefile builds two executable files, `myprogram` and `mylibrary`:
```
myprogram: myprogram.c
gcc myprogram.c -o myprogram

mylibrary: mylibrary.c
gcc mylibrary.c -shared -o mylibrary.so
```

10. Once you have created your makefile, you can build your project by running the following command:
```
make
```
11. If you want to clean up your project, you can run the following command:
```
make clean
```
Here are some additional things to keep in mind when writing makefiles:

* The names of targets and prerequisites should be unique.
* The commands in a rule should be tab-indented, not space-indented.
* You can use variables in your makefile. For example, the following variable defines the compiler to be used:
```
CC = gcc
```
You can then use the `CC` variable in your rules, such as:
```
myprogram: myprogram.c
$(CC) myprogram.c -o myprogram
```

* You can also use functions in your makefile. Functions are a way to encapsulate commonly used code. For example, the following function defines a function called `clean` that removes all the compiled binaries and object files:
```
clean:
    rm -f *.o *.exe
```

You can then call the `clean` function in your makefile, such as:
```
.PHONY: all clean

all: myprogram

clean:
    $(call clean)
```

# Flags de Gcc
The flags in the CFLAGS variable in the makefile are:

- `Wall`: This flag enables all warnings.
- `Wextra`: This flag enables additional warnings that are not enabled by -Wall.
- `Werror`: This flag turns all warnings into errors.
- `std=c99`: This flag specifies that the C99 standard should be used.
- `pedantic`: This flag enables all warnings that are considered to be pedantic.
- `g`: This flag enables debugging information to be generated.

# Generation query (you.com)
Write for me a make file that when you run the command "make all", it compiles all main files contained inside the proyect. The proyect structure is this: the src folder which contains 4 folders, Cap1, Cap2, Cap3 and Cap4; inside every folder there are files called listing1.1 listing1.2, etc, every one being a main file by itself (the need to be compiled). For the Cap2 you have listing 2.1, etc, for Cap3 you have listing3.1 and so one. The output files have to be inside of a folder called "build" with the same structure as the src folder (Cap1 with its files, Cap2, etc)
