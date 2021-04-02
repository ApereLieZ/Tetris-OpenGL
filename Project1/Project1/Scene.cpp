#define _CRT_SECURE_NO_WARNINGS
#include "Scene.h"
#include <gl/glut.h>
#include "utils.h"
#include "Cube.h"
#include <iostream>
#include <cstdlib>
#include "Logic.h"
#include <string>
using namespace GraphUtils;
namespace TetrisGame {

    Logic logic;

    
    Scene::Scene(float xStep, float zStep) {
        this->xStep = xStep;
        this->zStep = zStep;

        gameField = new int* [row];
        for (int i = 0; i < row; i++)
            gameField[i] = new int[coll];

        for (int i = 0; i < row; i++)  
            for (int j = 0; j < coll; j++)
            {
                gameField[i][j] = 0;
            }

        initialize();
    }

    void Scene::initialize()
    {
        distZ = -20;
        angleX = 0;
        angleY = 90;
        time = 0;
        finish = false;
        logic.spawnFigure();
    }

    void Scene::on_paint() {
        char GameText = logic.getScore();
        // визначаємо блакитний колір для очищення:
        glClearColor(0, 0.5, 0.5, 0);

        // показуємо очищене вікно:

        glViewport(0, 0, width, height);

        // Ініціалізуємо параметри матеріалів і джерела світла:
        float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // колір фонового освітлення 
        float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // колір дифузного освітлення 
        float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// колір дзеркального відображення
        float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла

        // Встановлюємо параметри джерела світла:
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // Визначаємо блакитний колір для очищення:
        if (finish)
        {
            glClearColor(0, 0.7, 0.7, 0);
        }
        else
        {
            glClearColor(0, 0.5, 0.5, 0);
        }

        // Очищуємо буфери:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        char text[128];
        sprintf(text, "Time: %d sec. Score: %i", time, logic.getScore());

        // Для відображення тексту, краще використовувати ортографічну проекцію:
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 1, 0); // жовтий текст
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
        glPopMatrix();

        // Включаємо режим роботи з матрицею проекцій:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // Задаємо усічений конус видимості в лівосторонній системі координат, 
        // 60 - кут видимості в градусах по осі у,
        // width/height - кут видимості уздовж осі x,
        // 1 и 100 - відстань від спостерігача до площин відсікання по глибині:
        gluPerspective(60, width / height, 1, 100);

        // Включаємо режим роботи з видовою матрицею:
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, distZ);	// камера з початку координат зсувається на distZ, 
        glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім обертається по осі Oy
        glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім обертається по осі Ox
        glEnable(GL_DEPTH_TEST);	// включаємо буфер глибини (для відсікання невидимих частин зображення)

                                    // Включаємо режим для установки освітлення:
        glEnable(GL_LIGHTING);

        // Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
        glEnable(GL_LIGHT0);

        //glTranslatef(2.5, -5.0, 0.0);
                                                                       //DRAW
        Cube(-5.5, 0, 0.5, 0.95, 0.95, row, diffGray, ambiGray, specGray).draw();
        Cube(0, 0, row/2, coll, 0.95, 0.95, diffGray, ambiGray, specGray).draw();
        Cube(5.5, 0, 0.5, 0.95, 0.95, row, diffGray, ambiGray, specGray).draw();


        for (int i = 0; i < 4; i++) {
            Cube((logic.a[i].y)-(float(coll) / 2 - 0.5), 0, (logic.a[i].x)-(float(row) / 2), 0.95, 0.95, 0.95, diffBlue, ambiBlue, specBlue).draw();
        }
        

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < coll; j++) {

                switch (gameField[i][j])
                {
                case 1: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffBlue, ambiBlue, specBlue).draw(); break;
                case 2: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffGreen, ambiGreen, specGreen).draw(); break;
                case 3: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffRed, ambiRed, specRed).draw(); break;
                case 4: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffYellow, ambiYellow, specYellow).draw(); break;
                case 5: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffOrange, ambiOrange, specOrange).draw(); break;
                case 6: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffViolet, ambiViolet, specViolet).draw(); break;
                case 7: Cube((j) - (float(coll) / 2 - 0.5), 0, (i) - (float(row) / 2), 0.95, 0.95, 0.95, diffYellow, ambiYellow, specYellow).draw(); break;
                default:
                    break;
                }           
                
                
               /* if (gameField[i][j] == 0) {
                    Cube((1 * j) - (float(coll) / 2 - 0.5), 0, (1 * i) - (float(row) / 2), 0.95, 0.95, 0.95, diffYellow, ambiYellow, specYellow).draw();
                }*/

            }
            
        }

        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glFlush();
        glutSwapBuffers();
	}
    void Scene::on_size(int width, int height)
    {
        this->width = width;
        if (height == 0)
            height = 1;
        this->height = height;
    }

    // Оброблювач подій, пов'язаних з натисканням кнопок миші
    void Scene::on_mouse(int button, int state, int x, int y)
    {
        // Зберігаємо поточні координати миші:
        mouseX = x;
        mouseY = y;
        this->button = button;  // зберігаємо інформацію про кнопки
        if (finish)
        {
            return;
        }
    }

    // Оброблювач подій, пов'язаних з пересуванням миші з натисненою кнопкою
    void Scene::on_motion(int x, int y)
    {
        if (button == 0){
            angleX += x - mouseX;
            angleY += y - mouseY;
            mouseX = x;
            mouseY = y;
        }
        else if (button == 2) {
            //gameField[7][9] = 1;
            std::cout << "a";
        }
    }


    // Оброблювач подій, пов'язаних з натисненням функціональних клавіш і стрілок 
    void Scene::on_special(int key, int x, int y)
    {
        switch (key) {
        case GLUT_KEY_UP:   // наближення
            logic.tryToRotate(gameField, row, coll);
            break;
        case GLUT_KEY_DOWN: // віддалення
            logic.downFigure( gameField,  row,  coll);
            break;
        case GLUT_KEY_LEFT:
            logic.moveFigure(1, gameField, row, coll);
            break;
        case GLUT_KEY_RIGHT:
            logic.moveFigure(-1, gameField, row, coll);
            break;
        }

    }


    int tick = 0; // лічильник, значення якого змінюється кожні 25 мс
    int gametic = 1;
                  // Оброблювач події від таймера
    void Scene::on_timer(int value)
    {
        gametic++;
        tick++;
        if (tick >= 40) // нарахували наступну секунду
        {
            if (!finish)// секунди нарощуються, якщо гру не закінчено
            {
                time++;
            }
            tick = 0;   // скинули лічильник
        }
        if (gametic >= 20) {
            gametic = 0;
            logic.downFigure(gameField, row, coll);
        }
        on_paint();     // здійснюємо перемалювання вікна
    }



}
