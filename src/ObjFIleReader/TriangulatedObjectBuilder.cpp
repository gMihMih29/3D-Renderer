#include "TriangulatedObjectBuilder.h"

#include "../Utilities/Logger.h"

namespace ThreeDRenderer {
void TriangulatedObjectBuilder::AddVertex(Vector3&& vertex) {
    vertexes_.emplace_back(vertex);
}

void TriangulatedObjectBuilder::AddNormal(Vector3&& normal) {
    normals_.emplace_back(normal);
}

void TriangulatedObjectBuilder::AddFaceElement(FaceElement&& face) {
    faces_.emplace_back(face);
}

TriangulatedObjectBuilder::Response TriangulatedObjectBuilder::Build() const {
    std::vector<Triangle> surfaces_;
    for (int i = 0; i < faces_.size(); ++i) {
        Vector3 normal(0, 0, 0);
        if (faces_[i].normals.empty()) {
            normal = FindNormalForFaceElemBruteForce_(i);
        } else {
            for (int j = 0; j < faces_[i].normals.size(); ++j) {
                normal += normals_[faces_[i].normals[j]];
            }
            normal.normalize();
        }
        for (int j = 1; j < faces_[i].points.size() - 1; ++j) {
            surfaces_.emplace_back(vertexes_[faces_[i].points[0]], vertexes_[faces_[i].points[j]],
                                   vertexes_[faces_[i].points[j + 1]], normal);
        }
    }
    return Response::Success(TriangulatedObject(std::move(surfaces_)));
}

int TriangulatedObjectBuilder::GetVertexesQuatity() const {
    return vertexes_.size();
}

int TriangulatedObjectBuilder::GetNormalsQuatity() const {
    return normals_.size();
}

TriangulatedObjectBuilder::Vector3 TriangulatedObjectBuilder::FindNormalForFaceElemBruteForce_(
    int index_of_face_elem) const {
    Vector3 normal(0, 0, 0);
    for (int i = 0; i < faces_[index_of_face_elem].points.size(); ++i) {
        int cur_point = faces_[index_of_face_elem].points[i];
        normal += FindNormalForPoint_(cur_point);
    }
    normal.normalize();
    return normal;
}

TriangulatedObjectBuilder::Vector3 TriangulatedObjectBuilder::FindNormalForPoint_(int point_index) const {
    Vector3 normal(0, 0, 0);
    std::vector<bool> vertex_is_used(GetVertexesQuatity());
    for (int i = 0; i < faces_.size(); ++i) {
        for (int j = 0; j < faces_[i].points.size(); ++j) {
            int prev = (j - 1) % faces_[i].points.size();
            if (prev < 0) {
                prev += faces_[i].points.size();
            }
            int prev_point = faces_[i].points[prev];
            int cur_point = faces_[i].points[j];
            if (prev_point == point_index && !vertex_is_used[cur_point]) {
                normal += vertexes_[cur_point] - vertexes_[point_index];
                vertex_is_used[cur_point] = true;
            }
        }
    }
    for (int i = 0; i < faces_.size(); ++i) {
        for (int j = 0; j < faces_[i].points.size(); ++j) {
            int next = (j + 1) % faces_[i].points.size();
            int next_point = faces_[i].points[next];
            int cur_point = faces_[i].points[j];
            if (next_point == point_index && !vertex_is_used[cur_point]) {
                normal += vertexes_[cur_point] - vertexes_[point_index];
                vertex_is_used[cur_point] = true;
            }
        }
    }
    normal = -normal;
    normal.normalize();
    return normal;
}

}  // namespace ThreeDRenderer
