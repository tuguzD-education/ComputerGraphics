#pragma once

#ifndef VIEWPORT_MANAGER_HPP_INCLUDED
#define VIEWPORT_MANAGER_HPP_INCLUDED

#include <span>

#include "component.hpp"
#include "viewport.hpp"

namespace computer_graphics {

class ViewportManager : public Component {
  public:
    struct Initializer : Component::Initializer {};

    explicit ViewportManager(class Game &game, const Initializer &initializer = {});

    [[nodiscard]] const Viewport &TargetViewport() const;

    [[nodiscard]] std::span<const Viewport> Viewports() const;

    void Update(float delta_time) override;
    void OnTargetResize() override;

  protected:
    virtual void SplitViewports(std::vector<Viewport> &into);

  private:
    Viewport target_viewport_;
    std::vector<Viewport> split_viewports_;
};

}  // namespace computer_graphics

#endif  // VIEWPORT_MANAGER_HPP_INCLUDED
