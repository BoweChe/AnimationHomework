#include "Curve.h"

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
    this->curve_pos = {
        { 0.0, 8.5, -2.0 },
        { -3.0, 11.0, 2.3 },
        { -6.0, 8.5, -2.5 },
        { -4.0, 5.5, 2.8 },
        { 1.0, 2.0, -4.0 },
        { 4.0, 2.0, 3.0 },
        { 7.0, 8.0, -2.0 },
        { 3.0, 10.0, 3.7 },
        { 0.0, 8.5, -2.0 },
        { -3.0, 11.0, 2.3 },
        { -6.0, 8.5, -2.5 }
    };
    
}

void Curve::calculate_curve()
{
    
    
    /*
	this->curve_points_pos = {
        //这里是线的坐标，只要修改这里就可以了
		{ 0.0, 8.5, -2.0 },
        //{ -1.5, 12, 0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
     */
    //curve_points_pos.insert(curve_points_pos.end(),{ -3.0, 11.0, 2.3 });
    float resolution = 0.005;
    for(int i=3;i<11;i++){
        glm::vec3 P0= curve_pos[i-3];
        glm::vec3 P1= curve_pos[i-2];
        glm::vec3 P2= curve_pos[i-1];
        glm::vec3 P3= curve_pos[i];
        for(int i=0;i<200;i++){
            float t=i*resolution;
            glm::vec3 c0 = P1;
            glm::vec3 c1 = (P2-P0)*0.5f;
            glm::vec3 c2 = (P2-P1)*3.0f-(P3-P1)*0.5f-(P2-P0)*2.0f*0.5f;
            glm::vec3 c3 = -2.0f*(P2-P1)+(P3-P1)*0.5f+(P2-P0)*0.5f;
            glm::vec3 pos = c3*t*t*t+c2*t*t+c1*t+c0;
            curve_points_pos.insert(curve_points_pos.end(),pos);
        }
        
    }
    //std::cout<<curve_points_pos.size();
}
