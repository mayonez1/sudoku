# Documentation

## ///PART 0 - Compilation and the makefile///

### Compilation

<p>Using the makefile is reccomended and it uses g++ as the compiler, if you don't have/don't want to use g++ or the makefile you will have to compile manually.
(Note that the makefile uses Linux terminal syntax and commands, so you may be unable to compile using the makefile if you don't have Linux or a Linux shell)
The project is not really large enough to warrant using precompiled headers and I also don't really like precompiled headers,
so there are none of those. To compile manually, firstly, you should compile main.cpp into an object file using square.hpp, which (for now) is it's only dependency.
Next, compile square.cpp into an object file using square.hpp, types.hpp, and global.hpp (in that order).
Then compile types.cpp into an object file using types.hpp, and global.cpp into an objct file using global.hpp (respectively).
Finally compile the main binary using main.o, square.o, types.o, and global.o (in that order). (Note: you can still do this, however, I've included compiled object files and the binary executable under sudoku/obj and sudoku/bin respectively).</p>

### The Makefile

<p>The makefile for this project is called Makefile.mk and can be found under the sudoku folder.
If you want to compile using the makefile (which is reccommended) cd into the directory where you've saved the source folder,
(<code>cd /your_file_path/sudoku/</code>), then enter the command <code>make -f Makefile.mk all</code> into your terminal.
If you want to remove all object files/binaries you can enetr the command <code>make -f Makefile.mk clean</code> (note: this will remove all files with the .o extension in that folder).</p>

## ///PART 1 - Types, Operators, and Exceptions///

### Types
<p>Currently, the program uses three custom types (defined in types.hpp) - the point type, the grd type, and the settings type. All of these are under namespace SUDK.</p>

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

**settings Type:**

<p>The settings type contains two variables:

- savePath - a string that tells the location to where the program should be saving the .sudk files.

- skill - an int that tells the program how many values to remove when the <code>Square::format()</code> function is run. In other words, it determines how hard the end puzzle will be.

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

<code>std::ifstream& operator>>(std::ifstream& file, SUDK::settings& set)</code> (Overloaded ifstream >> operator using SUDK::settings):

<p>Responsible for interpreting and taking in data from the settings.txt file, and putting it into an SUDK::settings variable.</p>

### Future Additions

<p>In the future, new types and exceptions and operators may be added if they're necessary
for the menu class/any other additions that may be made.</p>

## ///PART 2 - The Square Class///

### Variables

<p>

- <code>SUDK::grd grid</code> - this is the main sudoku grid for the class. This is what is getting displayed when Square::display() is called
and is what will be getting modified by the user using the menu class.

- <code>SUDK::point p</code> - a dummy point used when the Square class constructor is called.

- <code>int skill</code> - determines how hard the final puzzle will be, and is used in <code>Square::format()</code> to determine how many values should be removed from the grid.

- <code>std::string savePath</code> - the filepath where the program saves and loads to, used in <code>Square::save()</code> and <code>Square::load()</code>.

</p>

### Loading/Saving Functions

<p>

- <code>void load()</code> - called when loading a grid from a .sudk file. The program loads to the filepath in the savePath variable.

- <code>void save()</code> - called when saving a grid to a .sudk file. The program saves to the filepath in the savePath variable. Currently, the program will overwrite whatever file is at that path, however, this may change in later versions.

- <code>SUDK::grd readSUDK(std::string)</code> - function responsible for reading the SUDK file, contains error handling using the exceptions mentioned in part 1,
and is called whenever load() or load(std::string) is called. The std::string parameter is the filepath, and is passed directly from the load parameter.
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

- <code>void format()</code> - responsible for formatting the sudoku grid based on the skill variable. skill represents how
many symmetrical pairs of points will be taken out at random. By default the skill is 12, so therefore 24 numbers will be missing from the grid when called.
If the number is removed canModify will be set to true for that point.

</p>

### Constructors

<p>

- <code>Square()</code> - default Square class constructor fills the grid variable with 9 vectors of 9 points
where val is set to '0', canModify and modified set to false, and row and col set according to the point's loaction in the vector.

- <code>void init(int, std::string)</code> - not a constructor, however, I put it in the same category because it's also responsible for initialising the Square class. This function sets int skill, and std::string savePath to the parameters passed in.

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
This section is currently empty
</p>

### Future Additions

<p>
In the future, functions will likely be added that utilize some sort of data from the upcoming menu class.
Additionally, some functions may be made public in order to better utilize this menu class data.
The logic determining which function to call based on menu class data/user inputs will be handled by the
sriver.cpp driver.
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

### Fetching Functions

<p>

- <code>SUDK::settings fetchSettings(std::string)</code> - Gets data from the settings file located at the path passed in as std::string and returns the data as an SUDK::settings variable.

</p>

## ///PART 4 - Menu Class - WIP///

### Variables

<p>

- <code>enum screen {none, main, settings, grid, commands}</code> and <code>screen currentScreen</code> - tells the program what screen it's currently on so <code>Menu::getCommand(std::ostream&)</code> can react accordingly.

- <code>std::string settingsFilePath</code> - tells the program the filepath to the settings.txt file, so the user can make changes to it from within the program.

</p>

### Constructors 

<p>

- <code>Menu::Menu()</code> - Menu class default constructor.

- <code> void Menu::init(std::string)</code> - again, technically not a constructor, but responsible for initialising the menu class. The parameter, std::string will set the settingsFilePath variable.

</p>

### Private Interaction Functions

<p>

- <code>char Menu::getCommand(std::ostream&)</code> - prompts the user for a command, and gets the command in the form of a char via cin.

- <code>void Menu::doCommand(char)</code> - Executes the command that was recieved by getCommand.

</p>

### Public Interaction Functions

<p>

- <code>void Menu::editGrid(SUDK::grd&)</code> - allows the user to edit and make changes to the grid that is passed by reference.

</p>

### Display Functions

<p>

- <code>void Menu::showMain(std::ostream&) const</code> - prints the main menu to the desired ostream.

- <code>void Menu::showSettings(std::ostream&) const</code> - prints the settings menu to the desired ostream.

- <code>void Menu::showCommands(std::ostream&) const</code> - prints the commands menu to the desired ostream.

</p>

## ///PART 5 - driver.cpp - WIP///

### Arguments

<p>Currently, the user is able to use one argument in the command line to specify the location of the settings.txt file. An example of the argument in use would look something like this: <code>sudoku /path_to_settings/settings.txt</code>. If no argument is used the program will assume the settings.txt file is located at bin/settings/settings.txt. If more that one argument is used, then the program will use only the first argument.</p>

### Future Additions

<p>In the future, I would like to add support for a second command line argument that allows the user to choose a desired ostream, for example: <code>sudoku /path_to_settings/settings.txt cout</code> where cout is the desired ostream.