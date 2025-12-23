#ifndef UTILS_RESULT_HXX
#define UTILS_RESULT_HXX

#include <concepts>
#include <exception>
#include <variant>

namespace utils {

template <class Ok, class Ko> class BaseResult : private std::variant<Ok, Ko> {

public:
  explicit BaseResult(Ok const & okVal) noexcept
      : std::variant<Ok, Ko>::variant(okVal) {}
  explicit BaseResult(Ko const & koVal) noexcept
      : std::variant<Ok, Ko>::variant(koVal) {}

  bool isOk() { return std::holds_alternative<Ok>(*this); }

  template <class NewOk>
  BaseResult<NewOk, Ko>
  andThen(BaseResult<NewOk, Ko> const & other) const noexcept {
    if (auto const * const koVal = std::get_if<Ko>(*this)) {
      return makeResult(*koVal);
    }
    return other;
  }

  template <class NewOk, std::invocable<Ok const &, BaseResult<NewOk, Ko>> Fn>
  BaseResult<NewOk, Ko> andThen(Fn const & fn) const noexcept {
    if (auto const * const okVal = std::get_if<Ok>(*this)) {
      return fn(*okVal);
    }
    return makeResult(*std::get_if<Ko>(*this));
  }

  template <class NewKo>
  BaseResult<Ok, NewKo>
  orElse(BaseResult<Ok, NewKo> const & other) const noexcept {
    if (auto const * const okVal = std::get_if<Ok>(*this)) {
      return makeResult(*okVal);
    }
    return other;
  }

  template <class NewKo, std::invocable<Ko const &, BaseResult<Ok, NewKo>> Fn>
  BaseResult<Ok, NewKo> orElse(Fn const & fn) const noexcept {
    if (auto const * const koVal = std::get_if<Ko>(*this)) {
      return fn(*koVal);
    }
    return makeResult(*std::get_if<Ok>(*this));
  }

  template <class NewOk, std::invocable<Ok const &, NewOk> Fn>
  BaseResult<NewOk, Ko> mapOk(Fn const & fn) const noexcept {
    if (auto const * const okVal = std::get_if<Ok>(*this)) {
      return makeResult(fn(*okVal));
    }
    return makeResult(*std::get_if<Ko>(*this));
  }

  template <class NewKo, std::invocable<Ko const &, NewKo> Fn>
  BaseResult<Ok, NewKo> mapKo(Fn const & fn) const noexcept {
    if (auto const * const koVal = std::get_if<Ko>(*this)) {
      return makeResult(fn(*koVal));
    }
    return makeResult(*std::get_if<Ok>(*this));
  }

  Ok expectOk(std::exception const & e = std::bad_variant_access()) const {
    if (auto const * const okVal = std::get_if<Ok>(*this)) {
      return *okVal;
    }
    throw e;
  }

  Ok expectOk(Ok const & dfltVal) const noexcept {
    if (auto const * const okVal = std::get_if<Ok>(*this)) {
      return *okVal;
    }
    return dfltVal;
  }

  Ko expectKo(std::exception const & e = std::bad_variant_access()) const {
    if (auto const * const koVal = std::get_if<Ko>(*this)) {
      return *koVal;
    }
    throw e;
  }

  Ko expectKo(Ko const & dfltVal) const noexcept {
    if (auto const * const koVal = std::get_if<Ko>(*this)) {
      return *koVal;
    }
    return dfltVal;
  }

  template <std::invocable<Ok const &, void> Fn> BaseResult inspectOk(Fn fn) {
    if (auto const * const okVal = std::get_if<Ok>(*this)) {
      fn(*okVal);
    }
  }

  template <std::invocable<Ko const &, void> Fn> BaseResult inspectKo(Fn fn) {
    if (auto const * const koVal = std::get_if<Ko>(*this)) {
      fn(*koVal);
    }
  }

protected:
private:
};

template <class Ok, class Ko> class Result : public BaseResult<Ok, Ko> {};

template <class Ok, class Ko>
class Result<Result<Ok, Ko>, Ko> : public BaseResult<BaseResult<Ok, Ko>, Ko> {
public:
  Result<Ok, Ko> flatten() {
    if (auto const * const okVal = std::get_if<Result<Ok, Ko>>(*this)) {
      return *okVal;
    }
    return makeResult(std::get_if<Ko>(*this));
  }
};

template <class Ok, class Ko> Result<Ok, Ko> makeResult(Ok const & okVal) {
  return Result(okVal);
}

template <class Ok, class Ko> BaseResult<Ok, Ko> makeResult(Ko const & koVal) {
  return Result(koVal);
}

} // namespace utils

#endif // !UTILS_RESULT_HXX
