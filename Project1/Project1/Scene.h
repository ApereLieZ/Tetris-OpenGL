#ifndef Scene_h
#define Scene_h

namespace TetrisGame
{

    struct activePiec
    {
        int x, y;
    };

    const int coll = 10;
    const int row = 20;

    class Scene
    {

        int score;
        int **gameField; // ігрове поле
        int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)
        float angleX, angleY; // поточний кут повороту сцени 
        float mouseX, mouseY; // поточні координати
        float width, height;  // Розміри вікна
        float distZ;          // відстань по осі Z до сцени
        bool finish;          // ознака того, що гру завершено
        float xStep, zStep;   // відстань між блоками
        int time;             // поточний час у секуднах
        int dx = 0;
        
    public:
        Scene(float xStep, float zStep);
        ///~Scene();
        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);
        
       // bool moveDisk(int xFrom, int zFrom, int xTo, int zTo);
    private:
        void initialize();
    };

}

#endif