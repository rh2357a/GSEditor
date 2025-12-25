#ifndef _POKEGOLD_ADDRESS_H_
#define _POKEGOLD_ADDRESS_H_

#include <vector>

namespace pokegold {

class address
{
private:
    bool m_encoded_bank;
    u32 m_address;

public:
    address() : m_encoded_bank(false), m_address(0) {}
    address(u32 addr) : m_encoded_bank(false), m_address(addr) {}
    address(u8 bank, u16 addr) : m_encoded_bank(false), m_address((bank * 0x4000) | (addr - 0x4000)) {}
    address(u8 bank, const std::vector<u8> &addr_bytes) : m_encoded_bank(false), m_address((bank * 0x4000) | ((addr_bytes[0] | addr_bytes[1] << 8) - 0x4000)) {}
    address(const std::vector<u8> &addr_bytes) : m_encoded_bank(false), m_address((addr_bytes[0] * 0x4000) | ((addr_bytes[1] | addr_bytes[2] << 8) - 0x4000)) {}
    ~address() = default;

    /// @brief 이미지 전용 뱅크 변환
    /// @param addr_bytes 3-bytes 포인터
    /// @return address
    static address encoded_bank(const std::vector<u8> &addr_bytes)
    {
        u8 bank;
        switch (addr_bytes[0])
        {
        case 0x13:
            bank = 0x1f;
            break;
        case 0x14:
            bank = 0x20;
            break;
        case 0x1f:
            bank = 0x2e;
            break;
        default:
            bank = addr_bytes[0];
            break;
        }

        u16 ptr = (addr_bytes[1] | addr_bytes[2] << 8);
        return address(bank, ptr);
    }

public:
    u8 get_bank() { return static_cast<u8>(m_address / 0x4000); }

    std::vector<u8> to_bytes(bool ignore_bank = false)
    {
        std::vector<u8> bytes;
        if (!ignore_bank)
        {
            // TODO: encoded bank 수정...
            bytes.push_back(static_cast<u8>(m_address / 0x4000));
        }

        u32 a = m_address % 0x4000 + (m_address >= 0x4000 ? 0x4000 : 0);
        bytes.push_back(static_cast<u8>(a & 0xff));
        bytes.push_back(static_cast<u8>((a & 0xff00) >> 8));

        return bytes;
    }

public:
    operator size_t() const { return m_address; }

    friend address operator+(const address &addr, size_t offset)
    {
        address result = addr;
        result += offset;
        return result;
    }

    address &operator+=(size_t offset)
    {
        this->m_address += offset;
        return *this;
    }

    friend address operator-(const address &addr, size_t offset)
    {
        address result = addr;
        result -= offset;
        return result;
    }

    address &operator-=(size_t offset)
    {
        this->m_address -= offset;
        return *this;
    }
};

} // namespace pokegold

#endif
