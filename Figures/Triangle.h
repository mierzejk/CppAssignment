#pragma once
#ifndef ASSIGNMENT_TRIANGLE_H
#define ASSIGNMENT_TRIANGLE_H

#include "../drawing.h"

using namespace drawing;

namespace Figures {

    class Triangle: public Shape {
    protected:
        size_t x, y;
        int height;

        friend void swap(Triangle& first, Triangle& second, bool swapBase);

    public:
        Triangle(const size_t& x, const size_t& y, const int& height, const int& colour, const bool& selected = true) noexcept;
        Triangle(const Triangle& other) noexcept = default;
        inline Triangle(Triangle&& other) noexcept: Shape(move(other)), x{}, y{}, height{} {
            swap(*this, other, false);
        }
        inline Triangle& operator=(Triangle other) {
            swap(*this, other, true);
            return *this;
        }

        [[nodiscard]] vector<Pixel> GetPixels() const override;
        [[nodiscard]] unique_ptr<Shape> Clone() const override;

        [[nodiscard]] size_t X() const;
        size_t X(size_t value);
        [[nodiscard]] size_t Y() const;
        size_t Y(size_t value);
        [[nodiscard]] int Height() const;
        int Height(int value);
    };

}

#endif //ASSIGNMENT_TRIANGLE_H
