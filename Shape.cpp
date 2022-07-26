#include <algorithm>

#include "drawing.h"

namespace drawing {

    void swap(Shape &first, Shape &second) {
        using std::swap;
        swap(first.colour, second.colour);
        swap(first.selected, second.selected);
        swap(first.observers, second.observers);
        for_each(first.observers.cbegin(), first.observers.cend(), [&](const auto& observer) {
            observer->Delete(second, false);
            observer->Update(first, false);
        });
        for_each(second.observers.cbegin(), second.observers.cend(), [&](const auto& observer) {
            observer->Delete(first, false);
            observer->Update(second, false);
        });
    }

    Shape::Shape(const int &colour, const bool &selected) noexcept:
        colour{colour}, selected{selected} { }

    Shape::Shape(const Shape& other) noexcept:
        colour{other.colour}, selected{other.selected} { }

    Shape::~Shape() noexcept {
        for_each(this->observers.cbegin(), this->observers.cend(), [&](const auto& observer) {
            observer->Delete(*this, this->selected);
        });
    }

    void Shape::Attach(Observer& observer) {
        this->observers.push_back(&observer);
    }

    uint Shape::Detach(const Observer& observer, bool all) {
        uint erased{};
        auto iterator = this->observers.begin();
        while (iterator != this->observers.end() && (all or not erased)) {
            if (*iterator == &observer) {
                iterator = this->observers.erase(iterator);
                erased++;
            }
            else
                ++iterator;
        }

        return erased;
    }

    [[nodiscard]] bool Shape::Selected() const {
        return this->selected;
    }

    bool Shape::Selected(bool value) {
        const auto prev_value = this->selected;
        if (prev_value != value) {
            this->selected = value;
            if (value)
                this->Notify();
        }

        return prev_value;
    }

    [[nodiscard]] int Shape::Colour() const {
        return this->colour;
    }

    int Shape::Colour(int value) {
        const auto prev_value = this->colour;
        if (prev_value != value) {
            this->colour = value;
            this->Notify();
        }

        return prev_value;
    }

    void Shape::Notify() {
        for_each(this->observers.cbegin(), this->observers.cend(), [&](const auto& observer) {
            observer->Update(*this, this->selected);
        });
    }
}