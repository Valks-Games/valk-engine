## Mingw
If using CodeBlocks / Mingw, make sure the following is done.
- Remove the `.lib` extensions from all linked libraries
- Change `glfw3.lib` to `libglfw.a` (Mingw compiler looks for `.a` files)
- Provide the full linking paths for `glew32s.lib` and `libglfw.a`
- Mingw is 32 bit (not 64 bit); note that 64 bit can appear as x86_64
- Instead of using `__debugbreak();` use `__builtin_trap;`
- If a function is both a friend and static, declare the static method outside of the class and a copy of method with the friend modifier in the class

## Configuration
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

## Reference
https://www.opengl.org  
http://docs.gl  
http://glew.sourceforge.net  
https://www.glfw.org  
