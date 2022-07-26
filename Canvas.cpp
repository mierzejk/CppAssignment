#include <algorithm>
#include <set>

#include "drawing.h"

namespace drawing {

    void swap(Canvas &first, Canvas &second) {
        using std::swap;
        swap(first.paused, second.paused);
        swap(first.canvas, second.canvas);
        swap(first.height, second.height);
        swap(first.width, second.width);
        swap(first.length, second.length);
        swap(first.buffer, second.buffer);
        swap(first.shapes, second.shapes);
        for_each(first.shapes.cbegin(), first.shapes.cend(), [&](const auto& pair) {
            const auto& [shape, _] = pair;
            shape->Detach(second, true);
            shape->Attach(first);
        });
        for_each(second.shapes.cbegin(), second.shapes.cend(), [&](const auto& pair) {
            const auto& [shape, _] = pair;
            shape->Detach(first, true);
            shape->Attach(second);
        });
    }

    Canvas::Canvas(int* const array, const size_t& width, const size_t& height, const set<Shape*>& shapes, const bool& paused) noexcept(false):
                   paused{paused}, canvas{array}, height{height}, width{width}, length{height*width}, buffer{make_unique<int[]>(length)} {
        if (nullptr == array)
            throw std::invalid_argument("The canvas array cannot be null.");

        for_each(shapes.cbegin(), shapes.cend(), [&](const auto& shape) {
            if (nullptr == shape)
                return;

            this->Update(*shape, false);
        });
        this->Refresh(false);
    }

    Canvas::~Canvas() noexcept {
        for_each(this->shapes.cbegin(), this->shapes.cend(), [&](const auto &pair) {
            pair.first->Detach(*this, true);
        });
    }

    void Canvas::Refresh(const bool& force) {
        if (this->paused and not force)
            return;

        auto* const array = this->buffer.get();
        fill(array, array + this->length, 0);

        set<size_t> pixels{};
        this->mtx.lock();
        for (const auto& [_, shape]: this->shapes) {
            const auto&& points = shape->GetPixels();
            for_each(points.cbegin(), points.cend(), [&](const auto& point) {
                const auto& [x, y, colour] = point;

                if (0 == colour or x >= this->width or y >= this->height) // Ignoring transparent and outside bounds pixels.
                    return;

                const auto&& address = y * this->width + x;
                const auto&& [_, inserted] = pixels.insert(address);
                if (!inserted)
                    throw std::invalid_argument("Figures cannot overlap.");

                array[address] = colour;
            });
        }

        copy_n(array, this->length, this->canvas);
        this->mtx.unlock();
    }

    void Canvas::Update(Shape& shape, bool refresh) {
        this->mtx.lock();

        const auto&&[_, inserted] = this->shapes.insert_or_assign(&shape, shape.Clone());
        if (inserted)
            shape.Attach(*this);

        this->mtx.unlock();

        if (refresh)
            this->Refresh(false);
    }

    void Canvas::Delete(Shape& shape, bool refresh) {
        this->mtx.lock();

        shape.Detach(*this, true);
        const auto&& erased = this->shapes.erase(&shape) && refresh;

        this->mtx.unlock();

        if (erased)
            this->Refresh(false);
    }

    void Canvas::Pause() {
        this->paused = true;
    }

    void Canvas::Resume() {
        if (this->paused) {
            this->paused = false;
            this->Refresh(false);
        }
    }

}