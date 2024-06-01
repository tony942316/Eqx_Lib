export module Equinox.Misc:Decl;

import Eqx.Stdm;

export namespace eqx
{
    using ssize_t = stdm::make_signed_t<stdm::size_t>;

    template <typename T>
    inline constexpr auto nullp = static_cast<T*>(nullptr);

    template <typename T>
    concept StringConvertable =
        requires(const T& val) { stdm::to_string(val); };

    template <typename T>
    concept StringConstructable =
        requires(const T& val) { stdm::string{ val }; };

    template <typename T>
    concept Streamable =
        requires(const T& val, stdm::ostream& out) { out << val; };

    template <typename T, typename F>
        requires requires(const F& f) { static_cast<T>(f); }
    [[nodiscard]] constexpr T staticCast(const F& f) noexcept;

    template <typename T>
        requires StringConstructable<T>
    [[nodiscard]] constexpr stdm::string toString(const T& val) noexcept;

    template <typename T>
        requires StringConvertable<T> && (!StringConstructable<T>)
    [[nodiscard]] stdm::string toString(const T& val) noexcept;

    template <typename T, typename U>
        requires requires(const stdm::pair<T, U>& val)
            { eqx::toString(val.first); eqx::toString(val.second); }
    [[nodiscard]] constexpr stdm::string
        toString(const stdm::pair<T, U>& val) noexcept;

    template <typename T>
        requires stdm::ranges::range<T>
            && (!StringConstructable<T>)
            && (!StringConvertable<T>)
    [[nodiscard]] constexpr stdm::string toString(const T& val) noexcept;

    [[nodiscard]] constexpr char toLower(char val) noexcept;

    [[nodiscard]] constexpr stdm::string
        toLower(const stdm::string_view str) noexcept;

    [[nodiscard]] constexpr stdm::vector<stdm::string> parseString(
        const stdm::string_view str, const stdm::string_view pat) noexcept;

    template <typename T>
        requires eqx::Streamable<T>
    void print(const T& msg, stdm::ostream& out) noexcept;

    template <typename T>
        requires (!eqx::Streamable<T>) &&
            requires(const T& val) { eqx::toString(val); }
    void print(const T& msg, stdm::ostream& out) noexcept;

    template <typename T>
    void print(const T& msg) noexcept;

    template <typename T>
    void println(const T& msg, stdm::ostream& out) noexcept;

    template <typename T>
    void println(const T& msg) noexcept;

    constexpr void ensure(const bool expr,
        const stdm::string_view msg = stdm::string_view{},
        const stdm::source_location& loc = stdm::source_location::current())
        noexcept;

    consteval void noOp() noexcept;
}

export namespace eqx::stream
{
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    stdm::ostream& operator<< (stdm::ostream& outStream, const T& val);
}

export namespace eqx::literals
{
    consteval stdm::size_t operator""_size (unsigned long long val) noexcept;

    consteval stdm::size_t operator""_uz (unsigned long long val) noexcept;

    consteval eqx::ssize_t operator""_z (unsigned long long val) noexcept;

    consteval short operator""_short (unsigned long long val) noexcept;

    consteval unsigned short operator""_ushort (unsigned long long val)
        noexcept;

    consteval stdm::int8_t operator""_i8 (unsigned long long val) noexcept;

    consteval stdm::int16_t operator""_i16 (unsigned long long val) noexcept;

    consteval stdm::int32_t operator""_i32 (unsigned long long val) noexcept;

    consteval stdm::int64_t operator""_i64 (unsigned long long val) noexcept;

    consteval stdm::uint8_t operator""_u8 (unsigned long long val) noexcept;

    consteval stdm::uint16_t operator""_u16 (unsigned long long val) noexcept;

    consteval stdm::uint32_t operator""_u32 (unsigned long long val) noexcept;

    consteval stdm::uint64_t operator""_u64 (unsigned long long val) noexcept;

    consteval unsigned long long operator""_KB (unsigned long long val)
        noexcept;
}
