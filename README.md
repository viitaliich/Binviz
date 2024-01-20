# Files Binary Visualization

This implementation of Files Binary Visualisation is inspired by:
- Christopher Domas talk: https://www.youtube.com/watch?v=4bM3Gut1hIk
- Tsoding Daily video - Reverse Engineering Data Files: https://youtu.be/AUWxl0WdiNI?si=7xVg1Mnc2CtXbJnw

**stb** library is used in code: https://github.com/nothings/stb

## Explanation

The main idea of this project is to take a computationally difficult task, such as big file reverse engineering, and translate it to a problem our brains do naturally.

This became possible, since even in 'unstructured' data there is a structure.
Sequential bytes have an implicit relationship.

To see this hidden structure, all we need to do is to take sequential bytes of the file and translate them to coordinates on a 2D plane.

Different types of files have different patterns on a result image. 

Using these patterns, we can detect file type knowing nothing about it 🙂

## Examples





