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
