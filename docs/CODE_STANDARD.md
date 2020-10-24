# UAS Payload Coding Style Standard

We follow mainly the Google C++ standard. See the full list at: https://google.github.io/styleguide/cppguide.html#Function_Names

## Variable

The names of variables (including function parameters) and data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores. For instance: a_local_variable, a_struct_data_member, a_class_data_member_.

Common Variable names
For example:
```c
std::string table_name;  // OK - lowercase with underscore.
std::string tableName;   // Bad - mixed case.
```
Class Data Members

## Constant
Variables declared constexpr or const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case. Underscores can be used as separators in the rare cases where capitalization cannot be used for separation. For example: 

```c
const int kDaysInAWeek = 7;
const int kAndroid8_0_0 = 24;  // Android 8.0.0
```

All such variables with static storage duration (i.e. statics and globals, see Storage Duration for details) should be named this way. This convention is optional for variables of other storage classes, e.g. automatic variables, otherwise the usual variable naming rules apply. 

## Function
Regular functions have mixed case; accessors and mutators may be named like variables.

Ordinarily, functions should start with a capital letter and have a capital letter for each new word.

```c
AddTableEntry()
DeleteUrl()
OpenFileOrDie()
```

(The same naming rule applies to class- and namespace-scope constants that are exposed as part of an API and that are intended to look like functions, because the fact that they're objects rather than functions is an unimportant implementation detail.)

Accessors and mutators (get and set functions) may be named like variables. These often correspond to actual member variables, but this is not required. For example, int count() and void set_count(int count).


## Class
Type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.

The names of all types ！ classes, structs, type aliases, enums, and type template parameters ！ have the same naming convention. Type names should start with a capital letter and have a capital letter for each new word. No underscores. For example:

```c
// classes and structs
class UrlTable { ...
class UrlTableTester { ...
struct UrlTableProperties { ...

// typedefs
typedef hash_map<UrlTableProperties *, std::string> PropertiesMap;

// using aliases
using PropertiesMap = hash_map<UrlTableProperties *, std::string>;

// enums
enum UrlTableErrors { ...
```

## File Names
Filenames should be all lowercase and can include underscores (_) or dashes (-). Follow the convention that your project uses. If there is no consistent local pattern to follow, prefer "_".

Examples of acceptable file names:

```
my_useful_class.cc
my-useful-class.cc
myusefulclass.cc
myusefulclass_test.cc // _unittest and _regtest are deprecated.
```

C++ files should end in .cc and header files should end in .h. Files that rely on being textually included at specific points should end in .inc (see also the section on self-contained headers).

Do not use filenames that already exist in /usr/include, such as db.h.

In general, make your filenames very specific. For example, use http_server_logs.h rather than logs.h. A very common case is to have a pair of files called, e.g., foo_bar.h and foo_bar.cc, defining a class called FooBar.

## Macro Names
You're not really going to define a macro, are you? If you do, they're like this: MY_MACRO_THAT_SCARES_SMALL_CHILDREN_AND_ADULTS_ALIKE.

Please see the description of macros; in general macros should not be used. However, if they are absolutely needed, then they should be named with all capitals and underscores.

```c
#define ROUND(x) ...
#define PI_ROUNDED 3.0
```

## Function Comments
Declaration comments describe use of the function (when it is non-obvious); comments at the definition of a function describe operation.

## Global Variables
All global variables should have a comment describing what they are, what they are used for, and (if unclear) why it needs to be global. For example:

```c
// The total number of tests cases that we run through in this regression test.
const int kNumTestCases = 6;
```