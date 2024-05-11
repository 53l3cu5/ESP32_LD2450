#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

struct Position {
  int16_t x; 
  int16_t y;
  int speed;
  int16_t distance_resolution;
  bool valide;
  bool zone_ex_enter = false;
  float angle = 0;
  std::basic_string<char> position = "Static";
  std::basic_string<char> direction = "None";
};
struct Zone {
  int16_t x;
  int16_t y;
  int16_t height;
  int16_t width;
  int16_t target_count = 0;
  int16_t outside_target_count = 0;
  bool has_target = false;
  bool has_target_outside = false;
  
  // template_::TemplateTextSensor* tips_conf;
  // std::string name = "Zone";
};

struct Pxy {
  int16_t x; 
  int16_t y;
};


float toRadians(float degrees){
    return degrees * M_PI / 180.0;
}

// Définition de la fonction pour vérifier les cibles dans une zone donnée
bool check_targets_in_zone(struct Zone &z, struct Position &t, float angle) {
  struct Pxy p1, p2, p3, p4;
  float d12, d14, d15, d23, d25, d34, d35, d45; 
  float a152, a154, a253, a354, a_sum;
  float TAU = 2 * M_PI;//6.283185; // 2*PI
  bool isInside = false;
  
  p1.x = z.x;
  p1.y = z.y;
  p2.x = z.x - z.width * cos(toRadians(angle));
  p2.y = z.y + z.width * sin(toRadians(angle));
  p3.x = z.x - z.width * cos(toRadians(angle)) + z.height * cos(toRadians(angle - 90));
  p3.y = z.y + z.width * sin(toRadians(angle)) + z.height * sin(toRadians(angle + 90));
  p4.x = z.x + z.height * cos(toRadians(angle - 90));;
  p4.y = z.y + z.height * sin(toRadians(angle + 90));;
  
  d15 = sqrt(pow(p1.x-t.x,2)+pow(p1.y-t.y,2));
  d25 = sqrt(pow(p2.x-t.x,2)+pow(p2.y-t.y,2));
  d35 = sqrt(pow(p3.x-t.x,2)+pow(p3.y-t.y,2));
  d45 = sqrt(pow(p4.x-t.x,2)+pow(p4.y-t.y,2));
  d12 = sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
  d14 = sqrt(pow(p1.x-p4.x,2)+pow(p1.y-p4.y,2));
  d23 = sqrt(pow(p2.x-p3.x,2)+pow(p2.y-p3.y,2));
  d34 = sqrt(pow(p3.x-p4.x,2)+pow(p3.y-p4.y,2));
  
  a152 = acos((pow(d15,2)+pow(d25,2)-pow(d12,2))/(2*d15*d25));
  a154 = acos((pow(d15,2)+pow(d45,2)-pow(d14,2))/(2*d15*d45));
  a253 = acos((pow(d25,2)+pow(d35,2)-pow(d23,2))/(2*d25*d35));
  a354 = acos((pow(d35,2)+pow(d45,2)-pow(d34,2))/(2*d35*d45));
  a_sum = a152+a154+a253+a354;
  
  if (a_sum>=TAU) {
    isInside = true;
  }
  return isInside;
}

bool to_bool(std::basic_string<char> str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

void check_zone_valid(int x, int y, int width, int height, template_::TemplateTextSensor* tips_conf){
    if (x == 0 && width == 0 && y == 0 && height == 0){
        tips_conf->publish_state("Configure below");
        return;
    }

    char combined[80]; 
    sprintf(combined, "Curr Size: %d x %d", width, height);
    tips_conf->publish_state(combined);
}

void check_zout_valid(int z, template_::TemplateTextSensor* tips_conf){
    char combined[40]; 
    sprintf(combined, "Zone Exclusion %d", z);
    tips_conf->publish_state(combined);
}
