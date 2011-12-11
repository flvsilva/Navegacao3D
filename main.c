
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>

float angle = 0.0f;


float lx=0.0f,lz=-1.0f;


float x=0.0f, z=5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void changeSize(int w, int h)
{
    // Evitando divisão por zero :)
    if (h == 0) h = 1;

    float ratio =  w * 1.0 / h;

    // Matriz de projeção
    glMatrixMode(GL_PROJECTION);

    // Reinicia
    glLoadIdentity();

    // Seta o viewport para toda a janela
    glViewport(0, 0, w, h);

    // Seta a perspectiva correta
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Volta para o Modelview
    glMatrixMode(GL_MODELVIEW);
}

//desenho da caixa
void desenhaCaixa()
{
    glColor3f(1.0f, 1.0f, 0);
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutWireCube(0.3);

}

// movimentos
void computePos(float deltaMove)
{

    if (deltaMove == 0.4f) {
        float yrotrad;
        //yrotrad = (( 0 ) / 180 * 3.14f);
        x -= (cos(0)) * 0.1;
        z -= (sin(0)) * 0.1;
    } else if (deltaMove == -0.4f) {
        float yrotrad;
        yrotrad = (( 0 ) / 180 * 3.14f);
        x += (cos(yrotrad)) * 0.1;
        z += (sin(yrotrad)) * 0.1;
    } else {
        x += deltaMove * lx * 0.1f;
        z += deltaMove * lz * 0.1f;
    }

}

//renderizando

void renderScene(void)
{

    if (deltaMove)

        computePos(deltaMove);

    // Limpa buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reinicia as transformações
    glLoadIdentity();
    // põe a câmera
    gluLookAt( x, 1.0f, z,
               x+lx, 1.0f, z+lz,
               0.0f, 1.0f, 0.0f);

    // Desenha o chão
    glColor3f(0.2f, 0.7f, 0.3f);
    glBegin(GL_QUADS);
    /* Floor */


    glVertex3f(-15,0,-15);
    glVertex3f(-15,0,15);
    glVertex3f(15,0,15);
    glVertex3f(15,0,-15);

    glColor3f(0.7f, 0.7f, 0.3f);
    /* Ceiling */
    glVertex3f(-15,10,-15);
    glVertex3f(15,10,-15);
    glVertex3f(15,10,15);
    glVertex3f(-15,10,15);
    /* Walls */
    glColor3f(0.3f, 0.3f, 0.3f);

    //entada...
     /*
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1); */
    //glColor3f(0.3f, 0.3f, 1.0f);
    glVertex3f(-15,-15,-15);
    glVertex3f(15,-15,-15);
    glVertex3f(15,15,-15);
    glVertex3f(-15,15,-15);

    glVertex3f(15,15,15);
    glVertex3f(15,-15,15);
    glVertex3f(15,-15,-15);
    glVertex3f(15,15,-15);

    glVertex3f(-15,15,15);
    glVertex3f(-15,-15,15);
    glVertex3f(-15,-15,-15);
    glVertex3f(-15,15,-15);

    glEnd();

// Desenha as caixas
    int i = 0;
    int j = 0;
    glPushMatrix();
    glTranslatef(i*10.0,0,j * 10.0);
    desenhaCaixa();
    glPopMatrix();
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == 27)
        exit(0);
}

void pressKey(int key, int xx, int yy)
{
    if (key == 'w' || key == GLUT_KEY_UP)
    {
        deltaMove = 0.5f;

    }
    else if (key == 's' || key == GLUT_KEY_DOWN)
    {
        deltaMove = -0.5f;

    }
    else if (key == 'a' || key == GLUT_KEY_LEFT)
    {
        deltaMove = 0.4f;

    }
    else if (key == 'd' || key == GLUT_KEY_RIGHT)
    {
        deltaMove = -0.4f;

    }
/*
    switch (key)
    {
        // anda para frente
    case GLUT_KEY_UP :
        deltaMove = 0.5f;
        break;
    case (key == 'w') :
        deltaMove = 0.5f;
        break;
        // anda para trás
    case GLUT_KEY_DOWN :
        deltaMove = -0.5f;
        break;
    case (key == 's') :
        deltaMove = -0.5f;
        break;
    case GLUT_KEY_LEFT :
        deltaMove = 1.11f;
        break;

    case GLUT_KEY_RIGHT :
        deltaMove = -1.11f;
        break;

    }

    */
}

void releaseKey(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_UP :
    case GLUT_KEY_DOWN :
    case GLUT_KEY_LEFT :
    case GLUT_KEY_RIGHT :
        deltaMove = 0;
        break;
    }
}

void mouseMove(int x, int y)
{

    if (xOrigin >= 0)
    {


        deltaAngle = (x - xOrigin) * 0.01f;

        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y)
{


    if (button == GLUT_LEFT_BUTTON) {


    if (state == GLUT_UP)
    {
        angle += deltaAngle;
        xOrigin = -1;
    }
    else
    {
        xOrigin = x;
    }
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,400);
    glutCreateWindow("Trabalho CG");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);


    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 1;
}
