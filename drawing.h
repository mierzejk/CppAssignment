#pragma once
#ifndef ASSIGNMENT_DRAWING_H
#define ASSIGNMENT_DRAWING_H

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <vector>

using namespace std;

namespace drawing {

    struct Pixel {
        size_t X, Y;
        int Colour;
    };

    class Shape;

    class Observer {
    public:
        virtual ~Observer() = default;
        /**
         * Notifies the observer of a shape change.
         * @param shape The shape instance that has been changed.
         * @param refresh True if the change is supposed to produce immediate effect; false otherwise.
         */
        virtual void Update(Shape& shape, bool refresh) = 0;
        /**
         * Notifies deleted shape to the observer.
         * @param shape The shape instance that has been deleted.
         * @param refresh True if the shape removal is supposed to produce immediate effect; false otherwise.
         */
        virtual void Delete(Shape& shape, bool refresh) = 0;
    };

    class Shape {
        vector<Observer*> observers;

    protected:
        int colour;
        bool selected;

        friend void swap(Shape& first, Shape& second);
        explicit Shape(const int& colour, const bool& selected = true) noexcept;
        Shape() noexcept: colour{}, selected{} { };
        Shape(const Shape& other) noexcept;
        inline Shape(Shape&& other) noexcept: Shape() {
            swap(*this, other);
        }

        void Notify();

    public:
        virtual ~Shape() noexcept;

        [[nodiscard]] virtual unique_ptr<Shape> Clone() const = 0;
        [[nodiscard]] virtual vector<Pixel> GetPixels() const = 0;

        void Attach(Observer& observer);
        uint Detach(const Observer& observer, bool all = false);

        [[nodiscard]] bool Selected() const;
        bool Selected(bool value);
        [[nodiscard]] int Colour() const;
        int Colour(int value);
    };

    class Canvas final : public Observer {
        bool paused;
        mutex mtx;

        int* canvas;
        size_t height, width, length;
        unique_ptr<int[]> buffer;
        map<Shape* const, unique_ptr<Shape>> shapes;

        friend void swap(Canvas& first, Canvas& second);
        Canvas() noexcept: paused{}, canvas{nullptr}, height{}, width{}, length{} { };

    public:
        Canvas(int* array, const size_t& width, const size_t& height, const set<Shape*>& shapes = {}, const bool& paused = false) noexcept(false);
        inline Canvas(Canvas&& other) noexcept: Canvas() {
            swap(*this, other);
        }
        inline Canvas& operator=(Canvas other) {
            swap(*this, other);
            return *this;
        }
        ~Canvas() noexcept override;

        /**
         * If not in batch update mode, refreshes the underlying 2D array with the canvas' contents.
         * @param force True to ignore batch update mode and force refresh; false otherwise.
         */
        void Refresh(const bool& force = false);

        void Update(Shape& shape, bool refresh) override;
        void Delete(Shape& shape, bool refresh) override;

        /**
         * Enter the batch update mode.
         */
        void Pause();
        /**
         * Complete and quit the batch update mode.
         */
        void Resume();
    };

}

#endif //ASSIGNMENT_DRAWING_H
