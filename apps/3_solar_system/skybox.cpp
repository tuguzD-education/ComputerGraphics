#include "skybox.hpp"

Skybox::Skybox(computer_graphics::Game& game, const Initializer& initializer)
    : SceneComponent(game, initializer),
      front_{Game().AddComponent<computer_graphics::BoxComponent>([this] {
          computer_graphics::BoxComponent::Initializer box_initializer{
              .length = 1.0f,
              .height = 1.0f,
              .width = 0.0f,
          };
          box_initializer.transform.position = computer_graphics::math::Vector3::Forward * 0.5f;
          box_initializer.parent = this;
          box_initializer.texture_path = "resources/textures/skybox/back.png";
          return box_initializer;
      }())},
      back_{Game().AddComponent<computer_graphics::BoxComponent>([this] {
          computer_graphics::BoxComponent::Initializer box_initializer{
              .length = 1.0f,
              .height = 1.0f,
              .width = 0.0f,
          };
          box_initializer.transform.position = computer_graphics::math::Vector3::Backward * 0.5f;
          box_initializer.parent = this;
          box_initializer.texture_path = "resources/textures/skybox/front.png";
          return box_initializer;
      }())},
      left_{Game().AddComponent<computer_graphics::BoxComponent>([this] {
          computer_graphics::BoxComponent::Initializer box_initializer{
              .length = 0.0f,
              .height = 1.0f,
              .width = 1.0f,
          };
          box_initializer.transform.position = computer_graphics::math::Vector3::Left * 0.5f;
          box_initializer.parent = this;
          box_initializer.texture_path = "resources/textures/skybox/left.png";
          return box_initializer;
      }())},
      right_{Game().AddComponent<computer_graphics::BoxComponent>([this] {
          computer_graphics::BoxComponent::Initializer box_initializer{
              .length = 0.0f,
              .height = 1.0f,
              .width = 1.0f,
          };
          box_initializer.transform.position = computer_graphics::math::Vector3::Right * 0.5f;
          box_initializer.parent = this;
          box_initializer.texture_path = "resources/textures/skybox/right.png";
          return box_initializer;
      }())},
      top_{Game().AddComponent<computer_graphics::BoxComponent>([this] {
          computer_graphics::BoxComponent::Initializer box_initializer{
              .length = 1.0f,
              .height = 0.0f,
              .width = 1.0f,
          };
          box_initializer.transform.position = computer_graphics::math::Vector3::Up * 0.5f;
          box_initializer.parent = this;
          box_initializer.texture_path = "resources/textures/skybox/top.png";
          return box_initializer;
      }())},
      bottom_{Game().AddComponent<computer_graphics::BoxComponent>([this] {
          computer_graphics::BoxComponent::Initializer box_initializer{
              .length = 1.0f,
              .height = 0.0f,
              .width = 1.0f,
          };
          box_initializer.transform.position = computer_graphics::math::Vector3::Down * 0.5f;
          box_initializer.parent = this;
          box_initializer.texture_path = "resources/textures/skybox/bot.png";
          return box_initializer;
      }())} {
    Transform().scale *= 100.0f;
}
