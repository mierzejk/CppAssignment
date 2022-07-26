#include <algorithm>
#include <cmath>

#include "Circle.h"

namespace Figures {

    void swap(Circle &first, Circle &second, bool swapBase) {
        using std::swap;
        swap(first.x, second.x);
        swap(first.y, second.y);
        swap(first.radius, second.radius);
        swap(first.r_squared, second.r_squared);
        if (swapBase)
            swap(dynamic_cast<Shape&>(first), dynamic_cast<Shape&>(second));
    }

    Circle::Circle(const size_t& x, const size_t& y, const float& radius, const int& colour, const bool& selected) noexcept:
        Shape(colour, selected), x{x}, y{y}, radius{fabs(radius)}, r_squared{powf(radius, 2)} { }

    [[nodiscard]] vector<Pixel> Circle::GetPixels() const {
        vector<Pixel> result{};
        const auto &&X = static_cast<float>(this->x), &&Y = static_cast<float>(this->y);
        for (float i = max(0.f, ceil(X - this->radius)); i <= floor(X + this->radius);) {
            for (float j = max(0.f, ceil(Y - this->radius)); j <= floor(Y + this->radius);) {
                if (pow(i - X, 2) + pow(j - Y, 2) <= this->r_squared)
                    result.push_back({static_cast<size_t>(i), static_cast<size_t>(j), this->colour});

                j++;
            }
            i++;
        }

        return result;
    }

    [[nodiscard]] unique_ptr<Shape> Circle::Clone() const {
        return make_unique<Circle>(*this);
    }

    [[nodiscard]] size_t Circle::X() const {
        return this->x;
    }

    size_t Circle::X(size_t value) {
        const auto prev_value = this->x;
        if (prev_value != value) {
            this->x = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] size_t Circle::Y() const {
        return this->y;
    }

    size_t Circle::Y(size_t value) {
        const auto prev_value = this->y;
        if (prev_value != value) {
            this->y = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] float Circle::Radius() const {
        return this->radius;
    }

    float Circle::Radius(float value) {
        const auto prev_value = this->radius;
        if (prev_value != value) {
            this->radius = value;
            this->r_squared = powf(radius, 2);
            this->Notify();
        }

        return prev_value;
    }
}
