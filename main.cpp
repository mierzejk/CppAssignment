#include <iostream>

#include "drawing.h"
#include "Figures/Figures.h"

using namespace drawing;

#define WIDTH 40
#define HEIGHT 10

void print(const int* const matrix, size_t width, size_t height) {
    for(size_t i=0; i<height*width; i+=width)
    {
        for(size_t j=0; j<width; j++)
        {
            const auto& pixel = matrix[i+j];
            if (pixel)
                cout << pixel;
            else
                cout << "·";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int a[HEIGHT][WIDTH];
    const auto&& show = [&a](){ print(a[0], WIDTH, HEIGHT); };

    Figures::Triangle triangle{4, 0, -4, 3, false};
    auto circle = make_unique<Figures::Circle>(9, 5, 3, 8, false);
    Figures::Rectangle rectangle{13, 4, 18, 0, 4};

    cout <<  "Initial view." << endl;
    Canvas canvas(a[0], WIDTH, HEIGHT, {&triangle, circle.get()});
    show();

    cout <<  "Batch update - canvas unchanged." << endl;
    canvas.Pause();
    canvas.Update(rectangle, true);
    circle->Radius(4);
    show();

    cout <<  "Batch update - all pending changes applied." << endl;
    canvas.Resume();
    show();

    cout <<  "Triangle and circle are not selected - canvas unchanged unless refreshed." << endl;
    triangle.X(triangle.X() + 1); triangle.Y(triangle.Y() + 1);
    show();

    cout <<  "Keep `circle` for a \"std::invalid_argument: Figures cannot overlap.\" exception." << endl;
    circle = nullptr;
    canvas.Refresh();
    cout <<  "Triangle and circle are not selected - canvas has been refreshed." << endl;
    show();

    cout <<  "Rectangle is selected - canvas refreshed instantaneously." << endl;
    rectangle.X1(10); rectangle.Y1(6);
    show();

    return 0;
}
