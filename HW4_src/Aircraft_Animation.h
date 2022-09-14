#pragma once

#include <vector>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Curve.h"

class Aircraft_Animation
{

public:
	float total_moving_time = 10;
	float t1 = 0.1;
	float t2 = 0.7;
    float start_time = 0;
    int i=0;
    std::vector<float> table1;
    std::vector<float> table2;
    std::vector<glm::vec3> plane_pos;
    std::vector<int> position_index;
    

private:
	glm::mat4 m_model_mat;
	Curve* m_animation_curve = nullptr;

public:
	Aircraft_Animation();
	~Aircraft_Animation();

	void init();
	void init(Curve* animation_curve);
    void make_table();
    void clear_table();
    glm::mat4 getAirquaternion(glm::mat4 model_mat);
    glm::mat4 rotateM(glm::mat4 model_mat,glm::quat z);

	void update(float delta_time);

	void reset();
	//glm::mat4 get_model_mat(glm::mat4 m_model_mat);
    glm::mat4 get_model_mat(){return m_model_mat;};
    //return i function
};

