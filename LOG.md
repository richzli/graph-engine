# log

Probably a good idea to note down what troubles I ran into, in case I need to do this setup in the future.

## Setting up the environment

- To install GLFW, I just downloaded it from [the site](https://www.glfw.org/download.html). GLFW version 3.3.8.
    - Make sure to use the right libraries! I incorrectly assumed my MinGW was 64-bit, but it's actually 32-bit. I thought it was a problem with the linker for the longest time, but everything resolved itself the moment I replaced the 64-bit libraries with 32-bit ones.
    - Furthermore, make sure to link the `gdi32` library. The [GLFW build guide](https://www.glfw.org/docs/3.3/build_guide.html) mentions this briefly, but it's not obvious at first glance.
- To install GLAD, I used [this tool](https://glad.dav1d.de/). GL version 3.3, and Core Profile.
    - Very important! I needed to put `src/glad.c` inside my project. It was a single phrase in [this resource](https://learnopengl.com/Getting-started/Creating-a-window), and I completely missed it.
- [GLM](https://github.com/g-truc/glm) is headers-only, so no libraries are needed. Version 0.9.9.9.
    - Not sure exactly, but something funky happened during the unpacking process and the incorrect headers for a few files (`common.hpp`, `integer.hpp`, `packing.hpp`, and `vector_relational.hpp`) got placed, causing include path errors. Fixed by just re-installing.

While debugging, I found that the commands `g++ -print-search-dirs` was helpful for listing all (default) library paths and `g++ -E -x c++ - -v` was helpful for listing all include paths.

## A basic render

I decided to set up the majority of the project structure, and get a simple square rendered on screen.
- The project consists of an [app](src/app.cpp), which manages the window. The event loop is in [main](src/main.cpp).
- The app will render a [scene](src/scene/scene.cpp).
- The scene will manage [components](src/components/). Components will be basic drawable primitives: rectangles, circles, curves. Most of the program logic should go into the scene.

Some good resources I referenced:
- [LearnOpenGL](https://learnopengl.com/Getting-started/Hello-Triangle), which is a pretty classic resource for learning OpenGL. Also, the [GLFW Getting Started guide](https://www.glfw.org/docs/3.3/quick.html) was useful as well.
- [GLFW OpenGL Base](https://github.com/BonusPlay/GLFW-OpenGL-Base/tree/master), a repo I found that sets up a basic GLFW and OpenGL project. I found it useful for figuring out how to set up my shaders and filestructure in general.
- [Motion Canvas](https://github.com/motion-canvas/motion-canvas/tree/main), a vector graphics animation library.
- [Model View Projection](https://jsantell.com/model-view-projection/), a nicely-animated article about model-view-projection matrices.