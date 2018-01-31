/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "/home/devendra/catkin_ws/src/pubimage1/include/pubimage1/main_window.hpp"
#include <QPixmap>
#include "QProcess"
#include <signal.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include "/home/devendra/catkin_ws/src/pubimage1/include/pubimage1/qnode.hpp"
#include <std_msgs/String.h>
#include <sstream>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <QCheckBox>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>     //make sure to include the relevant headerfiles
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cvaux.h>
#include <math.h>
#include <cxcore.h>
#include <highgui.h>


double PI = 3.1415926;
using namespace std;
/*******GPS stuff****/
float old=789;

int pid;
/****command window stuff**********/
int kt=0,kc=0;
int out;
/*******************************/

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/


MainWindow::MainWindow(QNode *node, QWidget *parent) :
QMainWindow(parent),
qnode(node)
{
ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

// ReadSettings();
setWindowIcon(QIcon(":/images/icon.png"));
ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
setWindowTitle(QApplication::translate("MainWindowDesign", qnode->nodeName().c_str(), 0, QApplication::UnicodeUTF8));
QObject::connect(qnode, SIGNAL(clicked()), this, SLOT(subscribeimg()));

/*********************
** Logging
**********************/
ui.pubview->setModel(qnode->loggingModel2());
QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingViews1()));
//subscriber
ui.susview->setModel(qnode->loggingModel1());
QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingViews()));
ui.lbimage->setPixmap(qnode->PixmapModel());
//to fit the image to the text label size
ui.lbimage->setScaledContents( true );
ui.lbimage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

/**************camera2***********/
ui.lbimage2->setPixmap(qnode->PixmapModel2());
ui.lbimage2->setScaledContents( true );
ui.lbimage2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
/******************************************/
/**************camera3***********/
ui.lbimage3->setPixmap(qnode->PixmapModel3());
ui.lbimage3->setScaledContents( true );
ui.lbimage3->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
/******************************************/
/**************camera4***********/
// ui.view_logging->setModel(qnode->loggingModel());
ui.lbimage4->setPixmap(qnode->PixmapModel4());
ui.lbimage4->setScaledContents( true );
ui.lbimage4->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
/******************************************/
/**************camera5***********/
// ui.view_logging->setModel(qnode->loggingModel());
ui.lbimage5->setPixmap(qnode->PixmapModel5());
ui.lbimage5->setScaledContents( true );
ui.lbimage5->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
/******************************************/
/***********video***************/
ui.video->setPixmap(qnode->PixmapModel1());
ui.video->setScaledContents( true );
ui.video->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
/******************/
/***********video live feed***************/
ui.vidliv->setPixmap(qnode->PixmapModel6());
ui.vidliv->setScaledContents( true );
ui.vidliv->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
/******************/
/*************GPS Subscriber******************/
ui.gpsview->setModel(qnode->loggingModelgps());
QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingViewsgps()));
/**********************************************/

/*************IMU Subscriber******************/
ui.imuview->setModel(qnode->loggingModelimu());
QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingViewsimu()));
/**********************************************/

//ROS Image in Master
QPixmap pix("/home/devendra/Downloads/ROS.png");
int w= ui.pic->width();
int h=ui.pic->height();
ui.pic->setPixmap(pix.scaled(400,300,Qt::KeepAspectRatio));

//front page image
QPixmap pix1("/home/devendra/Downloads/frontpagenew(1).jpg");
int w1= ui.frontpage->width();
int h1=ui.frontpage->height();
ui.frontpage->setPixmap(pix1.scaled(w1,h1,Qt::KeepAspectRatio));


//keyboard image
QPixmap keyi("/home/devendra/Downloads/keyboard.png");
int w2= ui.keyb->width();
int h2=ui.keyb->height();
ui.keyb->setPixmap(keyi.scaled(w2,h2,Qt::KeepAspectRatio));
/***********/

//Xbox image
QPixmap xb("/home/devendra/Downloads/xbox.jpg");
int w3= ui.xbox->width();
int h3=ui.xbox->height();
ui.xbox->setPixmap(xb.scaled(w3,h3,Qt::KeepAspectRatio));
/********************/

//PS image
QPixmap psc("/home/devendra/Downloads/ps.png");
int w4= ui.ps->width();
int h4=ui.ps->height();
ui.ps->setPixmap(psc.scaled(w4,h4,Qt::KeepAspectRatio));
/**************/

//ntu image
QPixmap ntu("/home/devendra/Downloads/logo_ntu_new(2).png");
int w5= ui.logo1->width();
int h5=ui.logo1->height();
ui.logo1->setPixmap(ntu.scaled(w5,h5,Qt::KeepAspectRatio));
/**************/

//maritime image
QPixmap mar("/home/devendra/Downloads/maritime.png");
int w6= ui.logo2->width();
int h6=ui.logo2->height();
ui.logo2->setPixmap(mar.scaled(w6,h6,Qt::KeepAspectRatio));
/**************/

//camera postions
QPixmap cams("/home/devendra/Downloads/wamvcameras(3).jpg");
int w7= ui.cams->width();
int h7=ui.cams->height();
ui.cams->setPixmap(cams.scaled(w7,h7,Qt::KeepAspectRatio));
/**************/

QObject::connect(qnode,SIGNAL(Update_Image(const QPixmap*)),this,SLOT(updatePixmap(const QPixmap*)));//camera
QObject::connect(qnode,SIGNAL(Update_Image1(const QPixmap*)),this,SLOT(updatePixmap1(const QPixmap*)));//video
QObject::connect(qnode,SIGNAL(Update_Image2(const QPixmap*)),this,SLOT(updatePixmap2(const QPixmap*)));//camera2
QObject::connect(qnode,SIGNAL(Update_Image3(const QPixmap*)),this,SLOT(updatePixmap3(const QPixmap*)));//camera3
QObject::connect(qnode,SIGNAL(Update_Image4(const QPixmap*)),this,SLOT(updatePixmap4(const QPixmap*)));//camera4
QObject::connect(qnode,SIGNAL(Update_Image5(const QPixmap*)),this,SLOT(updatePixmap5(const QPixmap*)));//camera5
QObject::connect(qnode,SIGNAL(Update_Image6(const QPixmap*)),this,SLOT(updatePixmap6(const QPixmap*)));//videolive

//QObject::connect(qnode,SIGNAL(updatecanny(const QPixmap)),this,SLOT(updatePixmapcanny(const QPixmap)));//canny

//QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
QObject::connect(qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
QObject::connect(ui.about, SIGNAL(clicked()), this, SLOT(about()));

/****Publisher and subscriber buttons*************/
QObject::connect(ui.push, SIGNAL(triggered(bool)), this, SLOT(publish()));
QObject::connect(ui.suspb, SIGNAL(triggered(bool)), this, SLOT(suspublish()));
QObject::connect(ui.killpb, SIGNAL(triggered(bool)), this, SLOT(killpublish()));
/*******************************************************/
QObject::connect(ui.can, SIGNAL(clicked()), this, SLOT(edgeImage()));

/********************Camera buttons**********************/
QObject::connect(ui.startcamera, SIGNAL(clicked()), this, SLOT(subscribeimg()));
QObject::connect(ui.suspendcamera, SIGNAL(clicked()), this, SLOT(suspendimg()));
QObject::connect(ui.killcamera, SIGNAL(clicked()), this, SLOT(killimg()));
/**********************************************************************/

/********************Video buttons**********************/
QObject::connect(ui.startvideo, SIGNAL(clicked()), this, SLOT(subscribevideo()));
QObject::connect(ui.suspendvideo, SIGNAL(clicked()), this, SLOT(suspendvideo()));
QObject::connect(ui.killvideo, SIGNAL(clicked()), this, SLOT(killvideo()));
/**********************************************************************/
/*********************** GPS buttons*********************/
QObject::connect(ui.startgps, SIGNAL(clicked()), this, SLOT(startgps()));
QObject::connect(ui.susgps, SIGNAL(clicked()), this, SLOT(susgps()));
QObject::connect(ui.killgps, SIGNAL(clicked()), this, SLOT(killgps()));
/*********************************************************/
/************************IMU buttons************************/
QObject::connect(ui.startimu, SIGNAL(clicked()), this, SLOT(startimu()));
QObject::connect(ui.susimu, SIGNAL(clicked()), this, SLOT(susimu()));
QObject::connect(ui.killimu, SIGNAL(clicked()), this, SLOT(killimu()));
/*************************************************************/
QObject::connect(ui.termgo, SIGNAL(clicked()), this, SLOT(cmdline()));
QObject::connect(ui.killterm, SIGNAL(triggered(bool)), this, SLOT(cmdline()));
QObject::connect(ui.normgo, SIGNAL(clicked()), this, SLOT(normcmd()));
QObject::connect(ui.killone, SIGNAL(clicked()), this, SLOT(killone()));
/*******************Keyboard and JOystick********/
QObject::connect(ui.keyboard_teleop, SIGNAL(clicked()), this, SLOT(keyboardop()));
QObject::connect(ui.joystick_teleop, SIGNAL(clicked()), this, SLOT(joystickop()));

}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/
/************ Camera Buttons******************/
int r=0,s=0,t=0;
int cam1=0,cam2=0,cam3=0,cam4=0,cam5=0;
void MainWindow::subscribeimg() {

if(ui.camerac->isChecked())
{
r=1;
QPixmap dcam5("/home/devendra/Downloads/black.jpg");
if(ui.c1->isChecked())
{
cam1=1;
}
else{cam1=0;
ui.lbimage->setPixmap(dcam5.scaled(400,300,Qt::KeepAspectRatio));}

if(ui.c2->isChecked())
{
QPixmap dp("/home/devendra/Downloads/wamv1.JPG");
ui.lbimage2->setPixmap(dp.scaled(400,300,Qt::KeepAspectRatio));
}
else
{
cam2=0;
ui.lbimage2->setPixmap(dcam5.scaled(400,300,Qt::KeepAspectRatio));
}
if(ui.c3->isChecked())
{
cam3=1;
}
else{cam3=0;  ui.lbimage3->setPixmap(dcam5.scaled(400,300,Qt::KeepAspectRatio));}
if(ui.c4->isChecked())
{
cam4=1;
}
else{cam4=0;  ui.lbimage4->setPixmap(dcam5.scaled(400,300,Qt::KeepAspectRatio));}
if(ui.c5->isChecked())
{
cam5=1;
}
else{cam5=0; ui.lbimage5->setPixmap(dcam5.scaled(400,300,Qt::KeepAspectRatio));}

 }
else
{
QMessageBox nocam;
nocam.setText("Please Enable the camera module in configuration tab.");
nocam.exec();
}
}
void MainWindow::suspendimg()
{
s=1;
}
void MainWindow::killimg()
{
t=1;
}

/************ Video Buttons******************/
int u=0,v=0,w=0;
void MainWindow::subscribevideo()
{
if(ui.videoc->isChecked())
{
u=1;
}
else
{
QMessageBox novid;
novid.setText("Please Enable the Video camera module in configuration tab.");
novid.exec();
}
}
void MainWindow::suspendvideo()
{
v=1;
}
void MainWindow::killvideo()
{
w=1;
}

/****Publisher and Subscriber Buttons******/
int k=0,j=0,l=0;

void MainWindow::publish()
{
k=1;
}

void MainWindow::suspublish()
{
j=1;
}

void MainWindow::killpublish()
{
l=1;
}

void MainWindow::on_push_clicked(bool check )
{
publish();
}

void MainWindow::on_suspb_clicked(bool check )
{
suspublish();
}

void MainWindow::on_killpb_clicked(bool check )
{
killpublish();
}
/*********************************************/

/**************GPS buttons********************/
int g1=0,g2=0,g3=0;
void MainWindow::startgps()
{
if(ui.gpsc->isChecked())
{
g1=1;
}
else
{
QMessageBox nogps;
nogps.setText("Please Enable the GPS module in configuration tab.");
nogps.exec();
}
}
void MainWindow::susgps()
{
g2=1;
}
void MainWindow::killgps()
{
g3=1;
}

/*************************************************/
/*******************IMU BUttons*******************/
int i1=0,i2=0,i3=0;
void MainWindow::startimu()
{
if(ui.imuc->isChecked())
{
i1=1;
}
else
{
QMessageBox noimu;
noimu.setText("Please Enable the IMU module in configuration tab.");
noimu.exec();
}
}
void MainWindow::susimu()
{
i2=1;
}
void MainWindow::killimu()
{
i3=1;
}
/************************************************/

/******************Command line*******************/
void MainWindow::on_killterm_clicked(bool check )
{
killterm();
kt=1;
}

void MainWindow::about()
{
QMessageBox abt;
abt.setWindowTitle("About");
abt.setIconPixmap(QPixmap("/home/devendra/Downloads/about.png"));
abt.exec();
}

void MainWindow::showNoMasterMessage()
{
QMessageBox msgBox;
msgBox.setText("Couldn't find the ros master.");
msgBox.exec();
close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check )
{
if(ui.masterc->isChecked())
{
if ( ui.checkbox_use_environment->isChecked() ) {
if ( !qnode->on_init() ) {
showNoMasterMessage();
} else
{
ui.button_connect->setEnabled(false);
}

} else
{
if ( ! qnode->on_init(ui.line_edit_master->text().toStdString(),ui.line_edit_host->text().toStdString() )) {
showNoMasterMessage();
} else
{
ui.button_connect->setEnabled(false);
ui.line_edit_master->setReadOnly(true);
ui.line_edit_host->setReadOnly(true);
}
}
}
else
{
QMessageBox nomas;
nomas.setText("Please Enable the Master in configuration tab.");
nomas.exec();
}
}

void MainWindow::on_checkbox_use_environment_stateChanged(int state)
{
bool enabled;
if ( state == 0 ) {
enabled = true;
} else {
enabled = false;
}
ui.line_edit_master->setEnabled(enabled);
ui.line_edit_host->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
/*
void MainWindow::updatePixmapcanny(const QPixmap imagecan)
{
ui.label_can->setPixmap(imagecan);
}*/

void MainWindow::updatePixmap(const QPixmap* image)
{
ui.lbimage->setPixmap(*image);
}
void MainWindow::updatePixmap1(const QPixmap* image1)
{
ui.video->setPixmap(*image1);
}
void MainWindow::updatePixmap2(const QPixmap* image2)
{
ui.lbimage2->setPixmap(*image2);
}
void MainWindow::updatePixmap3(const QPixmap* image3)
{
ui.lbimage3->setPixmap(*image3);
}
void MainWindow::updatePixmap4(const QPixmap* image4)
{
ui.lbimage4->setPixmap(*image4);
}
void MainWindow::updatePixmap5(const QPixmap* image5)
{
ui.lbimage5->setPixmap(*image5);
}

void MainWindow::updatePixmap6(const QPixmap* image6)
{
ui.vidliv->setPixmap(*image6);
}


void MainWindow::updateLoggingViews1()
{
ui.pubview->scrollToBottom();
}
//subscriber
void MainWindow::updateLoggingViews()
{
ui.susview->scrollToBottom();
}

//GPS Subscriber
void MainWindow::updateLoggingViewsgps()
{
ui.gpsview->scrollToBottom();
}
//
//IMU Subscriber
void MainWindow::updateLoggingViewsimu()
{
ui.imuview->scrollToBottom();
}
//

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings()
{
QSettings settings("Qt-Ros Package", qnode->nodeName().c_str());
restoreGeometry(settings.value("geometry").toByteArray());
restoreState(settings.value("windowState").toByteArray());
QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
ui.line_edit_master->setText(master_url);
ui.line_edit_host->setText(host_url);
bool remember = settings.value("remember_settings", false).toBool();
ui.checkbox_remember_settings->setChecked(remember);
bool checked = settings.value("use_environment_variables", false).toBool();
ui.checkbox_use_environment->setChecked(checked);
if ( checked ) {
ui.line_edit_master->setEnabled(false);
ui.line_edit_host->setEnabled(false);
}
}

void MainWindow::WriteSettings()
{
QSettings settings("Qt-Ros Package", qnode->nodeName().c_str());
settings.setValue("geometry", geometry());
settings.setValue("master_url",ui.line_edit_master->text());
settings.setValue("host_url",ui.line_edit_host->text());
settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
settings.setValue("windowState", saveState());
settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));
}


void MainWindow::closeEvent(QCloseEvent *event)
{
qnode->shutdown();
QMainWindow::closeEvent(event);
}

/********** qnode**************/
QNode::QNode(int argc, char** argv, const std::string &name ) :
init_argc(argc),
init_argv(argv),
node_name(name)
{}

QNode::~QNode()
{
shutdown();
}
/**
 * This is called by the qt application to stop the ros node before the
 * qt app closes.
 */
void QNode::shutdown()
{
if(ros::isStarted()) {
ros::shutdown(); // explicitly needed since we use ros::start();
ros::waitForShutdown();
}
wait();
}

bool QNode::on_init() {
ros::init(init_argc,init_argv,node_name);
if ( ! ros::master::check() )
{
return false;
}
   
ros::start(); // our node handles go out of scope, so we want to control shutdown explicitly.
ros::NodeHandle n;
chatter_publisher = n.advertise<std_msgs::Float64>("chatter", 1000);
chatter_subscriber = n.subscribe("chatter", 1000, &QNode::myCallback, this);
chatter_subscriber_gps = n.subscribe("chatter", 1000, &QNode::myCallbackgps, this); //GPS Subscriber
chatter_subscriber_imu = n.subscribe("chatter", 1000, &QNode::myCallbackimu, this); //GPS Subscriber

/*********camera******/
image_transport::ImageTransport it_(n);
image_sub_ = it_.subscribe("/camera/image", 1,
&QNode::chatterCallback, this);
/***************/
/*******video*********/
image_transport::ImageTransport it_1(n);
image_sub_1 = it_1.subscribe("/usb_cam/image_raw", 1,
&QNode::chatterCallback1, this);
/************************/
/*******video liv*********/
image_transport::ImageTransport it_6(n);
image_sub_6 = it_6.subscribe("/usb_cam/image_raw", 1,
&QNode::chatterCallback6, this);
/************************/
/*********camera2******/
image_transport::ImageTransport it_2(n);
image_sub_2 = it_2.subscribe("/camera/image", 1,
&QNode::chatterCallback2, this);

/******************************/
/*********camera3******/
image_transport::ImageTransport it_3(n);
image_sub_3 = it_3.subscribe("/camera/image", 1,
&QNode::chatterCallback3, this);
/******************************/
/*********camera4******/
image_transport::ImageTransport it_4(n);
image_sub_4 = it_4.subscribe("/camera/image", 1,
 &QNode::chatterCallback4, this);
/******************************/
/*********camera5******/
image_transport::ImageTransport it_5(n);
image_sub_5 = it_5.subscribe("/camera/image", 1,
&QNode::chatterCallback5, this);
/******************************/
start();
return true;
}

bool QNode::on_init(const std::string &master_url, const std::string &host_url)
{
std::map<std::string,std::string> remappings;
remappings["__master"] = master_url;
remappings["__hostname"] = host_url;
ros::init(remappings,node_name);
if ( ! ros::master::check() )
{
return false;
}
ros::start(); // our node handles go out of scope, so we want to control shutdown explicitly.
ros::NodeHandle n;
// Add your ros communications here.
chatter_publisher = n.advertise<std_msgs::Float64>("chatter", 1000);
chatter_subscriber = n.subscribe("chatter", 1000, &QNode::myCallback, this);
chatter_subscriber_gps = n.subscribe("chatter", 1000, &QNode::myCallbackgps, this); //GPS Subscriber
chatter_subscriber_imu = n.subscribe("chatter", 1000, &QNode::myCallbackimu, this); //IMU Subscriber
/****camera***/
image_transport::ImageTransport it_(n);
image_sub_ = it_.subscribe("/camera/image", 1,
&QNode::chatterCallback, this);
/**************/
/******video*****/
image_transport::ImageTransport it_1(n);
image_sub_1 = it_1.subscribe("/usb_cam/image_raw", 1,
 &QNode::chatterCallback1, this);
/*******************/
/******video live*****/
image_transport::ImageTransport it_6(n);
image_sub_6 = it_6.subscribe("/usb_cam/image_raw", 1,
 &QNode::chatterCallback6, this);
/************************/
/*********camera2******/
image_transport::ImageTransport it_2(n);
image_sub_2 = it_2.subscribe("/camera/image", 1,
&QNode::chatterCallback2, this);
/******************************/
/*********camera3******/
image_transport::ImageTransport it_3(n);
image_sub_3 = it_3.subscribe("/camera/image", 1,
&QNode::chatterCallback3, this);
/******************************/
/*********camera4******/
image_transport::ImageTransport it_4(n);
image_sub_4 = it_4.subscribe("/camera/image", 1,
&QNode::chatterCallback4, this);
/******************************/
/*********camera5******/
image_transport::ImageTransport it_5(n);
image_sub_5 = it_5.subscribe("/camera/image", 1,
&QNode::chatterCallback5, this);
/******************************/
start();
return true;
}

/*********End of Qnode********/
/***************publisher and subsciber**********************/



void QNode::run()
{
ros::NodeHandle n;
ros::Rate loop_rate(10);
std_msgs::Float64 velocity; //create a variable of type "Float64",
double amplitude = 1.0;
double frequency = 5.0;
int dt = 0;

while ( ros::ok() )
{
ros::spinOnce();

if(!l && k && !j)
{
velocity.data = amplitude*sin(frequency*PI/180*dt); //phase increment by frequency*PI/180 radius each iteration
dt++;
ROS_INFO("Sending data %f", velocity.data);
chatter_publisher.publish(velocity); // publish the value--of type Float64--
std::stringstream ss;
ss << "velocity = " << velocity.data;
chatter_publisher.publish(velocity);
std::string s(ss.str());
log(Info,std::string("I sent: ")+s);
ros::spinOnce();
loop_rate.sleep();
}
else
{
k=0;j=0;
}

}

std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg)
{
logging_model2.insertRows(logging_model2.rowCount(),1);
std::stringstream logging_model_msg;
switch ( level ) {
case(Debug) : {
ROS_DEBUG_STREAM(msg);
logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
break;
 }
case(Info) : {
ROS_INFO_STREAM(msg);
logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
break;
}
case(Warn) : {
ROS_WARN_STREAM(msg);
logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
break;
}
case(Error) : {
ROS_ERROR_STREAM(msg);
logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
break;
}
case(Fatal) : {
ROS_FATAL_STREAM(msg);
logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
break;
}
}
QVariant new_row(QString(logging_model_msg.str().c_str()));
logging_model2.setData(logging_model2.index(logging_model2.rowCount()-1),new_row);
Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

/* *****END OF PUBLISHER**************************************************/

/* ******************************Subscriber*****************************************/

void QNode::myCallback(const std_msgs::Float64& message_holder)
{
log(Info, message_holder);
}

void QNode::log( const LogLevel &level, const std_msgs::Float64 &msg)
{
logging_model1.insertRows(logging_model1.rowCount(),1);
std::stringstream logging_model_msg;
switch ( level ) {
case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model1.setData(logging_model1.index(logging_model1.rowCount()-1),new_row);
    Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}
/*******************End of Subscriber**************************/


/*******************image listener***********************/



QImage QNode::cvtCvMat2QImage(const cv::Mat & image)
{
    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void QNode::chatterCallback(const sensor_msgs::ImageConstPtr& msg){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }
        px = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!t)
    {
    if(r && !s)
    {
        if(cam1)
        {
    Q_EMIT Update_Image(&px);
    }
                else{cam1=0;}
    }
    else{r=0;s=0;cam1=0;}
    }
}


/********************Video listener********************************/

QImage QNode::cvtCvMat2QImage1(const cv::Mat & image)
{

    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void QNode::chatterCallback1(const sensor_msgs::ImageConstPtr& msg1){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg1, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }

   /********************/
   cv::Mat out1;
        cv::Mat gray_out;
        cv::Mat canny_out;
        cv::Mat gray_out1;
  cv::Mat img1;


  cv::cvtColor(cv_ptr->image, gray_out, CV_BGR2GRAY);
       //cv::GaussianBlur(gray_out, gray_out, Size(3, 3), 0, 0);    // Replaces cv::boxFilter(gray_out, gray_out, -1, cv::Size(3,3)); or cvSmooth(gray_out, gray_out, CV_GAUSSIAN, 9,9);
       cv::Canny(gray_out, canny_out, 50, 125, 3);
       cv::cvtColor(canny_out, gray_out1, CV_GRAY2BGR);
       //cv::imshow( "CAMERA FEED", cv_ptr->image);
       //cv::imshow( "GRAY CAMERA", gray_out);
       //cv::imshow( "CANNY CAMERA", canny_out);
    //   cv::imshow( "CANNY EDGE DETECTION",gray_out1);


// cvWaitKey(50);


    /********************/
        px1 = QPixmap::fromImage(cvtCvMat2QImage(gray_out1));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!w)
    {
        if(u && !v)
    {
    Q_EMIT Update_Image1(&px1);
        }
        else { u=0; v=0;}

    }
}


/*********************/

/********************Video live listener********************************/

QImage QNode::cvtCvMat2QImage6(const cv::Mat & image)
{


    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void QNode::chatterCallback6(const sensor_msgs::ImageConstPtr& msg6){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg6, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }





        px6 = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!w)
    {
        if(u && !v)
    {
    Q_EMIT Update_Image6(&px6);
        }
        else { u=0; v=0;}

    }
}


/*********************/




/*********************GPS Subsciber*************************/

void QNode::myCallbackgps(const std_msgs::Float64& message_holder)
{

    loggps(Info, message_holder);

}


void QNode::loggps( const LogLevel &level, const std_msgs::Float64 &msg) {

        if(g1 && !g2 && !g3)
     {
    logging_modelgps.insertRows(logging_modelgps.rowCount(),1);
    std::stringstream logging_model_msg;

    switch ( level ) {
        case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_modelgps.setData(logging_modelgps.index(logging_modelgps.rowCount()-1),new_row);

    Q_EMIT loggingUpdated();// used to readjust the scrollbar

        old=msg.data;

    }


   else
        {
        g1=0;g2=0;
        }
}
/********************************************************/

/*********************IMU Subsciber*************************/

void QNode::myCallbackimu(const std_msgs::Float64& message_holder)
{


    logimu(Info, message_holder);

}


void QNode::logimu( const LogLevel &level, const std_msgs::Float64 &msg) {
     if(i1 && !i2 && !i3)
     {
    logging_modelimu.insertRows(logging_modelimu.rowCount(),1);
    std::stringstream logging_model_msg;
    switch ( level ) {
        case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << "received value is: " << msg.data;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_modelimu.setData(logging_modelimu.index(logging_modelimu.rowCount()-1),new_row);
    Q_EMIT loggingUpdated(); // used to readjust the scrollbar
     }
     else
     {
         i1=0;i2=0;
     }
}
/********************************************************/
/*******************command terminal*****************/

void MainWindow::cmdline()
{

    QProcess proc;
    QProcess proc1;
      QString command;
      QString command1;//Contains the command to be executed
  QStringList args;
QStringList args1;
QString cmd=ui.term->text();

QStringList pieces = cmd.split(" ");


command1="pgrep";
args1<<"-n";
command = "bash -c \""+cmd+" | pgrep -n >> ~/pid.txt\"";
proc.startDetached(command);
proc.close();


}


void MainWindow::killterm()
{
    QFile inputFile("/home/devendra/pid.txt");
    QString line;
    QStringList line1;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
         line = in.readLine();
         line1<<line;

       }
       inputFile.close();
    }
   qDebug()<<line1;
   ui.cmdtext->setText(line);
  int ty=line1.length();

  for(int g=0;g<ty;g++)
  {
   int pid1=line1[g].toInt();
   qDebug()<<pid1;
   kill(pid1,SIGTERM);
  }
  inputFile.remove();

}
void MainWindow::killone()
{
    QFile inputFile("/home/devendra/pid.txt");
    QString line;
    QStringList line1;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
         line = in.readLine();
         line1<<line;

       }
       inputFile.close();
    }
    int ty=line1.length();
    int pid=line1[ty-1].toInt();
    kill(pid,SIGTERM);

}



void MainWindow::keyboardop()

{
    if(ui.teleopc->isChecked())
    {

    }
    else {
          QMessageBox noteleop;
          noteleop.setText("Please Enable the Teleop module in configuration tab.");
          noteleop.exec();


    }


}


void MainWindow::joystickop()

{ if(ui.teleopc->isChecked())
    {

    }
    else {
          QMessageBox noteleop;
          noteleop.setText("Please Enable the Teleop module in configuration tab.");
          noteleop.exec();


    }


}
/***************NOrmal Commands*****************/
void MainWindow::normcmd()
{
QString normcommand=ui.norm->text();

if(normcommand=="displaycam")
  {  QString dispout="Displaying Image";

    subscribeimg();
  }
else if(normcommand=="stopcam")
{
    suspendimg();
}
else if(normcommand=="killcam")
{
    killimg();
}
else if(normcommand=="displayvideo")
{
subscribevideo();
}
else if(normcommand=="stopvideo")
{
    suspendvideo();
}
else if(normcommand=="killvideo")
{
    killvideo();
}
else if(normcommand=="displaygps")
{
    startgps();
}
else if(normcommand=="stopgps")
{
    susgps();
}
else if(normcommand=="killgps")
{
    killgps();
}
else if(normcommand=="displayimu")
{
    startimu();
}
else if(normcommand=="stopimu")
{
    susimu();
}
else if(normcommand=="killimu")
{
    killimu();
}



}
/***************camera2***********************************/

QImage QNode::cvtCvMat2QImage2(const cv::Mat & image)
{
    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}

void QNode::chatterCallback2(const sensor_msgs::ImageConstPtr& msg2){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg2, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }
        px2 = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!t)
    {
    if(r && !s)
{
    if(cam2)
    {


    Q_EMIT Update_Image2(&px2);
        }
        else { cam2=0;}
    }
    else {r=0;s=0;cam2=0;}
    }


}
/************************************************/
/***************camera3***********************************/

QImage QNode::cvtCvMat2QImage3(const cv::Mat & image)
{
    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void QNode::chatterCallback3(const sensor_msgs::ImageConstPtr& msg3){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg3, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }
        px3 = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!t)
    {
if(r && !s)
{
    if(cam3)
    {


    Q_EMIT Update_Image3(&px3);
        }
        else { cam3=0;}
    }
    else {r=0;s=0;cam3=0;}
    }

}
/************************************************/
/***************camera4***********************************/

QImage QNode::cvtCvMat2QImage4(const cv::Mat & image)
{
    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void QNode::chatterCallback4(const sensor_msgs::ImageConstPtr& msg4){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg4, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }
        px4 = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!t)
    {
    if(r && !s)
{
    if(cam4)
    {


    Q_EMIT Update_Image4(&px4);
        }
        else { cam4=0;}
    }
    else {r=0;s=0;cam4=0;}
    }

}
/************************************************/
/***************camera5***********************************/

QImage QNode::cvtCvMat2QImage5(const cv::Mat & image)
{
    QImage qtemp;
    if(!image.empty() && image.depth() == CV_8U)
    {
        const unsigned char * data = image.data;
        qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
        for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
        {
            for(int x = 0; x < image.cols; ++x)
            {
                QRgb * p = ((QRgb*)qtemp.scanLine (y)) + x;
                *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
            }
        }
    }
    else if(!image.empty() && image.depth() != CV_8U)
    {
        printf("Wrong image format, must be 8_bits\n");
    }
    return qtemp;
}
void QNode::chatterCallback5(const sensor_msgs::ImageConstPtr& msg5){


    cv_bridge::CvImagePtr cv_ptr;
      try
        {
          cv_ptr = cv_bridge::toCvCopy(msg5, sensor_msgs::image_encodings::BGR8);

        }
        catch (cv_bridge::Exception& e)
        {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
        }
        px5 = QPixmap::fromImage(cvtCvMat2QImage(cv_ptr->image));
    logging.insertRows(0,1);
    std::stringstream logging_msg;
    logging_msg << "[ INFO] [" << ros::Time::now() << "]: I heard: " << "camera";
    QVariant new_row(QString(logging_msg.str().c_str()));
    logging.setData(logging.index(0),new_row);
    if(!t)
    {
    if(r && !s)
{
    if(cam5)
    {


    Q_EMIT Update_Image5(&px5);
        }
        else {
        cam5=0;


    }
    }
    else {r=0;s=0;cam5=0;}
    }

}
/************************************************/

void MainWindow::edgeImage()
{
  /* QString FileName="/home/devendra/Downloads/bug.mp4";
   //IplImage* image =cvLoadImage(FileName.toLocal8Bit().data());
IplImage* image =cvLoadImage("/home/devendra/Downloads/bug.mp4");
IplImage* Gray = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1 );
cvCvtColor(image, Gray, CV_RGB2GRAY);
IplImage* canny= cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1 );
cvCanny(Gray,canny,50,150,3);
QImage imgCanny = QImage((const unsigned char*)canny->imageData,canny->width,canny->height,QImage::Format_Indexed8);
imgCanny.setPixel(0,0,qRgb(0,0,0));
ui.label_can->setPixmap(QPixmap::fromImage(imgCanny).scaled(ui.label_can->size()));*/
}
