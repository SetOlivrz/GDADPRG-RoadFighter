## Visual Studio 2019
1. Download VS 2019 from [here](https://visualstudio.microsoft.com/downloads/)
2. Select Desktop development with C++
3. Use this repository when selecting `Clone a repository`

## Project properties Setup:
1. Downloads SFML from [here](https://www.sfml-dev.org/download.php) or get from the folder both sfml and rapidjson
2. Put the `SFML-2.5.1` and 'rapidjson-1.1.0' directory in C:\ or any other folder as long as you change the path in the following path accordingly. 
3. In *`C/C++`->`General`->`Additional Include Directories`* paste this: `C:\SFML-2.5.1\include;%(AdditionalIncludeDirectories)`
4. In *`C/C++`->`Preprocessor`->`Preprocesor Definitions`* paste this: `SFML_STATIC;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)`
   - For release use this: `SFML_STATIC;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)`
6. In *`Linker`->`General`->`Additional Library Directories` paste this: `C:\SFML-2.5.1\lib;%(AdditionalLibraryirectories)`
7. In *`Linker`->`Input`->`Additional Dependencies` paste this: `winmm.lib;opengl32.lib;freetype.lib;sfml-graphics-s-d.lib;sfml-window-s-d.lib;sfml-system-s-d.lib;%(AdditionalDependencies)`
   - For release use this: `winmm.lib;opengl32.lib;freetype.lib;sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;%(AdditionalDependencies)`
8.
