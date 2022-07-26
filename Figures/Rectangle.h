#pragma once
#ifndef ASSIGNMENT_RECTANGLE_H
#define ASSIGNMENT_RECTANGLE_H

#include "../drawing.h"

using namespace drawing;

namespace Figures {

    class Rectangle : public Shape {
    protected:
        size_t x1, y1, x2, y2;

        friend void swap(Rectangle& first, Rectangle& second, bool swapBase);

    public:
        Rectangle(const size_t& x1, const size_t& y1, const size_t& x2, const size_t& y2, const int& colour, const bool& selected = true) noexcept;
        Rectangle(const Rectangle& other) noexcept = default;
        inline Rectangle(Rectangle&& other) noexcept: Shape(move(other)), x1{}, y1{}, x2{}, y2{} {
            swap(*this, other, false);
        }
        inline Rectangle& operator=(Rectangle other) {
            swap(*this, other, true);
            return *this;
        }

        [[nodiscard]] vector<Pixel> GetPixels() const override;
        [[nodiscard]] unique_ptr<Shape> Clone() const override;

        [[nodiscard]] size_t X1() const;
        size_t X1(size_t value);
        [[nodiscard]] size_t Y1() const;
        size_t Y1(size_t value);
        [[nodiscard]] size_t X2() const;
        size_t X2(size_t value);
        [[nodiscard]] size_t Y2() const;
        size_t Y2(size_t value);
    };

}

#endif //ASSIGNMENT_RECTANGLE_H
