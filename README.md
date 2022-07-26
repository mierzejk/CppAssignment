# Problem statement
You need to build an application that gives users a capability to draw shapes on a canvas and edit them.
>Create an API (a set of classes and methods) to allow a UI developer to implement the UI for the application described below (you are not in charge of the UI).
1. `Add` / `remove` shapes to / from canvas:
    - Rectangle
    - Circle
    - Triangle
2. Shape attributes:
    - Size
    - Color
    - Position
3. Each shape on canvas maybe `selected` or `unselected`:
    - Changing attribute(s) on the selected shape should have an immediate effect on the canvas.
    - The API can also batch requests for change before applying them to the canvas.

>Please notice that shapes can’t overlap.

Data structures:  
Your API and the UI share a 2D array of type int, which represents the drawing canvas (you are responsible to fill it and update it correctly).
