#pragma once

#ifndef MESH_COMPONENT_HPP_INCLUDED
#define MESH_COMPONENT_HPP_INCLUDED

#include "triangle_component.hpp"

namespace computer_graphics {

template <std::derived_from<TriangleComponent> ChildMesh = TriangleComponent>
class MeshComponent : public SceneComponent {
  public:
    using Vertex = typename ChildMesh::Vertex;
    using Index = typename ChildMesh::Index;

    struct Initializer : SceneComponent::Initializer {
        std::filesystem::path mesh_path;

        Initializer &MeshPath(const std::filesystem::path &mesh_path);
    };

    explicit MeshComponent(class Game &game, const Initializer &initializer);

    void LoadMesh(const std::filesystem::path &mesh_path);
};

}  // namespace computer_graphics

#include "mesh_component.inl"

#endif  // MESH_COMPONENT_HPP_INCLUDED
