#include <algorithm>

#include "Rectangle.h"

namespace Figures {
    void swap(Rectangle &first, Rectangle &second, bool swapBase) {
        using std::swap;
        swap(first.x1, second.x1);
        swap(first.y1, second.y1);
        swap(first.x2, second.x2);
        swap(first.y2, second.y2);
        if (swapBase)
            swap(dynamic_cast<Shape&>(first), dynamic_cast<Shape&>(second));
    }

    Rectangle::Rectangle(const size_t& x1, const size_t& y1, const size_t& x2, const size_t& y2, const int& colour, const bool& selected) noexcept:
        Shape(colour, selected), x1{x1}, y1{y1}, x2{x2}, y2{y2} { }

    [[nodiscard]] vector<Pixel> Rectangle::GetPixels() const {
        vector<Pixel> result{};
        const auto &top_x = max(min(this->x1, this->x2), 0UL), &top_y = max(min(this->y1, this->y2), 0UL);
        const auto &bottom_x = max(this->x1, this->x2), &bottom_y = max(this->y1, this->y2);
        for (auto i = top_x; i <= bottom_x; ++i)
            for (auto j = top_y; j <= bottom_y; ++j)
                result.push_back({i, j, this->colour});

        return result;
    }

    [[nodiscard]] unique_ptr<Shape> Rectangle::Clone() const {
        return make_unique<Rectangle>(*this);
    }

    [[nodiscard]] size_t Rectangle::X1() const {
        return this->x1;
    }

    size_t Rectangle::X1(size_t value) {
        const auto prev_value = this->x1;
        if (prev_value != value) {
            this->x1 = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] size_t Rectangle::Y1() const {
        return this->y1;
    }

    size_t Rectangle::Y1(size_t value) {
        const auto prev_value = this->y1;
        if (prev_value != value) {
            this->y1 = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] size_t Rectangle::X2() const {
        return this->x2;
    }

    size_t Rectangle::X2(size_t value) {
        const auto prev_value = this->x2;
        if (prev_value != value) {
            this->x2 = value;
            this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] size_t Rectangle::Y2() const {
        return this->y2;
    }

    size_t Rectangle::Y2(size_t value) {
        const auto prev_value = this->y2;
        if (prev_value != value) {
            this->y2 = value;
            this->Notify();
        }

        return prev_value;
    }
}
