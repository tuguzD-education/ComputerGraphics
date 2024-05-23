#include "computer_graphics/math.hpp"

namespace computer_graphics::math {

void Normalize(const Vector3 &vector, Vector3 &result) {
    vector.Normalize(result);
}

Vector3 Normalize(const Vector3 &vector) {
    Vector3 result;
    Normalize(vector, result);
    return result;
}

void RotateAround(
    const Vector3 &position, const Vector3 &rotation_point, const Quaternion &rotate_by, Vector3 &result) {
    result = Vector3::Transform(position - rotation_point, rotate_by) + rotation_point;
}

Vector3 RotateAround(const Vector3 &position, const Vector3 &rotation_point, const Quaternion &rotate_by) {
    Vector3 result;
    RotateAround(position, rotation_point, rotate_by, result);
    return result;
}

}  // namespace computer_graphics::math
