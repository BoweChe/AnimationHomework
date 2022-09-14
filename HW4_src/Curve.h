#pragma once
#include <vector>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class Curve
{
public:
	Curve();
	~Curve();
	
	void init();
	void calculate_curve();
    glm::mat4 calculate_quaternion(glm::mat4 model_mat,int j);
    glm::mat3 quaternion_matrix;
    void transpose();
    //glm::mat4 calculate_quaternion();
	
public:
	float tau = 0.5; // Coefficient for catmull-rom spline
	int num_points_per_segment = 200;

	std::vector<glm::vec3> control_points_pos;
	std::vector<glm::vec3> curve_points_pos;
    std::vector<glm::vec3> curve_pos;
    std::vector<glm::quat> control_points_quaternion;
    std::vector<glm::vec3> test_cube_points_pos;
    
};
