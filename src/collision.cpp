#include "computer_graphics/collision.hpp"

namespace computer_graphics {

Collision::~Collision() = default;

BoxCollision::BoxCollision(const PrimitiveType& primitive) : box_{primitive} {
    math::Quaternion orientation{box_.Orientation};
    orientation.Normalize();
    box_.Orientation = orientation;
}

auto BoxCollision::Primitive() const -> const PrimitiveType& {
    return box_;
}

auto BoxCollision::Primitive() -> PrimitiveType& {
    return box_;
}

bool BoxCollision::Intersects(const Collision& other) const {
    if (const auto box = dynamic_cast<const BoxCollision*>(&other)) {
        return box->Primitive().Intersects(box_);
    }
    return other.Intersects(*this);
}

bool BoxCollision::Intersects(const math::Ray& ray, float& dist) const {
    return box_.Intersects(ray.position, ray.direction, dist);
}

}  // namespace computer_graphics
