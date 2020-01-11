# A-Bezier-Curve-Editor
**Before Drawing**
  After 'make', using './proj4' command to start.

**Basic Operations**
  1. Add Points
    Clicking on the window and you will see a point where the position your mouse click.
  2. Draw Beizer Curve
    (1)Press 'b' on your keyboard to draw a Beizer curve after adding points.
    (2)You can still add points after drawing the curve.
  3. Draw B-spline Curve
    (1)Press 's' on your keyboard to draw a B-spline curve after adding points.
      *You can switch to the B-spline curve directly by pressing 's' after drawing Beizer curve.
    (2)You can still add points after drawing the curve.
    (3)Several bars (numbers of bars depending on you number of points) will occur after you pressing 's'. 
       These bars represent knots. 
       You can use '+'(to RIGHT/increase) or '-'(to LEFT/decrease) to move knots. 
       Click 'm' on your keyboard to change bars.
    (4)Click '2' will draw the curve in de Boor order 2;
       Click '3' will draw the curve in de Boor order 3;
       Click '4' will draw the curve in de Boor order 4.
       Default order will be 3.
  4. Move Points
    (1)You can use ↑↓→← (up, down, left, right) buttons on your keyboard to move the points.  
       Click 'c' to change the points you want to move, and the order is the order you added points.
       Default point will be the first point you added.
    (2)After moving points, you have to redraw the curves.
  5. Delete Points
    (1)  Click 'd' to delete the point you added most recently.
    (2) After delete the point, you have to redraw the curve by pressing 'b' or 's'.
  6. Reset
    Clicking 'r' on your keyboard to reset the scene;
  7. Exit
    Clicking 'q' on your keyboard to quit the editor/program.
