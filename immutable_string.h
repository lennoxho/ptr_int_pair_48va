#pragma once

#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#ifdef __cpp_lib_string_view
#include <string_view>
#endif

#include "ptr_int_pair_48va.h"

#ifndef ASSERT
#define ASSERT(X) assert(X)
#endif

#ifdef __cpp_constexpr
#if __cpp_constexpr >= 201304
#define CXX_14_CONSTEXPR constexpr
#else 
#define CXX_14_CONSTEXPR
#endif
#else
#define CXX_14_CONSTEXPR
#endif

#ifdef __has_cpp_attribute
#if __has_cpp_attribute(nodiscard)
#define NODISCARD [[nodiscard]]
#else 
#define NODISCARD
#endif
#else 
#define NODISCARD
#endif

struct constexpr_op_t {};
static constexpr constexpr_op_t constexpr_op;

template <typename CharType>
class basic_immutable_string_impl { basic_immutable_string_impl() = delete; };

template <typename CharType>
class basic_immutable_string { basic_immutable_string() = delete; };

template <typename CharType, typename Comparator>
using basic_immutable_string_view = basic_immutable_string_impl<CharType>;

namespace detail {

    template <typename T, typename... L>
    struct is_in {
        static constexpr bool value = false;
    };

    template <typename T, typename F, typename... R>
    struct is_in<T, F, R...> {
        static constexpr bool value = std::is_same<T, F>::value ||
                                      is_in<T, R...>::value;
    };

    template <typename T, typename CharType, typename Comparator, typename = void>
    struct is_comparator_immutable_string : public std::false_type {};

    template <typename T, typename CharType, typename Comparator>
    struct is_comparator_immutable_string<T, CharType, Comparator,
                                          std::enable_if_t<is_in<std::decay_t<T>,
                                          basic_immutable_string_impl<CharType>,
                                          basic_immutable_string<CharType>,
                                          basic_immutable_string_view<CharType, Comparator>>::value>> : public std::true_type {};

}

constexpr std::size_t ct_strlen(const char* str) {
    return *str == '\0' ? 0
                        : ct_strlen(str + 1) + 1;
}

template <>
class basic_immutable_string_impl<char> {

public:

    using value_type = const char;
    using size_type = std::uint16_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = reference;
    using pointer = value_type*;
    using const_pointer = pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = iterator;
    using const_reverse_iterator = const_iterator;

    using buffer_impl_type = ptr_int_pair_48va<value_type, size_type>;

protected:

    union buffer_type {
        char raw[buffer_impl_type::ptr_size_requirement];
        buffer_impl_type impl;

        constexpr buffer_type()
        :impl{}
        {}

        constexpr buffer_type(const_pointer str, size_type sz)
        :impl{ str, sz }
        {}

        constexpr buffer_type(const buffer_type &other) 
        :impl{ other.impl }
        {}
    } m_buffer;

    static_assert(sizeof(buffer_type) == sizeof(buffer_impl_type), "Alignment check failed");

    template <typename T>
    static inline size_type check_size(const T &size) {
        ASSERT(size <= max_size());
        return static_cast<size_type>(size);
    }

    template <typename T>
    static constexpr size_type ct_check_size(const T &size) {
        return size <= max_size() ? static_cast<size_type>(size)
                                  : throw std::out_of_range{ "" };
    }

    template <typename T>
    static inline const_pointer check_null(const_pointer str, const T &sz) {
        ASSERT(str[sz] == '\0');
        return str;
    }

    template <typename T>
    static constexpr const_pointer ct_check_null(const_pointer str, const T &sz) {
        return str[sz] == '\0' ? str
                               : throw std::out_of_range{ "" };
    }

    inline basic_immutable_string_impl(buffer_type buf) noexcept 
    :m_buffer{ buf }
    {}

public:

    constexpr basic_immutable_string_impl() {}

    template <typename Traits, typename Allocator>
    basic_immutable_string_impl(const std::basic_string<value_type, Traits, Allocator> &str)
    :m_buffer{ str.c_str(), check_size(str.size()) }
    {}

    explicit basic_immutable_string_impl(const_pointer str, size_type sz)
    :m_buffer{ check_null(str, sz), sz }
    {}

    explicit constexpr basic_immutable_string_impl(constexpr_op_t, const_pointer str, size_type sz)
    :m_buffer{ ct_check_null(str, sz), sz }
    {}

    basic_immutable_string_impl(const_pointer str)
    :m_buffer{ str, check_size(std::strlen(str)) }
    {}

    constexpr basic_immutable_string_impl(constexpr_op_t, const_pointer str)
    :m_buffer{ str, ct_check_size(ct_strlen(str)) }
    {}

#ifdef __cpp_lib_string_view
    template <typename Traits>
    basic_immutable_string_impl(const std::basic_string_view<value_type, Traits> &view)
    :m_buffer{ check_null(view.data(), view.size()), check_size(view.size()) }
    {}

    template <typename Traits>
    constexpr basic_immutable_string_impl(constexpr_op_t, const std::basic_string_view<value_type, Traits> &view)
    :m_buffer{ ct_check_null(view.data(), view.size()), ct_check_size(view.size()) }
    {}
#endif

    basic_immutable_string_impl(const basic_immutable_string<char> &str) noexcept;

    template <typename Traits, typename Allocator>
    inline basic_immutable_string_impl &operator=(const std::basic_string<value_type, Traits, Allocator> &str) {
        m_buffer = buffer_type{ str.c_str(), check_size(str.size()) };
        return *this;
    }

    inline basic_immutable_string_impl &operator=(const_pointer str) {
        m_buffer = buffer_type{ str, check_size(std::strlen(str)) };
        return *this;
    }

#ifdef __cpp_lib_string_view
    template <typename Traits>
    inline basic_immutable_string_impl &operator=(const std::basic_string_view<value_type, Traits> &view) {
        m_buffer = buffer_type{ check_null(view.data(), view.size()), check_size(view.size()) };
        return *this;
    }
#endif

    basic_immutable_string_impl &operator=(const basic_immutable_string<char> &str) noexcept;

    const_reference at(size_type pos) const {
        ASSERT(pos < size());
        return operator[](pos);
    }

    constexpr const_reference at(constexpr_op_t, size_type pos) const {
        return pos < size() ? operator[](pos)
                             : (throw std::out_of_range{ "" }, operator[](pos));
        // Use comma operator to stop the compiler from complaining.
    }

    constexpr const_reference operator[](size_type pos) const {
        return data()[pos];
    }

    constexpr const_reference front() const {
        return operator[](0);
    }

    constexpr const_reference back() const {
        return operator[](size() - 1);
    }

    constexpr const_pointer data() const {
        return size() == 0 ? m_buffer.raw
                           : m_buffer.impl.pointer();
    }

    constexpr const_pointer c_str() const {
        return data();
    }

    constexpr const_iterator begin() const {
        return data();
    }

    constexpr const_iterator cbegin() const {
        return begin();
    }

    constexpr const_iterator end() const {
        return data() + size();
    }

    constexpr const_iterator cend() const {
        return end();
    }

    constexpr const_iterator rbegin() const {
        return end() - 1;
    }

    constexpr const_iterator crbegin() const {
        return rbegin();
    }

    constexpr const_iterator rend() const {
        return begin() - 1;
    }

    constexpr const_iterator crend() const {
        return rend();
    }

    NODISCARD constexpr bool empty() const {
        return size() == 0;
    }

    constexpr size_type size() const {
        return m_buffer.impl.integer();
    }

    constexpr size_type length() const {
        return size();
    }

    static constexpr size_type max_size() {
        return std::numeric_limits<size_type>::max();
    }

    inline void swap(basic_immutable_string_impl &other) noexcept {
        m_buffer.impl.swap(other.m_buffer.impl);
    }

    static constexpr size_type npos = -1;
};

template <>
class basic_immutable_string<char> : public basic_immutable_string_impl<char> {

    using base_type = basic_immutable_string_impl<char>;
    using buffer_impl_type = typename base_type::buffer_impl_type;

public:

    using value_type = typename base_type::value_type;
    using const_pointer = typename base_type::const_pointer;
    using size_type = typename base_type::size_type;

private:

    inline void allocate_and_copy(const_pointer str, size_type sz) {
        if (sz == 0) return;

        auto ptr = new char[sz + 1];
        ASSERT(ptr != nullptr);

        std::memcpy(ptr, str, sz);
        ptr[sz] = '\0';
        base_type::m_buffer.impl = buffer_impl_type{ ptr, static_cast<size_type>(sz) };
    }

public:

    constexpr basic_immutable_string() {}

    template <typename Traits, typename Allocator>
    basic_immutable_string(const std::basic_string<value_type, Traits, Allocator> &str) {
        allocate_and_copy(str.c_str(), base_type::check_size(str.size()));
    }

    explicit basic_immutable_string(size_type sz, value_type c) {
        if (sz == 0) return;

        auto ptr = new char[sz + 1];
        ASSERT(ptr != nullptr);

        std::uninitialized_fill_n(ptr, sz, c);
        ptr[sz] = '\0';
        base_type::m_buffer.impl = buffer_impl_type{ ptr, sz };
    }

    explicit basic_immutable_string(const_pointer str, size_type sz) {
        allocate_and_copy(base_type::check_null(str, sz), sz);
    }
    
    basic_immutable_string(const_pointer str) {
        allocate_and_copy(str, base_type::check_size(std::strlen(str)));
    }

#ifdef __cpp_lib_string_view
    template <typename Traits>
    basic_immutable_string(const std::basic_string_view<value_type, Traits> &view) {
        allocate_and_copy(base_type::check_null(view.data(), view.size()), base_type::check_size(view.size()));
    }
#endif

    explicit basic_immutable_string(const base_type &impl) {
        allocate_and_copy(impl.data(), impl.size());
    }

    basic_immutable_string(std::unique_ptr<char[]> &&uptr) {
        auto sz = base_type::check_size(std::strlen(uptr.get()));
        if (sz > 0) {
            base_type::m_buffer.impl = buffer_impl_type{ uptr.release(), sz };
        }
    }

    basic_immutable_string(basic_immutable_string &&other) noexcept {
        base_type::m_buffer.impl.swap(other.m_buffer.impl);
    }

    inline auto release() noexcept {
        // We kinda own the data?
        auto ptr = const_cast<char*>(base_type::data());
        base_type::m_buffer.impl.clear();
        return std::unique_ptr<char[]>{ ptr };
    }

    inline basic_immutable_string &operator=(basic_immutable_string &&other) noexcept {
        release();
        base_type::m_buffer.impl.swap(other.m_buffer.impl);
        return *this;
    }

    inline basic_immutable_string dup() {
        basic_immutable_string tmp;
        tmp.allocate_and_copy(base_type::c_str(), base_type::size());
        return tmp;
    }

    ~basic_immutable_string() {
        auto sz = base_type::size();
        if (sz > 0) {
            delete[] base_type::data();
        }
    }

    inline void swap(basic_immutable_string &other) noexcept {
        base_type::swap(other);
    }

};

basic_immutable_string_impl<char>::basic_immutable_string_impl(const basic_immutable_string<char> &str) noexcept
:m_buffer{ str.m_buffer }
{}

basic_immutable_string_impl<char> &basic_immutable_string_impl<char>::operator=(const basic_immutable_string<char> &str) noexcept {
    m_buffer = buffer_type{ str.m_buffer };
    return *this;
}

template <typename CharType, typename Comparator, typename Rhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, CharType, Comparator>::value, bool> 
operator<(const basic_immutable_string_view<CharType, Comparator> &lhs, 
          const Rhs &rhs) noexcept
{
    return Comparator::lt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Lhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, CharType, Comparator>::value, bool>
operator<(const Lhs &lhs, 
          const basic_immutable_string_view<CharType, Comparator> &rhs) noexcept
{
    return Comparator::lt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Rhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, CharType, Comparator>::value, bool> 
operator>(const basic_immutable_string_view<CharType, Comparator> &lhs, 
          const Rhs &rhs) noexcept
{
    return Comparator::gt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Lhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, CharType, Comparator>::value, bool>
operator>(const Lhs &lhs, 
          const basic_immutable_string_view<CharType, Comparator> &rhs) noexcept
{
    return Comparator::gt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Rhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, CharType, Comparator>::value, bool>
operator>=(const basic_immutable_string_view<CharType, Comparator> &lhs,
           const Rhs &rhs) noexcept
{
    return !Comparator::lt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Lhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, CharType, Comparator>::value, bool>
operator>=(const Lhs &lhs,
           const basic_immutable_string_view<CharType, Comparator> &rhs) noexcept
{
    return !Comparator::lt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Rhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, CharType, Comparator>::value, bool> 
operator<=(const basic_immutable_string_view<CharType, Comparator> &lhs, 
           const Rhs &rhs) noexcept
{
    return !Comparator::gt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Lhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, CharType, Comparator>::value, bool>
operator<=(const Lhs &lhs, 
           const basic_immutable_string_view<CharType, Comparator> &rhs) noexcept
{
    return !Comparator::gt(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Rhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, CharType, Comparator>::value, bool> 
operator==(const basic_immutable_string_view<CharType, Comparator> &lhs, 
           const Rhs &rhs) noexcept
{
    return Comparator::eq(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Lhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, CharType, Comparator>::value, bool>
operator==(const Lhs &lhs, 
           const basic_immutable_string_view<CharType, Comparator> &rhs) noexcept
{
    return Comparator::eq(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Rhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, CharType, Comparator>::value, bool> 
operator!=(const basic_immutable_string_view<CharType, Comparator> &lhs, 
           const Rhs &rhs) noexcept
{
    return !Comparator::eq(lhs, rhs);
}
template <typename CharType, typename Comparator, typename Lhs>
inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, CharType, Comparator>::value, bool>
operator!=(const Lhs &lhs, 
           const basic_immutable_string_view<CharType, Comparator> &rhs) noexcept
{
    return !Comparator::eq(lhs, rhs);
}

namespace std {

    template <typename CharType, typename Traits>
    inline std::basic_ostream<CharType, Traits> &operator<<(std::basic_ostream<CharType, Traits> &os, 
                                                            const basic_immutable_string_impl<CharType> &str)
    {
        return os.write(str.c_str(), str.size());
    }

    template <typename CharType, typename Traits>
    inline std::basic_ostream<CharType, Traits> &operator<<(std::basic_ostream<CharType, Traits> &os,
                                                            const basic_immutable_string<CharType> &str)
    {
        return os.write(str.c_str(), str.size());
    }

    template <typename CharType>
    inline void swap(basic_immutable_string_impl<CharType> &lhs, basic_immutable_string_impl<CharType> &rhs) noexcept {
        lhs.swap(rhs);
    }

    template <typename CharType>
    inline void swap(basic_immutable_string<CharType> &lhs, basic_immutable_string<CharType> &rhs) noexcept {
        lhs.swap(rhs);
    }

}

using immutable_string_impl = basic_immutable_string_impl<char>;
using immutable_string = basic_immutable_string<char>;
template <typename Comparator>
using immutable_string_view = basic_immutable_string_view<char, Comparator>;