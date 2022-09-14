#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Eigen/Dense>
//#include <math.h>
using namespace std;
class Bone_Animation
{
public:
	Bone_Animation();
	~Bone_Animation();

	void init();
	void update(float delta_time);
	void reset();
    glm::mat4 Turquoise_Bone(glm::mat4 Pink_bone_obj_mat);
    glm::mat4 Pink_Bone(glm::mat4 Yellow_bone_obj_mat);
    glm::mat4 Yellow_Bone();
    float alpha = 0.1f;
    float t = 0.1f;
    //float t2;
    int i=1;
    std::vector<glm::vec3> delta_angle;

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;
	std::vector<glm::vec4> colors;
    //std::vector<glm::vec3> delta_angle;
    glm::vec3 root_position;
    glm::vec3 yellow_position;
    glm::vec3 pink_position;
    glm::vec3 turquoise_position;
    glm::vec3 object_position;
    glm::mat4 Turquoise_bone_obj_mat;
    glm::mat4 Pink_bone_obj_mat;
    glm::mat4 Yellow_bone_obj_mat;
    glm::mat4 Red_bone_obj_mat = glm::mat4(1.0f);
    //glm::mat4 get_model_mat(){return m_model_mat;};
    glm::mat4 get_model_mat(glm::mat4 m_model_mat,int t);
    glm::mat4 combine_matrix1(glm::mat4 first_model_mat,glm::mat4 second_model_mat);
    glm::mat4 combine_matrix2(glm::mat4 first_model_mat,glm::mat4 second_model_mat);
    
    //Eigen::MatrixXf jacobian = Eigen::MatrixXf::Zero(3, 9);
    Eigen::MatrixXf anglesVector = Eigen::MatrixXf::Zero(9, 1);
    //glm::mat3 anglesVector = glm::mat3(0.0f);
    Eigen::MatrixXf goalVector = Eigen::MatrixXf::Zero(3, 1);
    glm::mat3 test_a(Eigen::MatrixXf anglesVector);
    void setvalue(float temp1);
    
    float delta_theta(float temp1,float temp2);
    Eigen::MatrixXf get_jacobian();

};

