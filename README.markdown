![alt text](https://github.com/xforns/kitxen-wars/raw/master/readme_img.png "")

This is the repository for Kitchen Wars. Bear in mind that this is stupidity at its fullest.

This project is a very basic shoot'em up game. It was developed in the year 2000 as the final project of my elementary school. In 2013, stumbled upon the hard disk containing this project and decided that I would revamp it and re-learn C++. Most of the codebase ended up using old C++ mixed with C++11 (ie, mixing the old POSIX threads with C++11 threads.. no good I guess), plus the STD iterators and all convenience functions it offers. I was tempted to use Boost, but due to a lack of knowledge and my desire of portability and ease of installation, I tried to stick to the bare minimum of code APIs.

There is still work to do, quite a lot only if my wish is to leave it stable and.. well, visually won't change that much, it's what I like the most! :)


## INSTALLATION

As of now, I can only assure it works under OSX. Next is *nix, which shouldn't be that much difficult if I create anoter Makefile. So feel free!

**Requirements**

- A GNU C/C++ compiler with support for C+11
- OpenGL libraries (that means GL, GLU and GLUT)

And that's it. I expect that everybody reading at this point knows how to install everything, or mangle the Makefile if it needs to.

**Installing**

- Open a terminal and go to the root of the **x86_64** folder and run **make**
- Then simply execute **./kitxen** or **sh kitxen**


## CONSIDERATIONS

- The game crashes, *a lot*. Try not to get too excited firing bullets. I'm using shared pointers like there is no tomorrow.. and it looks like I'm using them wrong ;) There are no unique pointers neither auto though.

- Add to it some - assumedly thread-safe - singletons, like the collision system..

- Also add to the mix the POSIX threading system...

- And a custom messaging system..

- And some dynamic casts..

- And you have a recipe for disaster ;)

- So, all in all, it needs refactoring, quite a bit.


## ToDo

- When I left the project in 2013, besides the entire unstability of the game, what essentially put me off was my inability to make GLEW run. Still today 1 year later, after re-taking the project again, I couldn't make it work. There are lots of problems under OSX, last ones being the conflict of redefinition of GLtypes by OSX and GLEW. In the GLEW bug tracking system looks like this issue has been solved (see [here](http://sourceforge.net/p/glew/bugs/206/)), but I may be missing something.
  The main reason to use GLEW is its providing interface for shaders. Note that I'm using OpenGL 2 functions (not totally sure though), and my aim was to learn GLSL 1, so as to apply transparency to the fully opaque BMP's in the GPU (yes, I used BMP's back in the day, mainly for simplicity in reading them).

- Since it seems it's a very daunting task, the goal is now to convert the BMP's to PNG's with transparency corresponding to the black areas, and that's it. So in the list of priorities adding shading support is last. It would be nice adding some particle systems only in the GPU.. but well, priorities!

- Second item and surely the most important: game stability, which means: avoid all crashes. And that will probably mean a deep refactor:

  - Stop using POSIX threads, and use STD threads (Boost?).

  - Review the singletons in use. Avoid them, if possible.

  - Review the misuse and convenience of shared pointers. Most crashes are references to chunks of memory that are not there anymore.

  - Improve the drawing mechanism. When 20 enemies are being shown at the same time, the FPS are ridiculous. Maybe shading would come in handy here.. plus other optimizations.

- Include the use of Boost, and a more extended use of STD.

- Review the collision mechanism (not working between enemies).

- Permit to exit the game..

- Add some more logic for the enemies.. which means some AI, at least a bit!



***

