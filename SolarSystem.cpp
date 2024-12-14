#include <GL/glut.h>

GLfloat angle = 0.0, angle1 = 0.0, angle2 = 0.0; // Rotational angles for torus
GLfloat planetAngles[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // Angles for planets

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the Sun
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glutSolidSphere(1.0, 20, 20);

    // Planets
    GLfloat planetDistances[] = { 2.0, 3.5, 5.0, 7.0, 9.5, 12.0, 14.5, 17.0 }; // Distance from Sun
    GLfloat planetSizes[] = { 0.2, 0.4, 0.5, 0.6, 0.7, 0.6, 0.5, 0.4 }; // Sizes of planets
    GLfloat planetSpeeds[] = { 0.1, 0.08, 0.07, 0.05, 0.03, 0.02, 0.015, 0.01 }; // Speed of rotation
    GLfloat planetColors[][3] = {
    {0.6, 0.4, 0.2},  // Mercury - Brown
    {0.8, 0.6, 0.4},  // Venus - Beige
    {0.0, 0.0, 1.0},  // Earth - Blue
    {1.0, 0.0, 0.0},  // Mars - Red
    {1.0, 0.5, 0.0},  // Jupiter - Orange
    {0.8, 0.8, 0.6},  // Saturn - Yellow
    {0.2, 0.5, 1.0},  // Uranus - Light Blue
    {0.5, 0.5, 0.9}   // Neptune - Purple

    };

    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();
        glRotatef(planetAngles[i], 0.0, 0.0, 1.0); // Rotate planet on Z
        glTranslatef(planetDistances[i], 0.0, 0.0); // Move to orbit distance
        glColor3fv(planetColors[i]); // Set planet color
        glutSolidSphere(planetSizes[i], 20, 20); // Draw planet
        glPopMatrix();
    }

    // Central rotating torus
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0); // White
    glRotatef(angle, 0.0, 0.0, 1.0); //rotate to z
    glutWireTorus(0.3, 1.2, 20, 20);

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void test()
{
    angle += 0.005; // Slow rotation for the torus

    // Update planet angles for rotation
    GLfloat planetSpeeds[] = { 0.1, 0.08, 0.07, 0.05, 0.03, 0.02, 0.015, 0.01 };
    for (int i = 0; i < 8; i++)
    {
        planetAngles[i] += planetSpeeds[i];
        if (planetAngles[i] >= 360.0) planetAngles[i] -= 360.0;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Solar System");
    glutIdleFunc(test);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}