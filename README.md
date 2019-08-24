# CSpec

## Description
A spec framework for C++ modeled after RSpec & Protractor. The syntax it is very similar (Describe, Context, It, BeforeEach, AfterEach) so it shouldn't be too hard to use if you have experience with those languages. I am just sorta winging this so it's gonna have a very haphazard development process until I get a moment to focus. Currently no documentation aside from what's in the examples directory, but that really showcases all that it's currently capable of.

## Usage
- Download/Clone the repo
- Run the libcspec.a makefile target, which should be the default one anyway
- Move the produced static library into whatever project you want to run tests for
- Add CSpec's include directory to your project's include path
- Write specs (examples provided in given directory)
- When it comes to compiling, main() is already in the static lib so you have to exclude your main() from your spec build process
- Run your produced executable

## Why this exists
I developed it for personal use because I didn't like Google Test and am far more used to RSpec.

## How it works
Self executing lambdas before main. Considered taboo by some but eh it works so I'm not complaining. BeginSpec(spec_name) actually defines a variable that holds the result of the lambda. BeginSpec() also ends with the open brace of the lambda so everything in between that and EndSpec is the body of the lambda. Also across the whole project spec_name must be unique otherwise you'll get errors similar to what would happen if you tried to define the same variable twice. A good strategy would be to follow the naming convention of include guards per spec file.

Far from complete, but better than nothing.
