# Linux-File-Explorer
 Fully functional File Explorer Application, with a restricted feature set.
 
# Prerequisites:
1. Basic usage and architectural know-how of file explorer features
2. Preliminaries such as C/C++ code compilation, execution & debugging.

# Requirements:
The File Explorer works in two modes -
### 1. Normal mode (default mode) - 
Used to explore the current directory and navigate the filesystem
### 2. Command mode - 
Used to enter shell commands

# Normal mode:
Normal mode is the default mode of the application. It has the following functionalities -
1. Displays a list of directories and files in the current folder
  - Every file in the directory is displayed on a new line with the following attributes for each file -
    *  **File Name**
    *  **File Size**
    *  **Ownership (user and group) and Permissions**
    *  **Last modified**
  - The file explorer shows entries **“.”** and **“..”** for current and parent directory respectively.
  - The file explorer handles scrolling in the case of vertical overflow using up and down arrow keys
2. Opens directory/file when enter key is pressed -
  - Directory - Clear the screen and navigate into the directory and show the directory contents as specified in point 1.
  - File - Open the file in nano editor.
3. Traversal
  - Go back - Left arrow key would take the user to the previously visited directory
  - Go forward - Right arrow key would take the user to the next directory
  - Up one level - Backspace key would take the user up one level
  - Home - h key would take the user to the user home directory 
# Command Mode:
The application would enter the Command button whenever “:” (colon) key is pressed. In the  command mode, the user would be able to enter different commands.
1. Copy File/Direrectory- ‘**copy <source_file(s)> <destination_directory>**’ 
> Eg - copy foo.txt bar.txt baz.mp4 ./foobar 
Move - ‘**move <source_file> <destination_directory>**’ 
> move foo.txt ./foobar 
Rename - ‘**rename <old_filename> <new_filename>**’
> rename foo.txt bar.txt
2. Create File - ‘**create_file <file_name> <destination_path>**’ 
Create Directory - ‘**create_dir <dir_name> <destination_path>**’ 
> Eg -create_file foo.txt ./foobar
> create_file foo.txt .
> create_dir foo ./foobar
3. Delete File - ‘**delete_file <file_path>**’ 
Delete Directory(recursive) - ‘**delete_dir <dir_path>**’
4. Goto -
> goto <directory_path>
6. Search - ‘**search <file_name>**’ or ‘**search <directory_name>**’
  - Searchs for a given file or folder under the current directory recursively.
  - Prints True or False depending on whether the file or folder exists.
7. Enter **switch** command, the application will go back to Normal Mode
8. On pressing **q** key, the application will close.
9. Enter **clear** to clear the command mode screen.
 
## Useful References to learn
 ### C++ <Stat.h>: https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/sys/stat.h
 ### C++ Filesystem library: https://en.cppreference.com/w/cpp/filesystem
 ### Posix Spawn using C Programming(How to fork() and hold parent process): https://linuxhint.com/posix-spawn-c-programming/
