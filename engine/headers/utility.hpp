#ifndef UTILITY_H
#define UTILITY_H
#include <cctype>
#include <string>
#include <string_view>
#include <bit>

/// @brief Simple hash function for string `switch` statements.
/// The statement becomes `switch(hash(std::string))`
/// @param data std::string input, whether it be raw or a varable
/// @return hashed value of the string
constexpr uint32_t hash(std::string_view data) noexcept {   uint32_t hash = 5385;    for (auto &c : data)    hash = std::rotl(hash, 5) + c;    return hash; }

/// @brief Stack Overflow syntax sugar for string `case` statements.
/// The statement becomes `case "std::string"_ `
/// @param p raw string literal
/// @return hashed value of the string
constexpr inline unsigned int operator ""_(char const * p, size_t) { return hash(p); }
//

//
// Wrapper for std::tolower, modifies the string in-place
constexpr inline void lowercase(std::string &str) noexcept {    for (auto &c : str)    c = std::tolower(c); }
// Wrapper for std::toupper, modifies the string in-place
constexpr inline void uppercase(std::string &str) noexcept {    for (auto &c : str)    c = std::toupper(c); }
//



#endif