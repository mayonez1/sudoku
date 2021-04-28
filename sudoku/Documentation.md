#### Project designed and developed by Bryson Weeks and Henry Sartor for Baylor CSI 1430

# Documentation

## ///PART 0 - Compilation, the Makefile, and Command-Line Arguments///

### Compilation and the Makefile

<p>
If you're using Linux, BSD, MACOS, or some other UNIX-like with support for make, the use of sudoku/Makefile.mk is highly reccommended. Alternatively, you could also use the precompiled binary that comes included in the download, under sudoku/bin, and run the program directly. If you're on Windows however, you will have to compile from source. All header files/includes (.hpp files) can be found under sudoku/include, and all source code (.cpp files) can be found under sudoku/src. Additionally, all of the .d files under sudoku/obj should give you a good amount of information on what is specifically required to compile each object. A D compiler could also hypothetically be used to expedite this process, however, it has not been tested.
</p>

### Command-Line Arguments

<p>
The program accepts 2 command line arguments, delimited by -f and -a. Using -f and then typing a filename or filepath allows you to use a settings file other than the one at sudoku/settings/settings.txt. Naturally, the new file used should follow the same formatting as the original settings file, with the filepath to the save of the editable grid on the first line, the filepath to the save of the completed grid on the second line, and a difficulty value ranging from 1-60 on the 3rd line. Using -a and then typing 0 or 1, allows you to toggle off/on ANSI colours, formatting, and escape codes (with 0 being off and 1 being on). By default, whether ANSI is on or off is dependant on your operating system. If you are using Linux, MACOSX, BSD, Cygwin, or any Unix-like, ANSI will be enabled, otherwise ANSI is disabled by default (this includes Windows). The use of ANSI is highly reccomended as it makes the UX significantly better, so you should make sure to enable it if your machine completely supports it.
</p>

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

- completePath - a string that tells the program where it should be saving the .sudk files of the completed/filled in grids.

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

<code>std::ofstream& operator<<(std::ofstream& file, SUDK::settings& set);</code> (Overloaded ofstream << operator using SUDK::settings):

<p>Responsible for writing the user edited settings to the settings.txt file.</p>

## ///PART 2 - The Square Class///

### Variables

<p>

- <code>SUDK::grd grid</code> - this is the main sudoku grid for the class. This is what is getting displayed when Square::display() is called
and is what will be getting modified by the user using the menu class.

- <code>SUDK::grd compGrid</code> - this is the completed/filled in grid that the main, user-edited grid is checked against.

- <code>SUDK::point p</code> - a dummy point used when the Square class constructor is called.

- <code>int skill</code> - determines how hard the final puzzle will be, and is used in <code>Square::format()</code> to determine how many values should be removed from the grid.

- <code>std::string savePath</code> - the filepath where the program saves and loads to, used in <code>Square::save()</code> and <code>Square::load()</code>.

- <code>std::string compPath</code> - the filepath where the program saves and loads the completed grids to

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

- <code>void checkUserSquare(bool)</code> - checks the user edited grid against the completed grid and tells the user if their guess is correct or incorrect.

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

- <code>void init(int, std::string, std::string)</code> - not a constructor, however, I put it in the same category because it's also responsible for initialising the Square class. This function sets int skill, std::string savePath, and std::string compPath to the parameters passed in, in that order.

</p>

### Accessors

<p>

- <code>SUDK::grd getGrid() const</code> - accessor function that returns grid.

- <code>SUDK::grd getCompGrid() const</code> - accessor function that returns the completed grid.

</p>

### Mutators

<p>

- <code>void setGrid(SUDK::grd)</code> - sets grid equal to the parameter passed in.

- <code>void setCompGrid(SUDK::grd)</code> - sets compGrid equal to the parameter passed in.

</p>

## ///PART 3 - The GLOBAL namespace and functions///

### Preprocessor Functions

<p>

- <code>const char* getOS()</code> - returns the OS the user is running. Determines whether ANSI is enabled or disabled by default, and as it is a pre-processor derivative it is determined when the code is compiled, not when it is run.

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

## ///PART 4 - Menu Class///

### Menu_noANSI class

<p>

Completely the same as the normal Menu class, except without the ANSI formatting that the normal Menu class uses.

</p>

### Variables

<p>

- <code>enum screen {none, main, settings, grid, difficulty}</code> and <code>screen currentScreen</code> - tells the program what screen it's currently on so <code>Menu::getCommand(std::ostream&)</code> can react accordingly.

- <code>std::string settingsFilePath</code> - tells the program the filepath to the settings.txt file, so the user can make changes to it from within the program.

- <code>Square mainSquare</code> - the main square that will be used and worked in by the user.

- <code>bool hints</code> - tells whether or not hints have been toggled by the user, false by default.

- <code>SUDK::settings newSettings</code> - the settings file that is changed by the user, and what will be written to the settings file when the user makes a change.

</p>

### Constructors 

<p>

- <code>Menu::Menu()</code> - Menu class default constructor.

- <code> void Menu::init(std::string, Square)</code> - again, technically not a constructor, but responsible for initialising the menu class. The first parameter sets the settingsFilePath, and the second parameter sets the mainSquare.

</p>

### Private Interaction Functions

<p>

- <code>void Menu::getCommand()</code> and <code>void Menu::getCommand(bool)</code> - prompts the user for a command, and gets the command in the form of a char via cin. The optional boolean parameter tells the program to toggle the prompt on/off.

- <code>void Menu::doCommand(char)</code> - Executes the command that was recieved by getCommand.

- <code>void Menu::editGrid()</code> - Allows the user to edit the grid in mainSquare.

</p>

### Display Functions

<p>

- <code>void Menu::showMain()</code> - prints the main menu, and waits for a command.

- <code>void Menu::showSettings()</code> - prints the settings menu, and waits for a command.

- <code>void Menu::Difficulty()</code> - prints the difficulty menu, and waits for a command.

- <code>void Menu::showGridScreen()</code> - responsible for refreshing and updating the program when the user has changed a value in the grid. Basically, prints the grid screen and waits for a command.

</p>