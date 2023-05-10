# LLVM Project mod for LLVM course in MIPT
 
Added target **MySimulator** for self-made simulator with graphics support
 
## Build
 
**⚠️WARNING!⚠️** If LLVM is built by Windows 10 Pro, Visual Studio 17 2022, you should have almost ❗78-80 GB❗ space on disk available
 
	# Download repository
	git clone https://github.com/BiscuitsLayer/llvm-project-mod.git
	cd llvm-project-mod
 
	# Create build directory
	mkdir build
	cd build
 
	# Build
	cmake ..\ -S ..\llvm -B ./ -DLLVM_ENABLE_PROJECTS="clang" -DCMAKE_INSTALL_PREFIX=../install/ -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=On -DLLVM_TARGETS_TO_BUILD=X86 -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=MySimulator
	cmake --build . --parallel 8
 
This builds necessary LLVM subset and registers **x86** and **MySimulator** targets
 
*cwd: llvm-project\build*\
*LLVM built by: Windows 10 Pro, Visual Studio 17 2022*
 
	# Review targets
	.\Debug\bin\clang++.exe -print-targets
 
## Check
 
Check if everything is built correctly
 
*cwd: llvm-project\build*\
*LLVM built by: Windows 10 Pro, Visual Studio 17 2022*
 
	# Create directory with examples
	mkdir MySimulatorExamples
	cd MySimulatorExamples
 
Create an example C++ file **(main.cpp)**
 
```c
#include <stdio.h>
 
int factorial(int n) {
	if (n == 1) {
		return 1;
	}
	return factorial(n - 1) * n;
}
 
int main() {
	printf("%d", factorial(5));
	return 0;
}
```
 
	# Build and execute, check everything is fine
	..\Debug\bin\clang++.exe .\main.cpp -o main.exe
	.\main.exe
 
## MySimulator assembler check
 
Now let's check that assembler for MySimulator works correctly
 
*cwd: llvm-project\build\MySimulatorExamples*\
*LLVM built by: Windows 10 Pro, Visual Studio 17 2022*
 
Create an example C++ file for MySimulator target (my_simulator_main.cpp)
We have to return final result in main function, because **includes**, and therefore functions like **printf** are not supported
 
```c
int factorial(int n) {
    if (n == 1) {
        return 1;
    }
    return factorial(n - 1) * n;
}
 
int main() {
    return factorial(5);
}
```
 
	# Build and execute, check everything is fine
	..\Debug\bin\clang++.exe -target MySimulator .\my_simulator_main.cpp -S -o my_simulator_main.s
 
Produced output **(my_simulator_main.s)**
 
```nasm
	.text
	.file	"my_simulator_main.cpp"
	.globl	_Z9factoriali
	.type	_Z9factoriali,@function
_Z9factoriali:
	ADDi r2 r2 -16
	STi r1 r2 12
	STi r3 r2 8
	ADDi r3 r2 16
	STi r9 r3 -16
	LDi r4 r3 -16
	MOVli r9 1
	B.NE r4 r9 .LBB0_2
	B .LBB0_1
.LBB0_1:
	MOVli r4 1
	STi r4 r3 -12
	B .LBB0_3
.LBB0_2:
	LDi r4 r3 -16
	ADDi r9 r4 -1
	BL r1 _Z9factoriali
	LDi r4 r3 -16
	MUL r4 r9 r4
	STi r4 r3 -12
	B .LBB0_3
.LBB0_3:
	LDi r9 r3 -12
	LDi r3 r2 8
	LDi r1 r2 12
	ADDi r2 r2 16
	BR r1
.Lfunc_end0:
	.size	_Z9factoriali, .Lfunc_end0-_Z9factoriali
 
	.globl	main
	.type	main,@function
main:
	ADDi r2 r2 -12
	STi r1 r2 8
	STi r3 r2 4
	ADDi r3 r2 12
	MOVli r4 0
	STi r4 r3 -12
	MOVli r9 5
	BL r1 _Z9factoriali
	LDi r3 r2 4
	LDi r1 r2 8
	ADDi r2 r2 12
	BR r1
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
 
	.ident	"clang version 15.0.7 (https://github.com/BiscuitsLayer/llvm-project.git 3bef6d2329cda2d7b19cf5b5532316025f156619)"
	.section	".note.GNU-stack","",@progbits
```
 
Now this file is ready to be executed on our [self-made simulator](https://github.com/BiscuitsLayer/Scheme-Raytracer)!
