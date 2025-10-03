// Timer.cpp

export module Eqx.Lib.Timer;

import <Eqx/std.hpp>;

using namespace std::literals;

export namespace eqx::lib
{
    class Timer
    {
    public:
        Timer() = default;
        Timer(const Timer&) = default;
        Timer(Timer&&) = default;
        Timer& operator= (const Timer&) = default;
        Timer& operator= (Timer&&) = default;
        ~Timer() = default;

        inline void start() noexcept
        {
            m_start = std::chrono::steady_clock::now();
        }

        inline void end() noexcept
        {
            m_end = std::chrono::steady_clock::now();
        }

        [[nodiscard]] inline double read() noexcept
        {
            this->end();
            return this->seconds();
        }

        [[nodiscard]] inline float readf() noexcept
        {
            this->end();
            return this->secondsf();
        }

        [[nodiscard]] constexpr double seconds() const noexcept
        {
            return std::chrono::duration<double>(
                this->m_end - this->m_start).count();
        }

        [[nodiscard]] constexpr float secondsf() const noexcept
        {
            return std::chrono::duration<float>(
                this->m_end - this->m_start).count();
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> m_start;
        std::chrono::time_point<std::chrono::steady_clock> m_end;
    };
}
