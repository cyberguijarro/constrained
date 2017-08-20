#pragma once

#include <stdexcept>
#include <limits>
#include <type_traits>

template<
   typename T,
   long _Min = std::numeric_limits<long>::min(),
   long _Max = std::numeric_limits<long>::max()
>
struct limits
{
   static constexpr T Min = _Min;
   static constexpr T Max = _Max;
};

template<typename T, typename Limits>
class constrained
{
private:
   T x;

public:
   constexpr constrained() noexcept : x(Limits::Min)
   {
   }

   constexpr constrained(const T x) noexcept
   {
      operator=(x);
   }

   constexpr constrained<T, Limits>& operator=(const T _x)
#ifdef NDEBUG
      noexcept
#endif
   {
#ifdef NDEBUG
      x = _x;
#else
      if (_x >= Limits::Min && _x <= Limits::Max) {
         x = _x;
      } else {
         throw std::domain_error("Value is not within range");
      }
#endif

      return *this;
   }

   constexpr operator T() const noexcept
   {
      return x;
   }
};

template<typename T, T Min, T Max>
using constrained_integral = constrained<T, limits<T, Min, Max>>;

template<typename T>
using normalized = constrained<T, limits<T, 0, 1>>;

template<typename T>
using negative = constrained<T, limits<T, std::numeric_limits<T>::min(), 0>>;

template<typename T>
using positive = constrained<T, limits<T, 0>>;
