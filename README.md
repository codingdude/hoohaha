## Coding Style Guide

### Header Files

All header files should have #define guards to prevent multiple inclusion. The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_.
To guarantee uniqueness, they should be based on the full path in a project's source tree. For example, the file foo/src/bar/baz.h in project foo should have the following guard:

    #ifndef FOO_BAR_BAZ_H_
    #define FOO_BAR_BAZ_H_

    ...

    #endif  // FOO_BAR_BAZ_H_

Include headers in the following order: Related header, C system headers, C++ standard library headers, other libraries' headers, your project's headers.
All of a project's header files should be listed as descendants of the project's source directory without use of UNIX directory aliases . (the current directory) or .. (the parent directory). For example, project/src/base/logging.h should be included as

    #include "base/logging.h"

Headers should only be included using an angle-bracketed path if the library requires you to do so. In particular, the following headers require angle brackets:

* C and C++ standard library headers (e.g. <stdlib.h> and <string>).
* POSIX, Linux, and Windows system headers (e.g. <unistd.h> and <windows.h>).
* In rare cases, third_party libraries (e.g. <Python.h>).

In dir/foo.cpp, whose main purpose is to implement the stuff in dir2/foo2.h, order your includes as follows:

1. dir2/foo2.h.
2. A blank line
3. C system headers, and any other headers in angle brackets with the .h extension, e.g., <unistd.h>, <stdlib.h>, <Python.h>.
4. A blank line
5. C++ standard library headers (without file extension), e.g., <algorithm>, <cstddef>.
6. A blank line
7. Other libraries' .h files.
8. A blank line
9. Your project's .h files.

Separate each non-empty group with one blank line. Within each section the includes should be ordered alphabetically.
Sometimes, system-specific code needs conditional includes. Such code can put conditional includes after other includes.

### Naming

Optimize for readability using names that would be clear even to people on a different team.
Use names that describe the purpose or intent of the object. Do not worry about saving horizontal space as it is far more important to make your code immediately understandable by a new reader. Minimize the use of abbreviations that would likely be unknown to someone outside your project (especially acronyms and initialisms). Do not abbreviate by deleting letters within a word. As a rule of thumb, an abbreviation is probably OK if it's listed in Wikipedia. Generally speaking, descriptiveness should be proportional to the name's scope of visibility. For example, n may be a fine name within a 5-line function, but within the scope of a class, it's likely too vague
Note that certain universally-known abbreviations are OK, such as i for an iteration variable and T for a template parameter.
For the purposes of the naming rules below, a "word" is anything that you would write in English without internal spaces. This includes abbreviations, such as acronyms and initialisms. For names written in mixed case (also sometimes referred to as "camel case" or "Pascal case"), in which the first letter of each word is capitalized, prefer to capitalize abbreviations as single words, e.g., StartRpc() rather than StartRPC().

Filenames should be all lowercase and can include underscores (_).
Examples of acceptable file names:

* my_useful_class.cpp
* myusefulclass.cpp
* myusefulclass_test.cpp

C++ files should have a .cpp filename extension, and header files should have a .h extension.

Type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.
The names of all types — classes, structs, type aliases, enums, and type template parameters — have the same naming convention.

For example:

    // classes and structs
    class UrlTable
    class UrlTableTester
    struct UrlTableProperties

    // typedefs
    typedef hash_map<UrlTableProperties *, std::string> PropertiesMap;

    // using aliases
    using PropertiesMap = hash_map<UrlTableProperties *, std::string>;

    // enums
    enum class UrlTableError

The names of variables (including function parameters) and data members are snake_case (all lowercase, with underscores between words). Data members of classes (but not structs) additionally have trailing underscores. For instance: a_local_variable, a_struct_data_member, a_class_data_member_.

For example:

    std::string table_name;  // OK - snake_case.

Data members of classes, both static and non-static, are named like ordinary nonmember variables, but with the m_ prefix.

    class TableInfo
    {
        ...
    private:
        std::string m_table_name;  // OK - prefixed.
        static Pool<TableInfo>* m_pool;  // OK.
    };

Data members of structs, both static and non-static, are named like ordinary nonmember variables. They do not have the trailing underscores that data members in classes have.

    struct UrlTableProperties
    {
        std::string name;
        int num_entries;
        static Pool<UrlTableProperties>* pool;
    };

Variables declared constexpr or const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by CamelCase.

    const int kDaysInAWeek = 7;
    const int kAndroid8_0_0 = 24;  // Android 8.0.0

Regular functions should start with a capital letter and have a capital letter for each new word.

    AddTableEntry()
    DeleteUrl()
    OpenFileOrDie()

Namespace names are all lower-case, with words separated by underscores. Top-level namespace names are based on the project name . Avoid collisions between nested namespaces and well-known top-level namespaces.

Enumerators (for both scoped and unscoped enums) should be named like constants.

    enum class UrlTableError
    {
        kOk = 0,
        kOutOfMemory,
        kMalformedInput,
    };

Macros should be named with all capitals and underscores, and with a project-specific prefix.

    #define MYPROJECT_ROUND(x) ...

### Formatting

Each line of text in your code should be at most 80 characters long. A line may exceed 80 characters if it is

* a comment line which is not feasible to split without harming readability, ease of cut and paste or auto-linking -- e.g., if a line contains an example command or a literal URL longer than 80 characters.
* a string literal that cannot easily be wrapped at 80 columns. This may be because it contains URIs or other semantically-critical pieces, or because the literal contains an embedded language, or a multiline literal whose newlines are significant like help messages. In these cases, breaking up the literal would reduce readability, searchability, ability to click links, etc. Except for test code, such literals should appear at namespace scope near the top of a file. If a tool like Clang-Format doesn't recognize the unsplittable content, disable the tool around the content as necessary.
* an include statement.
* a header guard
* a using-declaration

Use only spaces, and indent 4 spaces at a time.

Return type on the same line as function name, parameters on the same line if they fit. Wrap parameter lists which do not fit on a single line as you would wrap arguments in a function call.
Functions look like this:

    ReturnType ClassName::FunctionName(Type par_name1, Type par_name2)
    {
        DoSomething();
        ...
    }

If you have too much text to fit on one line:

    ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
                                                 Type par_name3)
    {
        DoSomething();
        ...
    }

or if you cannot fit even the first parameter:

    ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
        Type par_name1,  // 4 space indent
        Type par_name2,
        Type par_name3)
    {
        DoSomething();  // 2 space indent
        ...
    }

Some points to note:
* Choose good parameter names.
* A parameter name may be omitted only if the parameter is not used in the function's definition.
* If you cannot fit the return type and the function name on a single line, break between them.
* If you break after the return type of a function declaration or definition, do not indent.
* The open parenthesis is always on the same line as the function name.
* There is never a space between the function name and the open parenthesis.
* There is never a space between the parentheses and the parameters.
* The opening brace appears either on a new line or at the end of the function declaration line if it contains single-line code.
* The close curly brace is either on the last line by itself or on the same line as the open curly brace.
* There should be a space between the close parenthesis and the open curly brace.
* All parameters should be aligned if possible.
* Default indentation is 4 spaces.

Either write the call all on a single line, wrap the arguments at the parenthesis, or start the arguments on a new line indented by four spaces and continue at that 4 space indent. In the absence of other considerations, use the minimum number of lines, including placing multiple arguments on each line where appropriate.

Function calls have the following format:

    bool result = DoSomething(argument1, argument2, argument3);

If the arguments do not all fit on one line, they should be broken up onto multiple lines, with each subsequent line aligned with the first argument. Do not add spaces after the open paren or before the close paren:

    bool result = DoSomething(averyveryveryverylongargument1,
                              argument2, argument3);

Arguments may optionally all be placed on subsequent lines with a four space indent:

    if (...)
    {
        ...
        ...
        if (...)
        {
            bool result = DoSomething(
                argument1, argument2,  // 4 space indent
                argument3, argument4);
            ...
        }

At a high level, looping or branching statements consist of the following components:

* One or more statement keywords (e.g. if, else, switch, while, do, or for).
* One condition or iteration specifier, inside parentheses.
* One or more controlled statements, or blocks of controlled statements.

For these statements:

* The components of the statement should be separated by single spaces (not line breaks).
* Inside the condition or iteration specifier, put one space (or a line break) between each semicolon and the next token, except if the token is a closing parenthesis or another semicolon.
* Inside the condition or iteration specifier, do not put a space after the opening parenthesis or before the closing parenthesis.
* Put any controlled statements inside blocks (i.e. use curly braces).
* The opening brace appears always on a new line
* Inside the controlled blocks, put one line break immediately after the opening brace, and one line break immediately before the closing brace.

The basic format for the statements:

    if (condition)                       // Good - no spaces inside parentheses.
    {
        DoOneThing();                    // Good - four-space indent.
        DoAnotherThing();
    }                                    // Good - closing brace on new line, else on the next line.
    else if (int a = f(); a != 3)
    {
        DoAThirdThing(a);
    }
    else
    {
        DoNothing();
    }
    
    // Good - the same rules apply to loops.
    while (condition)
    {
        RepeatAThing();
    }
    
    // Good - the same rules apply to loops.
    do
    {
        RepeatAThing();
    }
    while (condition);
    
    // Good - the same rules apply to loops.
    for (int i = 0; i < 10; ++i)
    {
        RepeatAThing();
    }

The basic format for a class definition:

    class MyClass : public OtherClass
    {
    public:
        MyClass();  // Regular 4 space indent.
        explicit MyClass(int var);
        ~MyClass() {}

        void SomeFunction();
        void SomeFunctionThatDoesNothing() {}

        void set_some_var(int var) { some_var_ = var; }
        int some_var() const { return some_var_; }

    private:
        bool SomeInternalFunction();

        int m_some_var;
        int m_some_other_var;
    };

The contents of namespaces are not indented. Namespaces do not add an extra level of indentation. For example, use:

    namespace {

    void foo() // Correct.  No extra indentation within namespace.
    {
        ...
    }

    }  // namespace
