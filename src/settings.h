#pragma once
#include <string>

namespace settings
{

const float screen_width = 1216;
const float screen_height = 800;
const std::string caption = "rpg";
const sf::Color bg_col = sf::Color(240, 240, 240, 255);
const int fps = 60;

//luni settings
//const Vector2 startpos = {0,0};
const int luni_width = 30;
const int luni_height = 38;
const float scale = 1;
const int animation_stop_frames = 5;
const int startcenterx = 400;
const float max_speed = 5;
const float floor_y = 600;
const float g = 1.1;
const float jump_vel = 20;
const float x_acceleration = 0.8;

//arrow settings
const int arrow_start_speed = 5;
const int arrow_acceleration = 2;
const int arrow_speed_cap = 60;

}