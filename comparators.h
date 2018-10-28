#pragma once

#include "immutable_string.h"

struct string_compare_loose {
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_loose>::value, bool>
    lt(const basic_immutable_string_view<char, string_compare_loose> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        return lhs.size() < rhs.size() || 
               (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) < 0);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_loose>::value, bool>
    lt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_loose> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        return lhs.size() < rhs.size() || 
               (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) < 0);
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_loose>::value, bool>
    gt(const basic_immutable_string_view<char, string_compare_loose> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        return lhs.size() > rhs.size() || 
               (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) > 0);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_loose>::value, bool>
    gt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_loose> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        return lhs.size() > rhs.size() || 
               (lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) > 0);
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_loose>::value, bool>
    eq(const basic_immutable_string_view<char, string_compare_loose> &lhs,
       const Rhs &rhs) noexcept
    {
        return lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_loose>::value, bool>
    eq(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_loose> &rhs) noexcept
    {
        return lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }
};

struct string_compare_weak {
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_weak>::value, bool>
    lt(const basic_immutable_string_view<char, string_compare_weak> &lhs,
       const Rhs &rhs) noexcept
    {
        return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_weak>::value, bool>
    lt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_weak> &rhs) noexcept
    {
        return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_weak>::value, bool>
    gt(const basic_immutable_string_view<char, string_compare_weak> &lhs,
       const Rhs &rhs) noexcept
    {
        return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_weak>::value, bool>
    gt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_weak> &rhs) noexcept
    {
        return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_weak>::value, bool>
    eq(const basic_immutable_string_view<char, string_compare_weak> &lhs,
       const Rhs &rhs) noexcept
    {
        return lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_weak>::value, bool>
    eq(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_weak> &rhs) noexcept
    {
        return lhs.size() == rhs.size() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }
};

struct string_compare_safe {
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_safe>::value, bool>
    lt(const basic_immutable_string_view<char, string_compare_safe> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::strncmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp < 0 || (cmp == 0 && lhs_len < rhs_len);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_safe>::value, bool>
    lt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_safe> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::strncmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp < 0 || (cmp == 0 && lhs_len < rhs_len);
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_safe>::value, bool>
    gt(const basic_immutable_string_view<char, string_compare_safe> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::strncmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp > 0 || (cmp == 0 && lhs_len > rhs_len);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_safe>::value, bool>
    gt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_safe> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::strncmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp > 0 || (cmp == 0 && lhs_len > rhs_len);
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_safe>::value, bool>
    eq(const basic_immutable_string_view<char, string_compare_safe> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        return lhs_len == rhs.size() && std::strncmp(lhs.c_str(), rhs.c_str(), lhs_len);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_safe>::value, bool>
    eq(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_safe> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        return lhs_len == rhs.size() && std::strncmp(lhs.c_str(), rhs.c_str(), lhs_len);
    }
};

struct string_compare_pendatic {
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_pendatic>::value, bool>
    lt(const basic_immutable_string_view<char, string_compare_pendatic> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::memcmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp < 0 || (cmp == 0 && lhs_len < rhs_len);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_pendatic>::value, bool>
    lt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_pendatic> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::memcmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp < 0 || (cmp == 0 && lhs_len < rhs_len);
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_pendatic>::value, bool>
    gt(const basic_immutable_string_view<char, string_compare_pendatic> &lhs,
        const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::memcmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp > 0 || (cmp == 0 && lhs_len > rhs_len);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_pendatic>::value, bool>
    gt(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_pendatic> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        auto rhs_len = rhs.size();
        auto cmp = std::memcmp(lhs.c_str(), rhs.c_str(), std::min(lhs_len, rhs_len));
        return cmp > 0 || (cmp == 0 && lhs_len > rhs_len);
    }
    template <typename Rhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Rhs, char, string_compare_pendatic>::value, bool>
    eq(const basic_immutable_string_view<char, string_compare_pendatic> &lhs,
       const Rhs &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        return lhs_len == rhs.size() && std::memcmp(lhs.c_str(), rhs.c_str(), lhs_len);
    }
    template <typename Lhs>
    static inline std::enable_if_t<detail::is_comparator_immutable_string<Lhs, char, string_compare_pendatic>::value, bool>
    eq(const Lhs &lhs,
       const basic_immutable_string_view<char, string_compare_pendatic> &rhs) noexcept
    {
        auto lhs_len = lhs.size();
        return lhs_len == rhs.size() && std::memcmp(lhs.c_str(), rhs.c_str(), lhs_len);
    }
};
