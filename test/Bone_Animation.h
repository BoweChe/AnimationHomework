#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Shader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

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
    glm::mat3 Jacobian_matrix();
    //glm::mat4 m_model_mat;
    int i = 0;

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;
	std::vector<glm::vec4> colors;

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
    float crossproduct(glm::vec4 tempv1, glm::vec4 tempv2);
    glm::vec4 four_Times_two_matrix(glm::mat4 temp1,glm::vec4 temp2);
    float delta_theta(glm::mat3 jacobian);
    glm::mat3 transpose(glm::mat3 jacobian);
    glm::vec3 three_times_three_vec(glm::mat3 jacobian,glm::vec3 distance);
    glm::mat4 combine_matrix1(glm::mat4 first_model_mat,glm::mat4 second_model_mat);
    glm::mat4 combine_matrix2(glm::mat4 first_model_mat,glm::mat4 second_model_mat);
    
    

};

