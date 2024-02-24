#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<Image> img;
    Camera camera;
    Scene scene;
    Renderer renderer;

    Initializer::ThreeSpheresTest(img, camera, scene, renderer);

    MainWindow w(img, camera, scene, renderer);
    w.show();
    return a.exec();
}
