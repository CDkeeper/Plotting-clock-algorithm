#include<GL/glut.h>
#include <math.h>
void setPixel(int x, int y) {
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void MidpointLine(int x0, int y0, int xe, int ye) {
    int a, b, d1, d2, d, x, y;
    float m;
    if (xe < x0) {
        d = x0, x0 = xe, xe = d;
        d = y0, y0 = ye, ye = d;
    }
    a = y0 - ye, b = xe - x0;
    if (b == 0) m = -1 * a * 100;
    else m = (float)a / (x0 - xe);
    x = x0, y = y0;
    setPixel(round(x), round(y));
    if (m >= 0 && m <= 1) {
        d = 2 * a + b;
        d1 = 2 * a, d2 = 2 * (a + b);
        while (x < xe) {
            if (d <= 0) {
                x++, y++, d += d2;
            }
            else {
                x++, d += d1;
            }
            setPixel(round(x), round(y));
        }
    }
    else if (m <= 0 && m >= -1) {
        d = 2 * a - b;
        d1 = 2 * a - 2 * b, d2 = 2 * a;
        while (x < xe) {
            if (d > 0) {
                x++, y--, d += d1;
            }
            else {
                x++, d += d2;
            }
            setPixel(round(x), round(y));
        }
    }
    else if (m > 1) {
        d = a + 2 * b;
        d1 = 2 * (a + b), d2 = 2 * b;
        while (y < ye) {
            if (d > 0) {
                x++, y++, d += d1;
            }
            else {
                y++, d += d2;
            }
            setPixel(round(x), round(y));
        }
    }
    else {
        d = a - 2 * b;
        d1 = -2 * b, d2 = 2 * (a - b);
        while (y > ye) {
            if (d <= 0) {
                x++, y--, d += d2;
            }
            else {
                y--, d += d1;
            }
            setPixel(round(x), round(y));
        }
    }
}

void init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ô²¿òÊ±ÖÓ");

    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}
void Bresenham_Circle(int xc, int yc, int r)
{
    int x, y, d;
    x = 0;
    y = r;
    d = 3 - 2 * r;
    glVertex2i(x + xc, y + yc);
    while (x < y)
    {
        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
        glVertex2i(x + xc, y + yc);
        glVertex2i(y + xc, x + yc);
        glVertex2i(y + xc, -x + yc);
        glVertex2i(x + xc, -y + yc);
        glVertex2i(-x + xc, -y + yc);
        glVertex2i(-y + xc, -x + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(-y + xc, x + yc);
    }
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2);
    glBegin(GL_POINTS);
    Bresenham_Circle(250, 250, 100);
    MidpointLine(250, 250, 200, 300);
    MidpointLine(250, 250, 300, 290);
    MidpointLine(250, 250, 260, 210);
    glEnd();
    glFlush();
}
int main(int argc, char** argv)
{
    init(argc, argv);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}

