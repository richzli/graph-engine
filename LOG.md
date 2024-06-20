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
- The app will render a [scene](src/scene.cpp).
- The scene will manage [components](src/components/). Components will be basic drawable primitives: rectangles, circles, curves. Most of the program logic should go into the scene.

Some good resources I referenced:
- [LearnOpenGL](https://learnopengl.com/Getting-started/Hello-Triangle), which is a pretty classic resource for learning OpenGL. Also, the [GLFW Getting Started guide](https://www.glfw.org/docs/3.3/quick.html) was useful as well.
- [GLFW OpenGL Base](https://github.com/BonusPlay/GLFW-OpenGL-Base/tree/master), a repo I found that sets up a basic GLFW and OpenGL project. I found it useful for figuring out how to set up my shaders and filestructure in general.
- [Motion Canvas](https://github.com/motion-canvas/motion-canvas/tree/main), a vector graphics animation library.
- [Model View Projection](https://jsantell.com/model-view-projection/), a nicely-animated article about model-view-projection matrices.

### Initializing shaders and components

Since this project is pretty much me experimenting with graphics programming, of course I'm going to be implementing some shader shenaniganery. Accordingly, each component (just [circle](src/components/circle.cpp), [line](src/components/line.cpp), and [arrow](src/components/arrow.cpp) right now) has a dedicated [shader program](resources/shaders).

The main issue is that I can't compile the shaders without initializing GLFW first, so we can't define them in-line along with the class. Thus, [src/components/core.cpp](src/components/core.cpp) defines functions that compile the shader programs, which are called in `app::init_opengl()`. (Since we have to reassign them, the shader programs can't be `const`... which is not the best, but it's the simplest workaround I have at the moment. Will probably change this later by adding more functionality to `shader`.)

A similar problem arises when creating the default components, so that happens here, as well. <u>Currently, each component has its own VAO and VBO</u>, which *definitely* does not scale and should be changed later, but even if I coalesced everything, I would still need to initialize the VAO's/VBO's in a similar manner.

## Graphs

Instead of the scene managing components directly, I decided to add in one final layer of abstraction, the [graph](src/engine/graph/graph.cpp). This is because ideally there should be a fair amount of logic as a graph is rendered and algorithms are run, so making dedicated objects for [nodes](src/engine/graph/node.cpp) and [edges](src/engine/graph/edge.cpp) seemed like the right choice.

These objects can hold data (vertex/edge weights) and keep track of the relevant connections. The implementation is quite barebones, with the only notable thing being that edges should always stay attached to their endpoints, so some component management needs to be done there.

### Interactability

Obviously, the user should be able to drag objects around with their mouse. How do we tie this into the existing implementation?

- The *app* handles the raw inputs with GLFW callbacks,
- which are passed to the *scene* in the form of *select* and *drag* events,
- and each *component* has *hit* and *drag* functions which deal with hitbox detection and per-frame mouse movement, respectively.

Along with the endpoint updating mentioned above, this allows us to spawn in a graph with draggable points attached.

### Other unrelated technical notes

I switched my MinGW to a 64-bit version. Also, `glad.c` is excluded from the .gitignore now, which will probably help with first-time setup.

Also, (0, 0) is now the center of the screen, rather than the bottom left corner. Orientation stays unchanged.