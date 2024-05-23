#pragma once

#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include <d3d11.h>

#include <functional>
#include <string>

namespace computer_graphics {

class Game;
class Camera;

class Component {
  public:
    struct Initializer {
        std::string name = "component";
    };

    explicit Component(Game &game, const Initializer &initializer = {});
    virtual ~Component();

    [[nodiscard]] std::string &Name();
    [[nodiscard]] const std::string &Name() const;

    virtual void Update(float delta_time);
    virtual void Draw(const Camera *camera);
    virtual void OnTargetResize();

  protected:
    [[nodiscard]] const Game &Game() const;
    [[nodiscard]] class Game &Game();

    [[nodiscard]] ID3D11DeviceContext &DeviceContext();
    [[nodiscard]] const ID3D11DeviceContext &DeviceContext() const;

    [[nodiscard]] ID3D11Device &Device();
    [[nodiscard]] const ID3D11Device &Device() const;

  private:
    std::reference_wrapper<class Game> game_;

    std::string name_;
};

}  // namespace computer_graphics

#endif  // COMPONENT_HPP_INCLUDED
