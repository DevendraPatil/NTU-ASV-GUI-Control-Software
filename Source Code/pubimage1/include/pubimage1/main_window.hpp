/**
 * @file common/main_window.hpp
 *
 * @brief Qt based gui for eros_qtalker.
 *
 * @date November 2010
 **/
#ifndef QTUTORIALS_MAIN_WINDOW_H
#define QTUTORIALS_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "QProcess"
/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(QNode *node, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();
Ui::MainWindowDesign ui;
    QNode *qnode;
     // void run1();
public Q_SLOTS:
	// Put automatically triggered slots here (because of connectSlotsByName())
	// void on_button_enable_clicked(bool check); // example only
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);

       //	void on_c2_stateChanged(int state);
	//void on_c2_clicked(bool check );
	void about();
        void publish();
	void suspublish();
	void killpublish();
	void on_push_clicked(bool check);
	void on_suspb_clicked(bool check);
	void on_killpb_clicked(bool check);
	void subscribeimg();
	void suspendimg();
        void killimg();
	void subscribevideo();
	void suspendvideo();
        void killvideo();

	void startgps();
	void susgps();
	void killgps();
	void startimu();
	void susimu();
	void killimu();
	void cmdline();
	void killterm();
	void killone();
	void on_killterm_clicked(bool check);
	void normcmd();
	void keyboardop();
        void joystickop();
 void edgeImage();
 //void subimage()=0;
//void ros_comms_init();
    /******************************************
    ** Manual connections
    *******************************************/
    //void updateLoggingView(); // no idea why this can't connect automatically
        void updatePixmap(const QPixmap* image);
        void updatePixmap1(const QPixmap* image1);
	void updatePixmap2(const QPixmap* image2);
	void updatePixmap3(const QPixmap* image3);
	void updatePixmap4(const QPixmap* image4);
	void updatePixmap5(const QPixmap* image5);
       void updatePixmap6(const QPixmap* image6);//canny
        void  updateLoggingViews(); //for subscriber
	void  updateLoggingViews1();
	void  updateLoggingViewsgps();
	void  updateLoggingViewsimu();
//private:
   // Ui::MainWindowDesign ui;
    //QNode *qnode;
    
       
};

#endif // QTUTORIALS_MAIN_WINDOW_H
