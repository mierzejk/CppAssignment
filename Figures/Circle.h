#pragma once
#ifndef ASSIGNMENT_CIRCLE_H
#define ASSIGNMENT_CIRCLE_H

#include "../drawing.h"

using namespace drawing;

namespace Figures {

    class Circle: public Shape {
    protected:
        size_t x, y;
        float radius, r_squared;

        friend void swap(Circle& first, Circle& second, bool swapBase);

    public:
        Circle(const size_t& x, const size_t& y, const float& radius, const int& colour, const bool& selected = true) noexcept;
        Circle(const Circle& other) noexcept = default;
        inline Circle(Circle&& other) noexcept: Shape(move(other)), x{}, y{}, radius{}, r_squared{} {
            swap(*this, other, false);
        }
        inline Circle& operator=(Circle other) {
            swap(*this, other, true);
            return *this;
        }

        [[nodiscard]] vector<Pixel> GetPixels() const override;
        [[nodiscard]] unique_ptr<Shape> Clone() const override;

        [[nodiscard]] size_t X() const;
        size_t X(size_t value);
        [[nodiscard]] size_t Y() const;
        size_t Y(size_t value);
        [[nodiscard]] float Radius() const;
        float Radius(float value);
    };

}

#endif //ASSIGNMENT_CIRCLE_H
