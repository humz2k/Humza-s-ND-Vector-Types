# Humza's ND Vector Types

Dealing with different libraries nd vector types is annoying.
Some just use raw C arrays, some using structs, and I have been finding it very annoying to deal wih converting between them.
This is a thing to make that slightly less annoying.
You could just roll your own nd vector type for each project, but that is just extra work and I hate extra work.

This repository contains my single header vector type library, because there are not enough vector type libraries in the world (https://xkcd.com/927/).
Just copy and paste hqvec.hpp somewhere in your project and then include it.