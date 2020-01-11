/*
 * A BEZIER CURVE EDITOR
 * Created by Yiming Hu
 */

#include <GL/gl.h>
#include <GL/glut.h>

//other includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

/* The number of pixels in the grid */
int grid_width;
int grid_height;

/* The size of pixels sets the inital window height and width */
float pixel_size;

void init();
void idle();
void display();
void draw_pix(double x, double y);
void draw_lines(double x1, double y1, double x2, double y2);
double xbeizer(std::vector<std::vector<double>> pt, double t);
double ybeizer(std::vector<std::vector<double>> pt, double t);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void skey(int ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();

/* Window information */
int win_height;
int win_width;
int mode;
int selected;
std::vector<std::vector<double>> points;

int main(int argc, char **argv)
{
    
    /* The number of pixels in the grid */
    grid_width = 100;
    grid_height = 100;
    
    /* The size of pixels sets the inital window height and width */
    pixel_size = 5;
    
    /* Window information */
    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;
    
    /* Set up glut functions */   
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    /* Initialize variables, allocate memory, create buffers, etc. */
    //create window of size (win_width x win_height
    glutInitWindowSize(win_width,win_height);
    glutCreateWindow("Bezier Curve Editor");
    
    /*defined glut callback functions*/
    glutDisplayFunc(display); //rendering calls here	
    glutReshapeFunc(reshape); //update GL on window size change
    glutMouseFunc(mouse);     //mouse button events
    glutMotionFunc(motion);   //mouse movement events
    glutKeyboardFunc(key);    //Keyboard events
    glutSpecialFunc(skey);    //Special keys: up arrow, down arrow, etc.    
    glutIdleFunc(idle);       //Function called while program is sitting "idle"

    /* Initialize opengl variables */
    init();

    /* start glut event loop */
    glutMainLoop();

    return 0;
}

/*initialize gl stufff*/
void init()
{
    /* Set clear color (Default background to white) */
    glClearColor(1.0,1.0,1.0,1.0);

    /* Checks for OpenGL errors */
    check();
}

//called repeatedly when glut isn't doing anything else
void idle()
{
    /* Redraw the scene over and over again */
    glutPostRedisplay();	
}

//this is where we render the screen
void display()
{
    //glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    /* Draw Points */
    if (points.size() != 0) {
      draw_pix(points[points.size()-1][0], points[points.size()-1][1]);
    }	

    /* Connect Lines */
    if (points.size() > 1) {
      draw_lines(points[points.size()-2][0], points[points.size()-2][1],points[points.size()-1][0], points[points.size()-1][1]);
    } 

    /* Clear the scene */
    if (mode == 4) {
      glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
      points.clear();
      mode = 0;
    }

    if (mode == 3) {
      glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      for (int x = 0; x < points.size(); x++) {
        draw_pix(points[x][0], points[x][1]);
        if (x != points.size()-1) {
          draw_lines(points[x][0], points[x][1],points[x+1][0], points[x+1][1]);
        }
      }
    }

    /* Beizer Curve */
    if (mode == 2) {
      glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      for (int x = 0; x < points.size(); x++) {
        draw_pix(points[x][0], points[x][1]);
        if (x != points.size()-1) {
          draw_lines(points[x][0], points[x][1],points[x+1][0], points[x+1][1]);
        }
      }
      double t = 0;
      while (t <= 1) {
        t += 0.001;
        draw_pix(xbeizer(points, t), ybeizer(points, t));
      }
    }

    glutSwapBuffers();
    check();
}

void draw_pix(double x, double y){
    glBegin(GL_POINTS);
      glColor3f(.2,.2,1.0);
      glVertex3f(x+.5,y+.5,0);
    glEnd();
}

void draw_lines(double x1, double y1, double x2, double y2) {

    glBegin(GL_LINES);
      glColor3f(.2,.2,1.0);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
    glEnd();

}

double xbeizer(std::vector<std::vector<double>> pt, double t) {
  double x;
  std::vector<std::vector<double>> temp;

  if (pt.size() == 1) {
    return pt[0][0];
  } else {
    for (int i = 0; i < pt.size()-1; i++) {
      std::vector<double> emp;

      x = (1 - t) * pt[i][0] + t * pt[i+1][0];
      emp.push_back(x);
      temp.push_back(emp);    
    }
    return xbeizer(temp, t);
  }  
}

double ybeizer(std::vector<std::vector<double>> pt, double t) {
  double y;
  std::vector<std::vector<double>> temp;

  if (pt.size() == 1) {
    return pt[0][1];
  } else {
    for (int i = 0; i < pt.size()-1; i++) {
      std::vector<double> emp;

      y = (1 - t) * pt[i][1] + t * pt[i+1][1];
      emp.push_back(0);
      emp.push_back(y);
      temp.push_back(emp);    
    }
    return ybeizer(temp, t);
  }  
}

void reshape(int width, int height)
{
     /*set up projection matrix to define the view port*/
    //update the ne window width and height
	win_width = width;
	win_height = height;
    
    //creates a rendering area across the window
    glViewport(0,0,width,height);

    // up an orthogonal projection matrix so that
    // the pixel space is mapped to the grid space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,grid_width,0,grid_height,-10,10);
    
    //clear the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //set pixel size based on width, if the aspect ratio
    //changes this hack won't work as well
    pixel_size = width/(float)grid_width;
    
    //set pixel size relative to the grid cell size
    glPointSize(pixel_size);
    //check for opengl errors
    check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
    switch(ch)
    {
      case 'q':
        exit(0);
        break;
      case 'd':
        points.pop_back();
        mode = 3;
        break;
      case 'b':
        mode = 2;
        break;
      case 'c':
        mode = 3;
        if (selected < points.size()) {
          selected++;
        } else {
          selected = 0;
        }
        break;
      case 'r':
        mode = 4;
        break;
      default:
        printf("Invalid Key\n");
        break;
    }

    glutPostRedisplay();
}

void skey(int ch, int x, int y) 
{
    if (ch == GLUT_KEY_UP) {
      mode = 3;
      points[selected][1]+=2;
    }
    if (ch == GLUT_KEY_DOWN) {
      mode = 3;
      points[selected][1]-=2;
    }
    if (ch == GLUT_KEY_LEFT) {
      mode = 3;
      points[selected][0]-=2;
    }
    if (ch == GLUT_KEY_RIGHT) {
      mode = 3;
      points[selected][0]+=2;
    }
}

//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{
    std::vector<double> point;
        
    if(state == GLUT_DOWN) { //button released
      /* Print the pixel location, and the grid location */     
      printf ("Added Point Dimension: %d %d\n", (int)(x/pixel_size),(int)((win_height-y)/pixel_size));

      point.push_back(x/pixel_size);
      point.push_back((win_height-y)/pixel_size);
      points.push_back(point);
    }
    
    //redraw the scene after mouse click
    glutPostRedisplay();
}

//gets called when the curser moves accross the scene
void motion(int x, int y)
{
    /* Redraw the scene after mouse movement */
    glutPostRedisplay();
}

//Checks for any opengl errors in the previous calls and
//outputs if they are present.
void check()
{
    GLenum err = glGetError();

    if(err != GL_NO_ERROR) {
      printf("GLERROR: There was an error %s\n",gluErrorString(err) );
      exit(1);
    }
}
