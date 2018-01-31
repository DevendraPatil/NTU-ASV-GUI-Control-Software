/**
 * @file /qlistener/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "/home/devendra/catkin_ws/src/pubimage1/include/pubimage1/main_window.hpp"
#include "/home/devendra/catkin_ws/src/pubimage1/include/pubimage1/qnode.hpp"
//#include "/home/devendra/catkin_ws/src/pubimage/include/pubimage/listener1.hpp"
/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    QNode listener(argc,argv,"qlistener");
  // Listenerv listener1(argc,argv);//video

    MainWindow w(&listener);

   //MainWindow a(&listener1);//vide0
  w.show();
  //  a.show();
    //QObject::connect(&listener,SIGNAL(Update_Image(const QPixmap*)),&w,SLOT(updatePixmap(const QPixmap*)));
   // QObject::connect(&listener1,SIGNAL(Update_Image1(const QPixmap*)),&a,SLOT(updatePixmap1(const QPixmap*)));//video

    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
