#pragma once 

#include <cstdint>
#include <limits>

template <typename PtrType, typename IntType>
class ptr_int_pair_48va {
    
    //
    // Constants
    //

    static constexpr int ptr_size_requirement = 8;
    static constexpr int int_size_limit = 2;

    static constexpr int high_bits_offset = 48;
    static constexpr std::uintptr_t high_bits_mask_set = std::uintptr_t(std::numeric_limits<std::uint16_t>::max()) << high_bits_offset;
    static constexpr std::uintptr_t high_bits_mask_flip = ~high_bits_mask_set;
    static constexpr std::uintptr_t bit_47_mask = std::uintptr_t(1) << 47;

    static_assert(sizeof(void*) == ptr_size_requirement, "ptr_int_pair_48va is only supported on 64 bit machines");
    static_assert(sizeof(IntType) <= int_size_limit, "The given IntType is larger than 2 bytes");
    
    //
    // Buffer details
    //

    struct view_type {
        char p[6];
        // Have to do this acrobatics because VC++ refuses to support 
        // bitfields larger than the size of IntType.
        union int_type {
            IntType v;
            char p[2];
        } i;
    };

    static_assert(sizeof(view_type) == ptr_size_requirement, "Alignment check failed");

    union buffer_type {
        std::uintptr_t raw;
        view_type view;

        constexpr buffer_type(std::uintptr_t raw)
        :raw{ raw }
        {}
    };

    static_assert(sizeof(buffer_type) == ptr_size_requirement, "Alignment check failed");

    //
    // Member variables
    //

    buffer_type m_buffer;

    //
    // Helper functions
    //

    static constexpr bool is_bit_47_set(std::uintptr_t raw) {
        return raw & bit_47_mask;
    }

    static constexpr std::uintptr_t compact_ptr_int_pair_helper(std::uintptr_t ptr_raw, std::uintptr_t i_offset) {
        return is_bit_47_set(ptr_raw) ? (i_offset | high_bits_mask_flip) & ptr_raw
                                      : i_offset | ptr_raw;
    }

    static constexpr std::uintptr_t compact_ptr_int_pair(PtrType* ptr, IntType i) {
        return compact_ptr_int_pair_helper(reinterpret_cast<std::uintptr_t>(ptr), static_cast<std::uintptr_t>(i) << high_bits_offset);
    }

public:
    
    //
    // Constructors
    //

    constexpr ptr_int_pair_48va()
    :m_buffer{ 0 }
    {}

    ptr_int_pair_48va(PtrType* ptr) noexcept
    :m_buffer{ compact_ptr_int_pair(ptr, IntType{}) }
    {}
    
    ptr_int_pair_48va(PtrType* ptr, IntType i) noexcept
    :m_buffer{ compact_ptr_int_pair(ptr, i) }
    {}

    //
    // Accessors
    //

    constexpr PtrType* pointer() const {
        return is_bit_47_set(m_buffer.raw) ? reinterpret_cast<PtrType*>(m_buffer.raw | high_bits_mask_set)
                                           : reinterpret_cast<PtrType*>(m_buffer.raw & high_bits_mask_flip);
    }

    constexpr IntType integer() const {
        return m_buffer.view.i.v;
    }

    inline void pointer(PtrType* ptr) noexcept {
        std::uintptr_t i = m_buffer.raw & high_bits_mask_set;
        m_buffer.raw = compact_ptr_int_pair_helper(reinterpret_cast<std::uintptr_t>(ptr), i);
    }

    inline void integer(IntType i) noexcept {
        m_buffer.view.i.v = i;
    }

    //
    // Comparators
    //
    // We cannot just do a raw buffer comparison because the buffer
    // reserved for IntType may have uninitialised padding.
    //

    constexpr bool operator==(const ptr_int_pair_48va &other) const {
        std::uintptr_t lhs_ptr = m_buffer.raw & high_bits_mask_flip;
        std::uintptr_t rhs_ptr = other.m_buffer.raw & high_bits_mask_flip;
        return lhs_ptr == rhs_ptr &&
               integer() == other.integer();
    }

    constexpr bool operator!=(const ptr_int_pair_48va &other) const {
        return !operator==(other);
    }

    constexpr bool operator<(const ptr_int_pair_48va &other) const {
        std::uintptr_t lhs_ptr = m_buffer.raw & high_bits_mask_flip;
        std::uintptr_t rhs_ptr = other.m_buffer.raw & high_bits_mask_flip;
        return lhs_ptr < rhs_ptr ||
               (lhs_ptr == rhs_ptr && integer() < other.integer());
    }
};