#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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
    //glm::mat4 m_model_mat;

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;
	std::vector<glm::vec4> colors;

	glm::vec3 root_position;
    glm::vec3 yellow_position;
    glm::vec3 pink_position;
    glm::vec3 turquoise_position;
    //glm::mat4 get_model_mat(){return m_model_mat;};
    glm::mat4 get_model_mat(glm::mat4 m_model_mat,int t);
    
    glm::mat4 combine_matrix1(glm::mat4 first_model_mat,glm::mat4 second_model_mat);
    glm::mat4 combine_matrix2(glm::mat4 first_model_mat,glm::mat4 second_model_mat);
    
    

};

