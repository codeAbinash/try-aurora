/**
 * Aurora ✨: The C code highlighting engine
 * Author 🧑🏻‍💻: Abinash Karmakar (codeAbinash)
 * Lightweight ✨ - 3kB only (gzipped) 🎉
 * Blazing fast ⚡ - 1000 lines in 4ms 🚀
 * 2023-10-26 📅
 */

// 1. Header File Highlighting
#include <stdio.h>

// 2. User Defined Header File Highlighting
#include "../include/myheader.h"

// 3. Function Definition Highlighting
void sayHello(int n) {
   float f = 10;
   for (size_t i = 0; i < n; i++, f += 0.1) {
      printf("Hello World! \t %d - %2.2f \n", i, f);
   }
}

// 4. Function Call Highlighting
sayHello(10);

// 5. Keyword Highlighting
long long int num = 1234;

// 6. Most used macros Highlighting
void* p = NULL;

// 7. Bracket Pair Highlighting
int num = (-30 + (10 + 20 * (3 / 4 + 10 * (20 + 30))));

// 8. Data Type Highlighting
float f = 10.0;
float f = 10.0f;
float f = 10.0F;

int x = 10;
int x = 0b10101;                   // Binary Number
int x = 0123215;                   // Octal Number
int x = 0x1A2BD;                   // Hexadecimal Number
int x = 10u;                       // Unsigned Integer
int x = 10U;                       // Unsigned Integer
long int x = 10l;                  // Long Integer
long int x = 10L;                  // Long Integer
long long int x = 10ll;            // Long Long Integer
long long int x = 10LL;            // Long Long Integer
unsigned long long int x = 10ull;  // Unsigned Long Long Integer
unsigned long long int x = 10ULL;  // Unsigned Long Long Integer

char c = 'a';   // Character
char c = '\n';  // Escape Sequence

char str[] = "Hello World!";        // String
char str[] = "Hello \"World!\"";    // Escape Sequence
char str[] = "Hello \n \t World!";  // Escape Sequence

char str[] = "Hello %s!";            // Format Specifier
char str[] = "The number is %d";     // Format Specifier
char str[] = "The number is %2.2f";  // Complex Format Specifier
char str[] = "The number is %x";     // Format Specifier

/**
 *
 * It is highly customizable. You can customize it as you want.
 * You can change the color of the keywords, macros, data types, etc.
 * You can change the color of each and every token. ✨
 * See the documentation for more details. 📖
 */

// ❌ Cannot highlight macros in different color other than names
#define PI 3.14159265358979323846
/*
 The reason behind this is that, macros may be defined beyond
 the scope of the file. So, it is not possible to highlight,
 though most used macros are highlighted. E.g. NULL, EOF
*/

// ❌ Cannot highlight user defined data types
struct Person {
   char name[20];
   int age;
   float salary;
};
/*
  The reason behind this is that, Some of the user defined
  data types may have scope which is complex to handle for
  this light weight  highlighting engine. Otherwise,
  it will make the engine heavy weight. So, it is not possible
  to highlight user defined data types.
*/

/*


     ▄▄▄       █    ██  ██▀███   ▒█████   ██▀███   ▄▄▄
    ▒████▄     ██  ▓██▒▓██ ▒ ██▒▒██▒  ██▒▓██ ▒ ██▒▒████▄
    ▒██  ▀█▄  ▓██  ▒██░▓██ ░▄█ ▒▒██░  ██▒▓██ ░▄█ ▒▒██  ▀█▄
    ░██▄▄▄▄██ ▓▓█  ░██░▒██▀▀█▄  ▒██   ██░▒██▀▀█▄  ░██▄▄▄▄██
     ▓█   ▓██▒▒▒█████▓ ░██▓ ▒██▒░ ████▓▒░░██▓ ▒██▒ ▓█   ▓██▒
     ▒▒   ▓▒█░░▒▓▒ ▒ ▒ ░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░
      ▒   ▒▒ ░░░▒░ ░ ░   ░▒ ░ ▒░  ░ ▒ ▒░   ░▒ ░ ▒░  ▒   ▒▒ ░
      ░   ▒    ░░░ ░ ░   ░░   ░ ░ ░ ░ ▒    ░░   ░   ░   ▒
          ░  ░   ░        ░         ░ ░     ░           ░  ░

*/

// Here is a sample code for you to test the highlighting engine.

// Example Code :

/**
 * Library for a vector data structure.
 * Author : Abinash Karmakar
 * 2023-09-01 MIT License Version: 1.0
 */

#include "../../Algorithms/algorithms.h"
#include "assert.h"
#include "malloc.h"
#include "vector.h"

vector vec_init_with_destroyer(size_t size, size_t element_size, void (*destroyer)(void*)) {
   assert(size >= 0 && "Size must be non negative");
   assert(element_size > 0 && "Element size must be positive");
   vector vec;    // Creating a vector.
   vec.size = 0;  // Setting the size to 0
   vec.element_size = element_size;
   vec.capacity = size;
   if (size > 0)
      vec.data = malloc(size * element_size);
   else
      vec.data = NULL;
   vec.destroyer = destroyer;
   return vec;
}
/**
 * @brief Function to get the void pointer to the element at the given index.
 * @param vec The vector.
 * @param index The index of the element.
 * @return A void pointer to the element at the given index.
 * Time complexity: O(1)
 * @note If the index is negative, then the index is calculated from the end of the vector.
 * @note If the index is out of bounds, then the program is aborted.
 */
void* vec_at(vector* vec, int index) {
   if (index >= 0) {
      // If out of bounds
      assert(index < vec->size && "Index out of bounds");
      return vec->data + index * vec->element_size;
   } else {
      // if too much negative
      assert(index >= -vec->size && "Index out of bounds");
      return vec->data + (vec->size + index) * vec->element_size;
   }
}

/**
 * @brief Function to destroy the vector in the range [start, end).
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
 */
void __vec_destroy_rng(vector* vec, void* start, void* end) {
   // Destroying in the range [start, end) of the vector. but not freeing the vector.
   void* pos = start;
   if (vec->destroyer != NULL) {
      while (pos != end) {
         vec->destroyer(pos);
         pos += vec->element_size;
      }
   }
}
/**
 * @brief Function to destroy the vector fully.
 * @param vec The vector.
 * Time complexity: O(n)
 */
void __vec_destroyer(vector* vec) {
   __vec_destroy_each_item(vec);
   free(vec->data);
   vec->data = NULL;
   vec->size = 0;
   vec->capacity = 0;
   vec->element_size = 0;
   vec->destroyer = NULL;
}

/**
 * @brief Function to resize the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
 */
void vec_resize(vector* vec, size_t size) {
   assert(size >= 0 && "Size must be non negative");
   // If the size is equal to the current size, then do nothing.
   if (size == vec->size) return;
   if (size > vec->capacity) {
      __force_resize_to(vec, size);
   } else if (size < vec->size) {
      // if `size` is less than the current size, then the last elements are destroyed.
      void* start = vec->data + size * vec->element_size;
      void* end = vec->data + vec->size * vec->element_size;
      __vec_destroy_rng(vec, start, end);
   }
   vec->size = size;
}

/**
 * @brief Function to reserve the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
 */
void vec_reserve(vector* vec, size_t size) {
   assert(size >= 0 && "Size must be non negative");
   size_t capacity = vec->capacity;
   // If the size is less than the current capacity, then do nothing.
   if (size <= capacity) return;
   // If the size is greater than the current capacity, then resize the vector.
   __force_reserve_to(vec, size);
}

/**
 * @brief Function to shrink the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
 */
void vec_shrink_to_fit(vector* vec) {
   __force_reserve_to(vec, vec->size);
}

/**
 * @brief Function to remove the last element from the vector.
 * @param vec The vector.
 * Time complexity: O(1)
 */
void vec_pop_back(vector* vec) {
   // Check if the vector is empty.
   assert(vec->size > 0 && "Vector is empty");
   // Destroying the last element.
   void* pos = vec->data + (vec->size - 1) * vec->element_size;
   if (vec->destroyer != NULL) {
      vec->destroyer(pos);
   }
   vec->size--;
}

/**
 * @brief Function to insert the data to the end of the vector.
 * @param vec The vector.
 * @param data The data to insert.
 * Time complexity: O(1)
 * @note This function is used internally by the library.
 */
void __valid_pos(vector* vec, void* pos) {
   // Check if the position is valid.
   void* end = vec->data + vec->size * vec->element_size;
   assert(pos >= vec->data && "Position pointer out of bounds, before start");
   assert(pos < end && "Position pointer out of bounds, after end");
}

/**
 * @brief Function to check if the range is valid.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(1)
 * @note This function is used internally by the library.
 */
void __check_erase_bounds(vector* vec, void* start, void* end) {
   // Check if the position is valid.
   __valid_pos(vec, start);
   __valid_pos(vec, end);
   // Check if the range is valid.
   if (start == end) return;
   assert(start <= end && "Start pointer must be less than or equal to end pointer");
   // Must be multiple of element size.
   assert((end - start) % vec->element_size == 0 && "Invalid range");
}

/**
 * @brief Function to erase the elements in the range [start, end) in the vector.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
 */
void vec_erase_rng(vector* vec, void* start, void* end) {
   // Check if the range is valid.
   __check_erase_bounds(vec, start, end);
   // Destroying the elements in the range.
   __vec_destroy_rng(vec, start, end);
   // Moving the elements after the range to the left.
   size_t size = vec->data + vec->size * vec->element_size - end;
   memmove(start, end, size);
   vec->size -= (end - start) / vec->element_size;
}

/**
 * @brief Function to erase the element in the vector at the given position.
 * @param vec The vector.
 * @param pos The position pointer.
 * Time complexity: O(n)
 */
void vec_erase(vector* vec, void* pos) {
   // Check if the position is valid.
   __valid_pos(vec, pos);
   void* end = vec->data + vec->size * vec->element_size;
   // Destroying the element at the position.
   if (vec->destroyer != NULL) {
      vec->destroyer(pos);
   }
   // Moving the elements after the position to the left.
   size_t size = end - pos - vec->element_size;
   memmove(pos, pos + vec->element_size, size);
   vec->size--;
}

/**
 * @brief Function to insert the data to the given position in the vector.
 * @param vec The vector.
 * @param pos The position pointer.
 * @param data The data to insert.
 * Time complexity: O(n)
 */
void vec_insert(vector* vec, void* pos, void* data) {
   // If the position is out of bound of [start, end) of the vector, then do nothing.
   // Here end is the address of the last element of the allocated memory.
   void* start = vec->data;
   void* capacityEnd = vec->data + vec->capacity * vec->element_size;
   void* end = vec->data + vec->size * vec->element_size;

   assert(pos >= start && "Position pointer out of bounds, before start");
   assert(pos <= capacityEnd && "Position pointer out of bounds, after end");

   if (pos == end) {
      vec_push_back(vec, data);
      return;
   }

   if (pos > end) {
      // Move the elements after the end to the right.
      size_t size = pos - end;
      // Copying the data to the position.
      memcpy(pos, data, vec->element_size);
      vec->size += (pos - end) / vec->element_size + 1;
   } else {
      // Move the elements after the end to the right.
      size_t size = end - pos;
      memmove(pos + vec->element_size, pos, size);
      // Copying the data to the position.
      memcpy(pos, data, vec->element_size);
      vec->size++;
   }
}

/**
 * @brief Function to insert a range of data to the given position in the vector.
 * @param vec The vector.
 * @param pos The position pointer.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
 */
void vec_insert_rng(vector* vec, void* pos, void* start, void* end) {
   // If the position is out of bound of [start, end) of the vector, then do nothing.
   // Here end is the address of the last element of the allocated memory.
   void* capacityEnd = vec->data + vec->capacity * vec->element_size;
   void* vecEnd = vec->data + vec->size * vec->element_size;

   assert(pos >= vec->data && "Position pointer out of bounds, before start");
   assert(pos <= capacityEnd && "Position pointer out of bounds, after end");
   // Check if the range is valid.
   assert(start <= end && "Start pointer must be less than or equal to end pointer");
   assert((end - start) % vec->element_size == 0 && "Invalid range");
   assert(end - start <= capacityEnd - vecEnd && "Not enough space in vector");

   if (pos >= vecEnd) {
      // Move the elements after the end to the right.
      size_t size = pos - vecEnd + (end - start);
      // Copying the data to the position.
      memcpy(pos, start, end - start);
      vec->size += (pos - vecEnd) / vec->element_size + (end - start) / vec->element_size;
   } else {
      // Move the elements after the end to the right.
      size_t size = vecEnd - pos;
      memmove(pos + (end - start), pos, size);
      // Copying the data to the position.
      memcpy(pos, start, end - start);
      vec->size += (end - start) / vec->element_size;
   }
}

/**
 * @brief Function to assign the vector to the given size and fill it with the given data.
 * @param vec The vector.
 * @param n The new size of the vector.
 * @param data The data to fill.
 * Time complexity: O(n)
 */
void vec_assign(vector* vec, size_t n, void* data) {
   assert(n >= 0 && "n must be non negative");
   // Destroying each item in the vector, but not freeing the vector.
   __vec_destroy_each_item(vec);
   // If the size is greater than the current capacity, then resize the vector.
   if (n > vec->capacity) {
      __force_resize_to(vec, n);
   }
   // Copying the data to the vector.
   void* dest = vec->data;
   vec->size = n;
   for (size_t i = 0; i < n; i++) {
      memcpy(dest, data, vec->element_size);
      dest += vec->element_size;
   }
}

/**
 * @brief Function to assign the vector to the given range and fill it with the given data.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
 */
void vec_assign_rng(vector* vec, void* start, void* end) {
   size_t element_size = vec->element_size;
   size_t size = (end - start) / element_size;
   assert(size >= 0 && "Size must be non negative");
   // Destroying each item in the vector, but not freeing the vector.
   __vec_destroy_each_item(vec);
   // If the size is greater than the current capacity, then resize the vector.
   if (size > vec->capacity) {
      __force_resize_to(vec, size);
   }
   // Copying the data to the vector.
   void* dest = vec->data;
   vec->size = size;
   for (size_t i = 0; i < size; i++) {
      memcpy(dest, start, element_size);
      dest += element_size;
      start += element_size;
   }
}

/**
 * @brief Function to make the vector size to double the current size.
 * @param vec The vector.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
 */
void __vec_double_if_full(vector* vec) {
   // If the vector is full, double the size of the vector.
   if (vec->size == vec->capacity) {
      // If the size is 0, then double the size to 1.
      if (vec->size == 0)
         __force_reserve_to(vec, 1);
      else
         __force_reserve_to(vec, vec->capacity * 2);
   }
}

/**
 * @brief Function to push the data to the end of the vector.
 * @param vec The vector.
 * @param data The data to push.
 * Time complexity: O(1)
 * @note If the vector is full, then the vector size is doubled.
 */
void vec_push_back(vector* vec, void* data) {
   // Check if the vector is full. If full, double the size of the vector.
   __vec_double_if_full(vec);
   // Copying the data to the end of the vector.
   void* dest = vec->data + vec->size * vec->element_size;
   vec->size++;
   memcpy(dest, data, vec->element_size);
}

// End of 'Data Structures/Vector/Vector.c'

// Happy Coding! 🧑🏻‍💻
// Made with ❤️ by Abinash
