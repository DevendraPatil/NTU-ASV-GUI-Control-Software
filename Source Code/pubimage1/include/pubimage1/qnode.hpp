/**
 * @file /eros_qtalker/include/eros_qtalker/qnode.hpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef NODE_HPP_
#define NODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/Float64.h>



#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
Q_OBJECT

public:
	QNode(int argc, char** argv, const std::string &name );
	virtual ~QNode();

	bool on_init();
	bool on_init(const std::string &master_url, const std::string &host_url);
	void shutdown();
	//virtual void run() = 0;
        void run();
	void myCallback(const std_msgs::Float64& message_holder);
	void myCallbackgps(const std_msgs::Float64& message_holder);//GPS
	void myCallbackimu(const std_msgs::Float64& message_holder);//IMU
       void subimage();
       	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };
	QStringListModel* loggingModel() { return &logging; }
	QStringListModel* loggingModel2() { return &logging_model2; }
	QStringListModel* loggingModel1() { return &logging_model1; }//subscriber
        QStringListModel* loggingModelgps() { return &logging_modelgps; }//GPS Subscriber
        QStringListModel* loggingModelimu() { return &logging_modelimu; }//IMU Subscriber
	void log( const LogLevel &level, const std::string &msg);
	void log( const LogLevel &level, const std_msgs::Float64 &msg); //subscriber
	void loggps( const LogLevel &level, const std_msgs::Float64 &msg); //GPS subscriber
	void logimu( const LogLevel &level, const std_msgs::Float64 &msg); //GPS subscriber
	QPixmap PixmapModel (){return px;} //camera
	QPixmap PixmapModel1 (){return px1;}//video
	QPixmap PixmapModel2 (){return px2;} //camera2
	QPixmap PixmapModel3 (){return px3;} //camera3
	QPixmap PixmapModel4 (){return px4;} //camera4
	QPixmap PixmapModel5 (){return px5;} //camera5
	QPixmap PixmapModel6(){return px6;} //video live
	const std::string& nodeName() { return node_name; }
	
Q_SIGNALS:
	void loggingUpdated();
	void rosShutdown();

	void Update_Image(const QPixmap* image);
	void Update_Image1(const QPixmap* image1);//video
	void Update_Image2(const QPixmap* image2);//camera2
	void Update_Image3(const QPixmap* image3);//camera3
	void Update_Image4(const QPixmap* image4);//camera4
	void Update_Image5(const QPixmap* image5);//camera5
        void Update_Image6(const QPixmap* image6);//camera5
	
protected:
 
	 //void ros_comms_init() ;
	//virtual void ros_comms_init1()=0;
        image_transport::Subscriber image_sub_;
	image_transport::Subscriber image_sub_1;//video
	image_transport::Subscriber image_sub_2;//camera2
	image_transport::Subscriber image_sub_3;//camera3
	image_transport::Subscriber image_sub_4;//camera4
	image_transport::Subscriber image_sub_5;//camera5
	image_transport::Subscriber image_sub_6;//video live
//	void chatterCallback(const std_msgs::String::ConstPtr &msg);
	void chatterCallback(const sensor_msgs::ImageConstPtr& msg);
	void chatterCallback1(const sensor_msgs::ImageConstPtr& msg1);//video
	void chatterCallback2(const sensor_msgs::ImageConstPtr& msg2);//camera2
	void chatterCallback3(const sensor_msgs::ImageConstPtr& msg3);//camera3
	void chatterCallback4(const sensor_msgs::ImageConstPtr& msg4);//camera4
	void chatterCallback5(const sensor_msgs::ImageConstPtr& msg5);//camera5
	void chatterCallback6(const sensor_msgs::ImageConstPtr& msg6);//live feed
	QImage cvtCvMat2QImage(const cv::Mat & image);
	QImage cvtCvMat2QImage1(const cv::Mat & image);//video
	QImage cvtCvMat2QImage2(const cv::Mat & image);//camera2
	QImage cvtCvMat2QImage3(const cv::Mat & image);//camera3
	QImage cvtCvMat2QImage4(const cv::Mat & image);//camera4
	QImage cvtCvMat2QImage5(const cv::Mat & image);//camera5
	QImage cvtCvMat2QImage6(const cv::Mat & image);//video live
	//ros::Subscriber chatter_subscriber;
	//void subimage()=0;
	int init_argc;
	char** init_argv;
    	QStringListModel logging;
	ros::Publisher chatter_publisher;
	ros::Subscriber chatter_subscriber;
	ros::Subscriber chatter_subscriber_gps;//GPS
	ros::Subscriber chatter_subscriber_imu;//GPS
   	 QStringListModel logging_model2;
    	QStringListModel logging_model1;//subscriber
    	QStringListModel logging_modelgps;//GPS subscriber
    	QStringListModel logging_modelimu;//IMU subscriber
    	QPixmap px;//camera
	QPixmap px1; //video
    	QPixmap px2;//camera2
    	QPixmap px3;//camera3
    	QPixmap px4;//camera4
    	QPixmap px5;//camera5
	QPixmap px6;//video live
    	const std::string node_name;
};


#endif /* NODE_HPP_ */
