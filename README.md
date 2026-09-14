## string2.h: Implementation of "strings" in pure C
This library implements strings in C, similarly to `std::string` in C++.  
It has only one header, `string2.h`, heh same as the project's name. That is why it is in `include/string2.h/string2.h`. The folder includes `.h` aswell because its in the name, not because I am necromancer or some sorcerer.  
Anyways, this single header declares everything you need to use.

Thats it. There's nothing much else going on in this library.  

### Documentation:
### 1. Construction/Destruction
I went the OOP way and each datatype is implemented using their respective structures.  
To construct an object, declare its respective structure and call the respective constructor, passing the structure's address and other values it takes.  
To destruct an object, similar to constructing it, call its respective destructor and pass the structure's address.  
If you do not call the destructor after constructing an object and the object's purpose have been served, bad things will happen, AKA memory leaks.  
Constructors and destructors follow this naming scheme:
```c
make_xyz(xyz* structure, ...); // Constructor
dealloc_xyz(xyz* structure, ...); // Destructor
```

### 2. string2
This structure implements string, obviously as its called string2 and thats the purpose of the project.  
It has the following two constructors:
```c
void make_string2(string2* string, char* cstring);
```
It constructors a string and copies the content of cstring into it.  
As the contents are actually copied, if you pass in a string literal and do modifications on this string object, it wont error out.  
This also means any modifications to the passed C string wont be reflected in this new string.
```c
void make_string2_size(string2* string, size_t initsize);
```
It constructs or makes, an empty string and reserves atleast `initsize` characters in its buffer.  
The string buffer is allocated in blocks of the value defined by `STRING_BUFFER_STEP` macro in `string2.h`. It is set to 128 by default.  
Meaning if you allocate 10 character, it will allocate 128, if you allocate 130, it will allocate 256 characters.  
### Concatenating to string2
Concatenation to string2 is done by functions with naming scheme:
```c
void string2_concat_datatype+other(string2* string, datatype thing_to_concatenate);
```
The arguments they take are pretty self explanatory but I am still going to document them.  
There are the following functions for concatenation:
```c
void string2_concat_char(string2* string, char c);
```
Concatenates a single character `c` to string2 `string`;
```c
void string2_concat_cstring(string2* string, char* cstring, size_t length);
```
Concatenates a C string AKA character array `cstring` of length `length` to string2 `string`.  
Note that as `length` is taken into account, `cstring` does not need to contain a null terminator `'\0'`. If this function encounters `'\0'`, it will concatenate it aswell and will not stop. You have been warned.  
```c
void string2_concat_cstring_auto(string2* string, char* cstring);
```
Automatically calculates the length of the given `cstring` and concatenates it to string2`string`. `cstring` must be terminated with `\0`;  
```c
void string2_concat_string2(string2* string, string2* str2);
```
Concatenates string2 `str2` to string2 `string`.  

If you need to concatenate often to a string2, use string2_builder instead.

### Reading into string2 from stream
It has the following functions for reading from input streams like a file or `stdin`:
```c
void string2_readword(string2 *string, FILE *stream);
```
It reads a continious array or characters NOT separated by any whitespace character from stream `stream` into string2 `string`. Whitespace characters include a space `' '`, tab `'\t'` line feed `'\n'` and CRLF `'\r\n'`.  
HOWEVER, any carriage return `\r` NOT followed by line feed `'\n'` isnt considered a whitespace and will be read into the string2 `string`.  
```c
void string2_readline(string2 *string, FILE *stream);
```
Just like readword, it reads a continious arry of characters into string2 `string` in a line from stream `stream`.  
Similarly to above, a single carriage return `\r` NOT followed by a line feed `'\n'` will be read into the string2 `string`.  
### Other stuff; Getter; Setter;
```c
char string2_getchar(string2* string, size_t index);
```
Returns the character at index `index` in string2 `string`.  
If index is out of bounds, it returns NULL.
```c
void string2_putchar(string2* string, size_t index, char c);
```
Sets the character at index `index` to be character `c` in string2 `string`.  
If index is out of bounds, it does nothing.  
### Zaping the string2 out of existence
After you are done torturing string2s, you can finally put them out of their misery with
```c
void dealloc_string2(string2* string);
```
This function brutally murders string2 `string` and frees the resources it aquired during its torture.  

### 3. string2_builder
It has the following constructor:
```c
void make_string2_builder(string2_builder* builder);
```
Already yapped enough about it thrice before...
### Appending/Concatenating to a string2_builder
The functions implementing this behaivor follow this naming scheme:
```c
void string2_builder_append_datatype+other(string2* string, datatype thing_to_concatenate);
```
They work exactly as the concatenating functions of string2. But they do it on a string2_builder. Already yapped enough about this...  
### Building a string (string2/C string)
After you are done appending and working with `string2_builder` you can finally build it with the building functions.  
They are:
```c
void string2_builder_build_string2(string2_builder* builder, string2* str);
```
Builds the string and stores it into string2 `str`. The passed string2 `str` should not have been constructed by its constructors, as this functions calls its constructors internally.  
```c
char* string2_builder_build_cstring(string2_builder* builder, uint* length)
```
Allocates a C string (character array), builds the string, stores into the C string and returns it.  
Takes a NULLABLE `length`, if an address to a `size_t` AKA `unsigned long/int` is given, stores the length of the built string into it, INCLUDING the null terminator `'\0'`.
```c
void string2_builder_build_cstring_to(string2_builder* builder, char* cstring);
```
Builds a C string and stores it into C string `cstring`. C string `cstring` must be atleast the size of the string that will be build, which also INCLUDES the null terminator `'\0'`.  
See the next section to get the length of the built string.  
### Other stuff; Getter; Setter;
```c
size_t string2_builder_get_length(string2_builder* builder);
```
Returns the length of the string of the string2_builder `builder`. It EXCLUDES the null terminator `'\0'`.
```c
char string2_builder_getchar(string2_builder* builder, size_t index);
```
Returns the character at index `index` in string2_builder `builder`.  
If index is out of bounds, it returns NULL.
```c
void string2_builder_putchar(string2_builder* builder, size_t index, char c);
```
Sets the character at index `index` to be character `c` in string2_builder `builder`.  
If index is out of bounds, it does nothing.  
### Destructing string2_builder
It has the following destructor:
```c
void dealloc_string2_builder(string2_builder* builder);
```
I am tired yapping...
### 4. Adios
For examples, see programs in `src/test`.