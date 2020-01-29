# CSpec

## Description

A spec framework for C++ modeled after RSpec & Protractor. The syntax it is very similar (Describe, Context, It, BeforeEach, AfterEach) so it shouldn't be too hard to use if you have experience with those frameworks. I am just sorta winging this so it's gonna have a very haphazard development process until I get a moment to focus. Currently no documentation aside from what's in the examples directory, but that really showcases all that it's currently capable of.

## Usage

- Download/Clone the repo
- Run make 
- Move the produced static library or shared object into whatever project you want to run tests for
- Add CSpec's include directory to your project's include path
- Write specs (examples provided in the 'examples' directory)
- When it comes to compiling, main() is already in the static lib & shared lib so you have to exclude your main() from your spec build process
  - An example of how to do that that would be to rename your main.cpp file to main.cxx and only compile cpp files
- Run the produced executable after compiling with the library of choice

## Global Helper Variables

- `ENV`  unordered\_map\<string, string\>: Contains all environment variables.
- `ARGV` vector\<string\>: Contains the arguments passed into the program.

## Why this exists

I developed it for personal use because I didn't like the complexity of Google Test and am far more used to RSpec.

## How it works

Despite myself hating on Google Test, I essentially copied their method. Eval(test) produces a class with the name of the test given using preprocessor macros. This class is instantiated and within its constructor it adds itself to a queue of tests. The braces following the Eval() function describe the body() function of this test, which is executed when it's that test's turn in the queue.

