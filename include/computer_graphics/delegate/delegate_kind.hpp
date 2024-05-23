#pragma once

#ifndef DELEGATE_KIND_HPP_INCLUDED
#define DELEGATE_KIND_HPP_INCLUDED

namespace computer_graphics::delegate {

class DelegateKindBase {
  public:
    DelegateKindBase();
    virtual ~DelegateKindBase() noexcept;

    [[nodiscard]] virtual const void *Owner() const;
};

template <typename R, typename... Args>
class DelegateKind : public DelegateKindBase {
  public:
    [[nodiscard]] virtual R Execute(Args &&...args) = 0;
};

}  // namespace computer_graphics::delegate

#endif  // DELEGATE_KIND_HPP_INCLUDED
