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
        int **gameField; // ������ ����
        int button;           // ������ ���� (-1 - �� ���������, 0 - ���, 2 - �����)
        float angleX, angleY; // �������� ��� �������� ����� 
        float mouseX, mouseY; // ������ ����������
        float width, height;  // ������ ����
        float distZ;          // ������� �� �� Z �� �����
        bool finish;          // ������ ����, �� ��� ���������
        float xStep, zStep;   // ������� �� �������
        int time;             // �������� ��� � ��������
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