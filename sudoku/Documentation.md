# Documentation

## ///PART 0 - Compilation and the makefile///

### Compilation

<p>Using the makefile is reccomended and it uses g++ as the compiler, if you don't have/don't want to use g++ or the makefile you will have to compile manually.
(Note that the makefile uses Linux terminal syntax and commands, so you may be unable to compile using the makefile if you don't have Linux or a Linux shell)
The project is not really large enough to warrant using precompiled headers and I also don't really like precompiled headers,
so there are none of those. To compile manually, firstly, you should compile main.cpp into an object file using square.hpp, which (for now) is it's only dependency.
Next, compile square.cpp into an object file using square.hpp, types.hpp, and global.hpp (in that order).
Then compile types.cpp into an object file using types.hpp, and global.cpp into an objct file using global.hpp (respectively).
Finally compile the main binary using main.o, square.o, types.o, and global.o (in that order).</p>

### The Makefile

<p>The makefile for this project is called Makefile.mk and can be found under the sudoku folder.
If you want to compile using the makefile (which is reccommended) cd into the directory where you've saved the source folder,
(<code>cd /your_file_path/sudoku/</code>), then enter the command <code>make -f Makefile.mk all</code> into your terminal.
If you want to remove all object files/binaries you can enetr the command <code>make -f Makefile.mk clean</code> (note: this will remove all files with the .o extension in that folder).</p>

## ///PART 1 - Types, Operators, and Exceptions///

### Types
<p>Currently, the program uses two custom types (defined in types.hpp) - the point type, and the grd type. Both of these are under namespace SUDK.</p>

**point Type:**

<p>The point type (called using SUDK::point) is the data type for a point in the sudoku grid. Each point contains 5 variables:

- val - a char that represents what is actually at the point in the grid, and should contain characters with ASCII values 48 - 57 (characters 0-9),
where a '0' character represents a space. However, any character can techincally be a point value, so you could have the character 'a' as a point value
for example, though it just wouldn't make sense in terms of playing sudoku, and the only way this can be achieved is if the .sudk file is edited.

- canModify - a bool that tells the program if this point can be modified. If the point can be modified the program will show this by printing an asterisk (*)
next to the point value when Square::display() is called.

- modified - a bool that tells the program if the point has been modified.

- row - an int that tells the program what row this point belongs on.

- col - an int that tells the program what column this point belongs on.

</p>

**grd Type:**

<p>The grd type (called using SUDK::grd) is the data type for the sudoku grid. It is a 2-Dimensional vector of points.</p>

### Exceptions

<p>

*SUDK Exceptions (under namespace SUDK):*


- bad_marker - thrown when reading the .sudk file if the marker (see SUDK_Documentation) is invalid.

- malformed_block - thrown when reading the .sudk file if the block does not begin with '{' or end with '}'.

- bad_start - thrown when reading .sudk file if the file does not begin with the #START command

- out_of_range - thrown when reading the .sudk file if the row or column value is greater than 8 or less than 0

- invalid_bool - thrown when reading the .sudk file if the canModify or modified value is not a 1 or 0

- bad_read - thrown in the Square::readSUDK function if any error is thrown while reading

- bad_file - thrown in the Square::readSUDK function if the file that the user has tried to open is not a .sudk file or does not exist

</p>

<p>

*GLOBAL Exceptions (under namespace GLOBAL):*

- mod_by_0 - thrown when the program tries to modulus by 0, specifically in the randomNum function when amount is passed in as 0.

</p>

### Operators

<code>std::ifstream& operator>>(std::ifstream&, SUDK::grd&)</code> (Overloaded ifstream >> operator using SUDK::grd):

<p>Responsible for interpreting/parsing the data from an ifstream (in this case, a .sudk file specifically) and putting that data into an SUDK::grd.
This is the operator that is responsible for doing 90% of the work when Square::load() or Sqaure::readSUDK are called, and allows the program to
get usable data from .sudk files.</p>

### Future Additions

<p>In the future, new types and exceptions and operators may be added if they're necessary
for the menu class/any other additions that may be made.</p>

## ///PART 2 - The Square Class///

### Variables

<p>

- <code>SUDK::grd grid</code> - this is the main sudoku grid for the class. This is what is getting displayed when Square::display() is called
and is what will be getting modified by the user using the menu class.

- <code>SUDK::point p</code> - a dummy point used when the Square class constructor is called.

</p>

### Loading/Saving Functions

<p>

- <code>void load()</code> and <code>void load(std::string)</code> - called when loading a grid from a .sudk file, the optional std::string parameter is the filepath,
if this is left blank the default filepath is sudoku.sudk and will be saved to the directory the user runs the program from.

- <code>void save()</code> and <code>void save(std::string)</code> - called when saving a grid to a .sudk file. The optional std::string parameter is the filepath to where the
file is being saved. Like load(), the default filepath is sudoku.sudk in the directory that the user has run the program from. If a file already exists at
the filepath, it will be overwritten.

- <code>SUDK::grd readSUDK(std::string)</code> - function responsible for reading the SUDK file, contains error handling using the exceptions mentioned in part 1,
and is called whenever load() or load(std::string) is called. The std::string parameter is the filepath, and is passed directly from the load parameter.
If load is called without a parameter, "sudoku.sudk" is used as a parameter instead.

</p>

### Checking Functions

<p>

*(For more information on the logic of these functions and how the alogorithm actually works, refer to generation_algorithim.txt)*

- <code>bool checkCell(char num, int row, int col, SUDK::grd grid) const</code> - checks if num is unique in a 3x3 cell. Determines which cell num belongs to
using row and col parameters. Returns true if it is unique, false otherwise.

- <code>bool checkCol(char num, int col, SUDK::grd grid) const</code> - checks if num is unique in the column. Returns true if it is unique, false otherwise.

- <code>bool checkRow(char num, int row, SUDK::grd grid) const</code> - checks if num is unique in the row. Returns true if it is unique, false otherwise.

- <code>bool check(char num, int row, int col, SUDK::grd grid) const</code> - runs all 3 checking functions (checkCell, checkRow, checkCol) and return true if
they all return true, false otherwise. This function essentially exists so that I can just call 1 check function in the create() function.

</p>

### Generation Functions

<p>

*(For more information on the logic of these functions and how the alogorithm actually works, refer to generation_algorithim.txt)*

- <code>void replenish(vector<char>&)</code> - responsible for replenishing the character vector assigned to each point with characters 1-9 (ASCII 49 - 57).

- <code>void create()</code> - responsible for doing everything to create a complete sudoku grid (refer to generation_algorithim.txt for more details).

- <code>void format() and void format(int)</code> - responsible for formatting the sudoku grid based on the optional int parameter difficulty. Difficulty represents how
many symmetrical pairs of points will be taken out at random. By default the difficulty is 12, so therefore 24 numbers will be missing from the grid when called.
If the number is removed canModify will be set to true for that point.

</p>

<p>

*I went on a bit of a tangent here, and this is explaining why the format() functions work the way they do*

Currently format() and format(int) will only generate symmetrical sudoku puzzles, the reason for this is so that I don't have to recursively check whether or not
the puzzle is solvable, because all symmetrical puzzles are by nature solvable. This also means that difficulty does not have to be determined post-formatting and then
checked against the value that was passed in. Using symmetrical puzzles allows for an objective standard of difficulty based on the amount of numbers missing from the formatted
puzzle. This may change in the future, however, to make a non-symmetrical puzzle, and then have the computer solve it, assign a difficulty rating to it, and then re-evaluate the
formatting based on the comparison between the difficulty that was passed in would not only increase waiting time for the user, but it would also likely require some amount of machine
learning, which is outside the subject area of this class, and outside my skillset as a programmer. To clarify, when I say solvable, I mean solvable using logical deduction.
Technically, any sudoku puzzle is solvable if you were to just guess luckily enough, however, this defeats the purpose of soing sudoku in the first place, and so any puzzle that
requires a significant amount of guessing to solve is deemed to be un-solvable. Additionally, this is the reason machine learnig would need to be implemented in order to determine
not only to get an accurate difficulty rating for the formatted puzzle, but to also determine if it is solvable by the standards I mentioned previously. Because if I were to say,
just modify the checking functions in order to make a hypothetical 'bool solvable()' function, I would have to rely on an algorithm that used some sort of brute force or guess and check
like my create() function does. As a result, I think it's best to just generate symmetrical sudoku puzzles and call it a day. Of course a way around this could be using a web scraper to fetch
pre-made puzzles, making some puzzles myself, or using a library that implements the machine learning that I was referring to before, however I feel that this sort of defeats the
entire purpose of the project. One final solution could be to generate random unfinished sudoku puzzles and then determine if they're solvable during generation, however, 
generation would take significantly longer this way (with the only way to speed it up using some level of machine learning), and determining an accurate difficulty would still require machine
learning. So, in conclusion, while I could easily give each puzzle generated more variablilty by not using symmetrical pairs, I think it's best I do it this way so that
I can implement a difficulty system, and ensure that all functions are solvable, however, if I get bored and have some time on my hands, this may change.

</p>

### Constructors

<p>

- <code>Square()</code> - default Square class constructor fills the grid variable with 9 vectors of 9 points
where val is set to '0', canModify and modified set to false, and row and col set according to the point's loaction in the vector.

</p>

### Accessors

<p>

- <code>SUDK::grd getGrid() const</code> - accessor function that returns grid.

</p>

### Mutators

<p>

- <code>void setGrid(SUDK::grd)</code> - sets grid equal to the parameter passed in.

</p>

### Wrappers/Executors

<p>

- <code>void testRun()</code> - run function used for testing/debugging purposes.

</p>

### Future Additions

<p>
In the future, functions will likely be added that utilize some sort of data from the upcoming menu class.
Additionally, some functions may be made public in order to better utilize this menu class data.
The logic determining which function to call based on menu class data/user inputs will be handled by the
main.cpp driver.
</p>

## ///PART 3 - The GLOBAL namespace and functions///

### Preprocessor Functions

<p>

- <code>const char* getOS()</code> - returns the OS the machine is running on in the form of a string literal.
It has returns for Linux, 32 Bit Windows, 64 Bit Windows, OSX, and Unix. If it encounters anything else
it will return "Other". The function uses macros and the g++ OS tags to determine the OS. I'm pretty sure it will
return "UNIX" on machines running BSD or on some older PowerPC Macintosh computers, but I'm not entirely sure. And I
literally have no clue what it will return for POSIX based systems (as in I'm not sure if it will return "UNIX" or "OTHER").
Currently, this function is not being utilised, however, it may be used in the future, to, for example, make a apecific sudoku saves
directory under the documents folder or something like that. Additionally, if I ever decided to implement a GUI or multithreading,
this would give me compatibility across platforms, and allow my program to run on non linux (or even non x86) machines.

</p>

### Random Functions

<p>

- <code>void randomNum(unsigned int&, unsigned int)</code> and <code>void randomNum(unsigned int&, unsigned long, unsigned int)</code> - 
these functions randomize the first parameter, based on the second parameter (the amount), and the third, optional parameter (the seed).
The second parameter - amount determines what the rand() will be modulused by. The third parameter is the seed, and it's optional.
If a third parameter is not used time(0) will be used to seed rand(). These functions also contain error handling, and will throw the
mod_by_0 exception if the second parameter or the amount passed in is less than or equal to zero.

<code>void _seed(unsigned int&)</code> and <code>void _seed(unsigned int&, unsigned int)</code> - These functions, like the ones above randomize the number passed in as
the first parameter. These two functions, however, don't use amount as a parameter, and are intended to make the number into a seed that can be used
to seed rand() in some other function. The second, optional, parameter is the seed. By default, the function will seed rand() with time(0) and then set
the number passed in as the first parameter equal to rand(). If a second parameter is passed, however, the function will seed rand() with the second parameter.

</p>

## ///PART 4 - Menu Class///

**WIP**

## ///PART 5 - Driver/main.cpp///

**WIP**