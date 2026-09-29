// Developed by Pavlo Vus on 16.04.2026
#pragma once

template<std::size_t N = 16>

class Word
{
    static_assert(N >= 2, "Буфер Word повинен бути щонайменше 2 байти");

    char _buf[N];
    std::size_t _len;

    //Допоміжний приватний конструктор
    Word(const char* s, const std::size_t n) noexcept : _buf{}, _len{(n < N - 1) ? n : (N - 1)}
    {
        if (s && _len > 0) std::memcpy(_buf, s, _len);
    }

public:
    //Конструктори
    Word() noexcept : _buf{}, _len{0} {}
    explicit Word(const std::string& s) : Word(s.data(), s.size()) {}
    explicit Word(const char* s) : Word(s, s ? std::strlen(s) : 0) {}

    bool operator<(const Word& o) const noexcept { return std::strcmp(_buf, o._buf) < 0; }

    bool operator==(const Word& o) const noexcept
    {
        return _len == o._len && std::memcmp(_buf, o._buf, _len) == 0;
    }

    //Селектори
    [[nodiscard]] std::size_t length() const noexcept { return _len; }
    [[nodiscard]] const char* c_str() const noexcept { return _buf; }
    [[nodiscard]] std::string str() const { return {_buf, _len}; }
};

template<std::size_t N = 16>
std::ostream& operator<<(std::ostream& os, const Word<N> & w) { return os << w.c_str(); }