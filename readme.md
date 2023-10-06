# OpenGLFramework

This is a framework for working with opengl. The framework provides a library called **MyGL** which has the following features:

- Abstract OpenGL classes: [VertexBuffer](MyGL/VertexBuffer.h), [VertexArray](MyGL/VertexArray.h), [ElementBuffer](MyGL/ElementBuffer.h), [Shader](MyGL/Shader.h), [Shader](MyGL/Shader.h), [Texture](MyGL/Texture.h)
- Additional classes: [Camera](MyGL/Camera.h), [Model](MyGL/Model.h), [Mesh](MyGL/Mesh.h)

The Model class can load most models from files common 3d model files, and draw them with their assigned textures. However it does not work with colors that are stored inside vertices yet.

## Building
The framework has only been tested with MSVC as compiler (Visual Studio). When using any other compiler, you may have to modify the [CMakeLists.txt](CMakeLists.txt) file.
### Dependencies
The project uses submodules to manage dependencies. Make sure to clone them as well when cloning the project.
Additionally, you have the option to use a custom glad version. Currently this project is using [glad](dependencies/GLAD/include/glad/glad.h) for **opengl 4.6**. If you want to use a different version, you can replace the glad folder with a different version, using this site: [https://glad.dav1d.de](https://glad.dav1d.de) . The glad folder should contain an ```include``` folder and a ```src``` folder containig the glad.c file

### CMake 
The framework is built using cmake. The following commands can be used to build the framework:

```bash
cmake .
make
```

Make sure to move the generated dll files to the same folder as the executable.
