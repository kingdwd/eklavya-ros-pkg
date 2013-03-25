#include <iostream>

#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "diagnostics.h"
#include "../../eklavya2.h"

namespace diagnostics_space {
  void diagnostics_space::Diagnostics::plotMap() {
    for (int i = 0; i < MAP_MAX; i++) {
      uchar* ptr = (uchar *)(map_image->imageData + i * map_image->widthStep);
      for (int j = 0; j < MAP_MAX; j++) {
        if (global_map[j][MAP_MAX - i - 1] > 0) {
          ptr[3 * j] = 0;
          ptr[3 * j + 1] = 0;
          ptr[3 * j + 2] = 0;
        } else {
          ptr[3 * j] = 200;
          ptr[3 * j + 1] = 200;
          ptr[3 * j + 2] = 200;
        }
      }
    }
    
    cvShowImage("Diag Map", map_image);
    cvWaitKey(1);
  }
  
  void diagnostics_space::Diagnostics::printPose() {
    cout << "[DIAG] [POSE] [POSITION] : (" << 
            pose.position.x << ", " <<
            pose.position.y << ", " << 
            pose.position.z << ") " <<
            "[ORIENTATION] : (" << 
            pose.orientation.x << ", " << 
            pose.orientation.y << ", " <<
            pose.orientation.z << ")" << endl;
  }
  
  void diagnostics_space::Diagnostics::printLatLong() {
    cout << "[DIAG] [LATLNG] : " << lat_long.latitude << ", " << lat_long.longitude << endl;
  }
  
  void diagnostics_space::Diagnostics::printOdom() {
    cout << "[DIAG] [ODOM] : " << odom.left_velocity << ", " << odom.right_velocity << endl;
  }
  
  void diagnostics_space::Diagnostics::printBotLocation() {
    cout << "[DIAG] [BOT] : (" << 
            bot_location.x << ", " <<
            bot_location.y << ", " <<
            bot_location.z << ")" << endl;
  }

  void diagnostics_space::Diagnostics::printTargetLocation() {
    cout << "[DIAG] [TARGET] : (" << 
            target_location.x << ", " <<
            target_location.y << ", " <<
            target_location.z << ")" << endl;
  }

  void diagnostics_space::Diagnostics::plotPath(vector<Triplet> my_path) {
    cvSetZero(path_image);
    
    for(int i = 0; i < (int) my_path.size() - 1; i++) {
      int x = (int) my_path[i].x;
      int y = MAP_MAX - (int) my_path[i].y - 1;

      int x1 = (int) my_path[i + 1].x;
      int y1 = MAP_MAX - (int) my_path[i + 1].y - 1;
      
      srand(i + time(0));
      
      cvLine(path_image, cvPoint(x, y), cvPoint(x1, y1), CV_RGB(rand() % 255, rand() % 255, rand() % 255), 2, CV_AA, 0);
    }
    
    cvShowImage("[DIAG] Path", path_image);
    cvWaitKey(1);
  }
}
