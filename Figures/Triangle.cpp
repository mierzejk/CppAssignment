#include <algorithm>

#include "Triangle.h"

namespace Figures {

    void swap(Triangle &first, Triangle &second, bool swapBase) {
        using std::swap;
        swap(first.x, second.x);
        swap(first.y, second.y);
        swap(first.height, second.height);
        if (swapBase)
            swap(dynamic_cast<Shape&>(first), dynamic_cast<Shape&>(second));
    }

    Triangle::Triangle(const size_t& x, const size_t& y, const int& height, const int& colour, const bool& selected) noexcept:
        Shape(colour, selected), x{x}, y{y}, height{height} { }

    [[nodiscard]] vector<Pixel> Triangle::GetPixels() const {
        vector<Pixel> result{};
        const auto&& step = this->height > 0 ? 1 : -1;
        const auto &&X = static_cast<int>(this->x), &&Y = static_cast<int>(this->y) - this->height + step;
        for (auto j = max(0, -Y); j != this->height; j += step) {
            const auto &&point_y = Y + j;
            for (auto i = j > X ? -X : -j; i != j + step; i += step)
                result.push_back({static_cast<size_t>(X + i), static_cast<size_t>(point_y), this->colour});
        }

        return result;
    }

    [[nodiscard]] unique_ptr<Shape> Triangle::Clone() const {
        return make_unique<Triangle>(*this);
    }

    [[nodiscard]] size_t Triangle::X() const {
        return this->x;
    }

    size_t Triangle::X(size_t value) {
        const auto prev_value = this->x;
        if (prev_value != value) {
            this->x = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] size_t Triangle::Y() const {
        return this->y;
    }

    size_t Triangle::Y(size_t value) {
        const auto prev_value = this->y;
        if (prev_value != value) {
            this->y = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] int Triangle::Height() const {
        return this->height;
    }

    int Triangle::Height(int value) {
        const auto prev_value = this->height;
        if (prev_value != value) {
            this->height = value;
            this->Notify();
        }

        return prev_value;
    }
}
