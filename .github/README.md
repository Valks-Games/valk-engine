# Configuration
In case for some reason the configuration gets undone for whatever reason, it has all been shown here.

## CodeBlocks
Download [CodeBlocks with MinGW 32 Bit Binaries](http://www.codeblocks.org/downloads/)

Make sure the compiler is linked to MinGW under Settings > Compiler > Toolchain Exectuables > Compiler's Installation Directory

Make sure MinGW is indeed 32 bit. Go to the bin directory of MinGW and type `gcc --version`. (If you see `x86_64` then it is 64 bit)

### Build Options
Link Libraries
```
(provide full file path) glew32s.lib
(provide full file path) libglfw3.a
opengl32
User32
Gdi32
Shell32
```

Compiler
```
..\Dependencies\GLFW\include\
..\Dependencies\GLEW\include\
```

Linker
```
..\Dependencies\GLEW\lib\Release\Win32\
..\Dependencies\GLFW\lib\
```

### Compiler Notes
Note that if you see `__debugbreak();` it should instead be `__builtin_trap;`.  
Note that if a function is both a friend and static, declare the static method outside of the class and a copy of method with the friend modifier in the class.  

## Visual Studio
Note that Visual Studio has been prone to crash alot (at least for me) and that is why I have transitioned to CodeBlocks.

Make sure the project is using `x86`  
Following settings should apply for `All Configurations` and `All Platforms`.

Additional Include Directories
```
$(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include;%(AdditionalIncludeDirectories)
```

Additional Library Dependencies
```
$(SolutionDir)Dependencies\GLEW\lib\Release\Win32;$(SolutionDir)Dependencies\GLFW\lib-vc2019
```

Additional Dependencies
```
glew32s.lib;glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib;
```

### Compiler Notes
Note that if you see `__builtin_trap;` it should instead be `__debugbreak();`.  
Note that Visual Studio allows you to declare functions as both friend and static.  

## Reference
https://www.opengl.org  
http://docs.gl  
http://glew.sourceforge.net  
https://www.glfw.org  
