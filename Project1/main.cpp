#include <GL/glut.h>

float angle = 0.0f;
float cameraX = -.0f, cameraY = 0.0f, cameraZ = -5.0f;
float sphereX = 2.5f, sphereZ = 0.0f;  // Sesuaikan nilai agar bola tidak terlalu jauh

void init() {
    glEnable(GL_DEPTH_TEST);
}

// Fungsi untuk menggambar sebuah kubus berwarna
void drawCube() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);  // Merah
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);

    glColor3f(0.0, 1.0, 0.0);  // Hijau
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);

    glColor3f(0.0, 0.0, 1.0);  // Biru
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    glColor3f(1.0, 1.0, 0.0);  // Kuning
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
}

// Fungsi untuk menggambar sebuah bola merah yang dapat di-translasi
void drawSphere() {
    glColor3f(1.0, 0.0, 0.0);  // Merah
    glTranslatef(sphereX, 0.0, sphereZ);  // Sesuaikan nilai agar bola tidak terlalu dekat
    glutSolidSphere(1.0, 50, 50);
}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(angle, 1.0, 1.0, 0.0);

    drawCube();
    drawSphere();

    glutSwapBuffers();
}

// Fungsi reshape
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi keyboard untuk tombol-tombol normal
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q':
        exit(0);
        break;
    }

    glutPostRedisplay();
}

// Fungsi special keys untuk tombol panah
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        cameraY += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 0.1f;
        break;
    case GLUT_KEY_LEFT:
        cameraX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        cameraX += 0.1f;
        break;
    }

    glutPostRedisplay();
}

// Fungsi handleKeyPress untuk tombol W, A, S, D
void handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        sphereZ -= 0.1f;
        break;
    case 's':
    case 'S':
        sphereZ += 0.1f;
        break;
    case 'a':
    case 'A':
        sphereX -= 0.1f;
        break;
    case 'd':
    case 'D':
        sphereX += 0.1f;
        break;
    }

    glutPostRedisplay();
}

// Fungsi update untuk animasi
void update(int value) {
    angle += 1.0f;
    if (angle > 360) {
        angle -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(60, update, 0);
}

// Fungsi main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL 3D Objects");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(25, update, 0);

    // Menambahkan callback untuk handleKeyPress
    glutKeyboardFunc(handleKeyPress);

    glutMainLoop();

    return 0;
}
