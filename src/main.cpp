#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

/**
 * @brief A struct to check if a type is a tuple
 * @tparam T The type to check
 */
template <typename T>
struct is_tuple : std::false_type {};

/**
 * @brief A specialization of the is_tuple struct for tuples
 * @tparam Args The types of the tuple elements
 */
template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};

/**
 * @brief A helper function to print the elements of a tuple
 * @tparam T The type of the tuple
 * @tparam Is The indices of the tuple elements
 * @param t The tuple to print
 * @param seq The sequence of indices
 */
template <typename T, std::size_t... Is>
void print_tuple(const T& t, std::index_sequence<Is...>) noexcept
{
    int _[]{ 0, (std::cout << (Is > 0 ? "." : "") << std::get<Is>(t), 0)... };
    (void)_;
}

/**
 * @brief A function to print an integral value as an IP address
 * @tparam T The type of the value
 * @param value The value to print
 */
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void>
print_ip(T value) noexcept
{
    for (size_t i = 0; i < sizeof(T); ++i)
    {
        if (i != 0)
        {
            std::cout << ".";
        }
        std::cout << static_cast<int>((value >> (8 * (sizeof(T) - i - 1))) & 0xFF);
    }
    std::cout << std::endl;
}

/**
 * @brief A function to print a string as an IP address
 * @tparam T The type of the string
 * @param value The string to print
 */
template <typename T>
std::enable_if_t<std::is_same_v<T, std::string>, void>
print_ip(T value) noexcept
{
    std::cout << value << std::endl;
}

/**
 * @brief A function to print a tuple as an IP address
 * @tparam T The type of the tuple
 * @param value The tuple to print
 */
template <typename T>
std::enable_if_t<is_tuple<T>::value, void>
print_ip(T value) noexcept
{
    print_tuple(value, std::make_index_sequence<std::tuple_size_v<T>>{});
    std::cout << std::endl;
}

/**
 * @brief A function to print a container as an IP address
 * @tparam T The type of the container
 * @param value The container to print
 */
template <typename T>
std::enable_if_t<std::is_same_v<T, std::vector<typename T::value_type, typename T::allocator_type>> ||
    std::is_same_v<T, std::list<typename T::value_type, typename T::allocator_type>>, void>
    print_ip(T value) noexcept
{
    auto it = value.begin();
    while (it != value.end())
    {
        std::cout << *it;
        if (++it != value.end())
        {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

/**
 * @brief The main function to demonstrate the print_ip function
 * @return 0 on successful execution
 */
int main() noexcept
{
    print_ip(int8_t{ -1 }); // 255
    print_ip(int16_t{ 0 }); // 0.0
    print_ip(int32_t{ 2130706433 }); // 127.0.0.1
    print_ip(int64_t{ 8875824491850138409 }); // 123.45.67.89.101.112.131.41
    print_ip(std::string{ "Hello, World!" }); // Hello, World!
    print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0

    return 0;
}
