# UAS Payload Coding Style Standard

---

<!-- vscode-markdown-toc -->
* 1. [OOP guideline](#OOPguideline)
* 2. [Coding Standard](#CodingStandard)
	* 2.1. [Variable](#Variable)
	* 2.2. [Constant](#Constant)
	* 2.3. [Function](#Function)
	* 2.4. [Class](#Class)
	* 2.5. [File Names](#FileNames)
	* 2.6. [Headers](#Headers)
	* 2.7. [Includes](#Includes)
	* 2.8. [Namespaces](#Namespaces)
	* 2.9. [Macro Names](#MacroNames)
	* 2.10. [Function Comments](#FunctionComments)
	* 2.11. [Global Variables](#GlobalVariables)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->


##  1. <a name='OOPguideline'></a>OOP guideline

Please refer to [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

- use [rules of five](https://en.cppreference.com/w/cpp/language/rule_of_three) for class default operators


##  2. <a name='CodingStandard'></a>Coding Standard

We follow mainly the Google C++ standard. See the full list at [Google CPPGuidelone](https://google.github.io/styleguide/cppguide.html#Function_Names).

###  2.1. <a name='Variable'></a>Variable

The names of variables (including function parameters) and data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores. For instance: a_local_variable, a_struct_data_member, a_class_data_member_.

Common Variable names
For example:
```c
std::string table_name;  // OK - lowercase with underscore.
std::string tableName;   // Bad - mixed case.
```
Class Data Members

###  2.2. <a name='Constant'></a>Constant
Variables declared constexpr or const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case. Underscores can be used as separators in the rare cases where capitalization cannot be used for separation. For example: 

```c++
const int kDaysInAWeek = 7;
const int kAndroid8_0_0 = 24;  // Android 8.0.0
```

All such variables with static storage duration (i.e. statics and globals, see Storage Duration for details) should be named this way. This convention is optional for variables of other storage classes, e.g. automatic variables, otherwise the usual variable naming rules apply. 

###  2.3. <a name='Function'></a>Function
Regular functions have mixed case; accessors and mutators may be named like variables.

Ordinarily, functions should start with a capital letter and have a capital letter for each new word.

```c++
AddTableEntry()
DeleteUrl()
OpenFileOrDie()
```

(The same naming rule applies to class- and namespace-scope constants that are exposed as part of an API and that are intended to look like functions, because the fact that they're objects rather than functions is an unimportant implementation detail.)

Accessors and mutators (get and set functions) may be named like variables. These often correspond to actual member variables, but this is not required. For example, int count() and void set_count(int count).


###  2.4. <a name='Class'></a>Class
Type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.

The names of all types ！ classes, structs, type aliases, enums, and type template parameters ！ have the same naming convention. Type names should start with a capital letter and have a capital letter for each new word. No underscores. For example:

```c++
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

###  2.5. <a name='FileNames'></a>File Names
Filenames should be all lowercase and include underscores "_".

Examples of acceptable file names:

```
my_useful_class.cpp
my_useful_class_test.cpp // _unittest and _regtest are deprecated.
```

C++ files should end in .cc and header files should end in .h. Files that rely on being textually included at specific points should end in .inc (see also the section on self-contained headers).

Do not use filenames that already exist in /usr/include, such as db.h.

In general, make your filenames very specific. For example, use http_server_logs.h rather than logs.h. A very common case is to have a pair of files called, e.g., foo_bar.h and foo_bar.cc, defining a class called FooBar.

###  2.6. <a name='Headers'></a>Headers

* Use _header guards_ to prevent issues of duplicate or circular includes which cause the source code to be compiled multiple times and cause build errors. 
    * If you're writing C++ (ie. not C), use `#pragma once` at the very top of the file. 
      ```cpp
      #pragma once
      ```
    * If you're writing C, header guards should be used. They should be fully capitalized and include `_H_` at the end.
      ```c
      #ifndef AI_WORLD_FIELD_H_
      #define AI_WORLD_FIELD_H_
      ```
      At the end of the file, make sure to close the conditional preprocessor. An inline comment must be at the end with the same name as the _\#define_
      ```cpp
      #endif /* AI_WORLD_FIELD_H_ */
      ```
*In general the reason a header guard's name is so complicated is to make sure that it is unique. There cannot be any other header guards or constants defined with #define anywhere else in the code, or weird build issues may occur.*


###  2.7. <a name='Includes'></a>Includes

* Use `#include` sparingly and only include the necessary sources to build the file. Do not include headers whos class or implementation is not used.
* Often `.cpp` files include its corresponding header `.h` file, it means the `.cpp` file include everything included in the header. Do not have duplicate `#include`'s in both `.h` and `.cpp` files.
* `#include`s are generally preferred written on the `.cpp` side; use minimum `#include` in the header file. Use _forward declarations_ in headers if necessary.
* Specify full path of the include file on the file system, relative to the top-level project directory or _WORKSPACE_ file. Do not use relative paths.
  ```c++
  // Incorrect
  #include "../../driver/rc_driver.h"
 
  // Incorrect
  #include "rc_driver.h"

  // Correct
  #include "driver/rc_driver.h"
  ```

###  2.8. <a name='Namespaces'></a>Namespaces

Namespace names are all lower-case, with words separated by underscores.

* We use namespace for it's protection, despite added complexity.
    * Considering that we use a lot of library code for driver, we want to protect our code with namespace so that if both the library and our code has `attachGPS()`, as long as we define a namespace for our GPS code, we don't need to worry about running into naming conflict.
* Do not use `using namespace ...` in header files.
    * This is because any file that includes this header will also implicitly be using the namespace, which can cause subtle issues and naming conflicts.
* namespace **DO NOT **add indentation!
  * ```c++
  	// correct
	namespace abc
	{
	class A {
		...
	}
	}  // namespace

	//incorrect
	namespace abc
	{
		class A {
			...
		}
	}  // namespace
	```


###  2.9. <a name='MacroNames'></a>Macro Names

> You're not really going to define a macro, are you? If you do, they're like this: `MY_MACRO_THAT_SCARES_SMALL_CHILDREN_AND_ADULTS_ALIKE`.

Please see the description of macros; in general macros should not be used. However, we only use marco for pin assignments, as other embedded library generally does. However, to avoid macro conflict, make sure to start the name with `WALLE` and use decriptive words. *All Macro variables should be named with all capitals and underscores.* **DO NOT use marco for any other purposes.**

```c++
#define WALLE_MOTOR_PIN_A 1
#define WALLE_BNO055_SDA 10
```


###  2.10. <a name='FunctionComments'></a>Function Comments
Function comment is **very important**! Declaration comments describe use of the function (when it is non-obvious); comments at the definition of a function describe operation.

We use [javadoc](https://www.tutorialspoint.com/java/java_documentation.htm) style function comment style. 

In the header file:
```c++
// incorrect
// This function add two numbers
double add(int a, int b);

// correct
/**
 * This function add two nunmbers
 * @param a the first number to add
 * @param b the second number to add
 * @exception (optional)
 * @throws (optional)
 * @return a + b
 */
double add(int a, int b);

// more example
/**
 * Returns true if the polygon intersects the circle, false otherwise.
 *
 * @param first
 * @param second
 * @return true if the polygon intersects the circle, false otherwise
 */
bool intersects(const Polygon &first, const Circle &second);
```

in .cpp file, we keep the function comment to code comments only. Any class/function documentations should be in the header file

```c++
// incorrect
/**
 * This function add two nunmbers
 * @param a the first number to add
 * @param b the second number to add
 * @exception
 * @throws
 * @return
 */
double add(int a, int b) {
	...
}

// correct
double add(int a, int b) {
	// code related comment
	...
}
```

###  2.11. <a name='GlobalVariables'></a>Global Variables
All global variables should have a comment describing what they are, what they are used for, and (if unclear) why it needs to be global. For example:

```c++
// The total number of tests cases that we run through in this regression test.
const int kNumTestCases = 6;
```