#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float angle = 0.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f, z=5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
//************************************************************************************//
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
   glColor3f(1.0f, 1.0f, 0); //seta a cor
   glTranslatef(0.0f ,0.75f, 0.0f); // faz a translação
   glutSolidCube(0.3); //plota o cubo
    //glutSolidTeapot(0.7); bule :D
}


// movimentos
void computePos(float deltaMove)
{

    // Gambiarra para fazer o strafe :)
    if (deltaMove == 0.4f) {
        x -= (cos(0)) * 0.1;
        z -= (sin(0)) * 0.1;
    } else if (deltaMove == -0.4f) {
        x += (cos(0)) * 0.1;
        z += (sin(0)) * 0.1;

    // Andando pra frente/trás
    } else {
        x += deltaMove * lx * 0.1f;
        z += deltaMove * lz * 0.1f;
    }

}

//renderizando
void renderScene(void)
{
    // se for um movimento, faz o que foi pedido
    if (deltaMove) computePos(deltaMove);
    // Limpa buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reinicia as transformações
    glLoadIdentity();
    // põe a câmera
    gluLookAt( x, 1.0f, z,
               x+lx, 1.0f, z+lz,
               0.0f, 1.0f, 0.0f);

    glColor3f(0.2f, 0.7f, 0.3f);
    glBegin(GL_QUADS);
    // Desenha o chão
    glVertex3f(-15,0,-15);
    glVertex3f(-15,0,15);
    glVertex3f(15,0,15);
    glVertex3f(15,0,-15);

    // Teto
    glColor3f(0.7f, 0.7f, 0.3f);
    glVertex3f(-15,10,-15);
    glVertex3f(15,10,-15);
    glVertex3f(15,10,15);
    glVertex3f(-15,10,15);

    // Paredes
    glColor3f(0.3f, 0.3f, 0.3f);

    /*entrada (tá em preto, sem paredes...

    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glColor3f(0.3f, 0.3f, 1.0f); */

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

// Desenha a caixa
    glPushMatrix();
    glTranslatef(0.0,0,0.0);
    desenhaCaixa();
    glPopMatrix();
    glutSwapBuffers();
}

// Processa teclas especiais
void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == 27) //testa se foi pressionado 'esc'
        exit(0);
}

// Processa as teclas de movimento, passando valores para deltaMove, que vão ser usados na função de computar os movimentos!
// Não sei o motivo, mas 'wasd' ainda não funcionam
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
}

// Quando o usuário soltar a tecla, o movimento tem que parar, então seto o deltaMove para 0.
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

// Processa movimentação do mouse
void mouseMove(int x, int y)
{
    //Botão esquerdo do mouse deve estar clicado, esse valor é alterado na função 'mouseButton'...
    if (xOrigin >= 0)
    {
        deltaAngle = (x - xOrigin) * 0.01f;

        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

// Inicializa a interação do usuário através do mouse
void mouseButton(int button, int state, int x, int y)
{
    // Botão esquerdo deve estar clicado, facilita testes, sem trancar o mouse na tela.
    if (button == GLUT_LEFT_BUTTON) {
    // caso solte o clique
    if (state == GLUT_UP)
    {
        angle += deltaAngle;
        xOrigin = -1;
    }
    //seta o xOrigin baseado no movimento!
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
    glutInitWindowPosition(100,100); // seta a posição da janela
    glutInitWindowSize(600,400); // seta o tamanho da janela
    glutCreateWindow("Trabalho CG"); // título da janela

    glutDisplayFunc(renderScene); // função de dispĺay
    glutReshapeFunc(changeSize); // redesenho
    glutIdleFunc(renderScene);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop(); // deixa o app em loop

    return 1;
}
