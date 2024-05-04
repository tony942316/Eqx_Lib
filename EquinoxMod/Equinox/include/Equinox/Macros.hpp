#ifndef EQUINOX_MACROS_HPP
#define EQUINOX_MACROS_HPP

#ifdef EQX_NO_ASSERTS
#define ENSURE_HARD(...) noOp();
#define EQX_NO_ASSERTS true
#else
#define ENSURE_HARD(...) ensure(__VA_ARGS__);
#define EQX_NO_ASSERTS false
#endif // EQX_NO_ASSERTS

#endif // EQUINOX_MACROS_HPP
