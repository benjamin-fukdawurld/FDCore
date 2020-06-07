#ifndef FDCORE_H
#define FDCORE_H

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <thread>
#include <vector>


/**
 * @def FD_CORE_FNV32_PRIME the prime number to use in fnv32-a hashing
 */
#ifndef FD_CORE_FNV32_PRIME
    #define FD_CORE_FNV32_PRIME (0x01000193)
#endif

/**
 * @def FD_CORE_FNV32_INIT the init number to use in fnv32-a hashing
 */
#ifndef FD_CORE_FNV32_INIT
    #define FD_CORE_FNV32_INIT (0x811c9dc5)
#endif



/**
 *
 * @file FDCore.h This file defines several basic tools like string modifications, regex for
 * numbers, number of cores etc.
 *
 */

/**
 * @namespace FDCore contains all the utils functions and objects used in most of the FD framework's
 * libraries
 */
namespace FDCore
{
    char *readFile(FILE *file);

    /**
     * @brief ltrim supresses spaces at the begining of a string
     * @param s the string to trim
     * @return s without spaces before the first character
     */
    std::string &ltrim(std::string &s);

    /**
     * @brief rtrim supresses spaces at the end of a string
     * @param s the string to trim
     * @return s without spaces after the last character
     */
    std::string &rtrim(std::string &s);

    /**
     * @brief trim supresses spaces at the begining and the end of a string
     * @param s the string to trim
     * @return s without spaces before the first character and after the last character
     */
    inline std::string &trim(std::string &s) { return ltrim(rtrim(s)); }

    /**
     * @brief uniformSpaces replaces any blank character (ie : ' ', '\t', '\n' etc.) set to a single
     * ' '
     * @param s the string to uniform
     * @return a string with only ' ' as space
     */
    inline std::string &uniformSpaces(std::string &s);

    /**
     * @brief prepareString supresses useless spaces and uniform them to simplify parsing
     * @param s the string to format
     * @return the formated string
     */
    inline std::string &prepareString(std::string &s) { return uniformSpaces(trim(s)); }

    /**
     * @brief getFloatRegex returns a regex that matches every floating point number
     * @return a regex that matches every float
     */
    inline std::string getFloatRegex() { return "[+-]?\\d*\\.?\\d+"; }

    /**
     * @brief getIntegerRegex returns a regex that matches every integer
     * @return a regex that matches every integer
     */
    inline std::string getIntegerRegex() { return "[+-]?\\d+"; }

    /**
     * @brief cleanStream formats an entire stream content and write it into another one
     * @param in the input stream to format
     * @param out the stream that contains the result of the formating
     * @return the stream that contains the result of the formating
     */
    std::ostream &cleanStream(std::istream &in, std::ostream &out);


    /**
     * @brief Convert a wild string into string
     * @param wstr the wild string to convert
     * @return the converted string
     */
    inline std::string wstringToString(const std::wstring &wstr)
    {
        return std::string(wstr.begin(), wstr.end());
    }


    /**
     * @brief Convert a string into wild string
     * @param str the string to convert
     * @return the converted wild string
     */
    inline std::wstring stringToWString(const std::string &str)
    {
        return std::wstring(str.begin(), str.end());
    }


    /**
     * @brief getNumberOfCores this function returns the number of cores for this application if
     * NUMBER_OF_CORE is defined, it is returned otherwise it returns
     * std::thread::hardware_concurrency(). If NO_THREAD_ALLOWED is defined it returns 0
     * @return the number of cores for this application
     */
    inline uint_fast8_t getNumberOfCores()
    {
#ifdef NUMBER_OF_CORE
        return static_cast<uint_fast8_t>(NUMBER_OF_CORE);
#elif defined(NO_THREAD_ALLOWED)
        return 0;
#else
        return std::thread::hardware_concurrency();
#endif
    }


    /**
     * @brief returns the prime number used in the fnv32-a hashing
     * @return the prime number used in the fnv32-a hashing
     */
    constexpr uint32_t fnv32_prime() { return static_cast<uint32_t>(FD_CORE_FNV32_PRIME); }


    /**
     * @brief returns the initial value used in the fnv32-a hashing
     * @return the initial value used in the fnv32-a hashing
     */
    constexpr uint32_t fnv32_init() { return static_cast<uint32_t>(FD_CORE_FNV32_INIT); }

    /**
     * @brief hashes a string using fnv32-a algorithm
     * @param str the string to hash
     * @param hval the initial value of the hash (used for concatenation hash)
     * @return fnv32-a hash value
     */
    uint32_t fnv_32a_str(char *str, uint32_t hval);


    /**
     * @brief hashes a string using fnv32-a algorithm
     * @param str the string to hash
     * @return fnv32-a hash value
     */
    inline uint32_t fnv_32a_str(char *str) { return fnv_32a_str(str, fnv32_init()); };


    /**
     * @brief eliminates elements from a STL vector to reduce its size
     * @param v the vector where the item must be erased
     * @param item the item to delete
     */
    template<typename T>
    void remove(std::vector<T> v, const T &item)
    {
        v.erase(std::remove(v.begin(), v.end(), item), v.end());
    }


    /**
     * @brief eliminates elements from a STL vector to reduce its size
     * @param v the vector where the item must be erased
     * @param pred a predicate that says whether or not an item must be erase
     */
    template<typename T, typename Pred>
    void remove_if(std::vector<T> v, Pred pred)
    {
        v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());
    }

    template<typename T, typename PtrType = T>
    T *alignMemory(PtrType *toAlign, size_t Align)
    {
        return reinterpret_cast<T *>((reinterpret_cast<unsigned int>(toAlign) + Align) &
                                     ~(Align - 1));
    }

    typedef uint8_t *handle_ptr;

    typedef int8_t byte;
    typedef int16_t word;
    typedef int32_t dword;
    typedef int64_t qword;

    typedef uint8_t ubyte;
    typedef uint16_t uword;
    typedef uint32_t udword;
    typedef uint64_t uqword;
} // namespace FDCore

#endif
