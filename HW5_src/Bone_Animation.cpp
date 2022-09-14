#include "Bone_Animation.h"



Bone_Animation::Bone_Animation()
{
    //this->m_model_mat = glm::mat4(1.0f);
}


Bone_Animation::~Bone_Animation()
{
}

void Bone_Animation::init()
{
	root_position = { 2.0f,1.0f,2.0f };
    yellow_position = {2.0f,3.5f,2.0f};
    pink_position = {2.0f,7.0f,2.0f};
    turquoise_position = {2.0f,9.5f,2.0f};

	scale_vector =
	{
		{1.0f,1.0f,1.0f},
		{0.5f,4.0f,0.5f},
		{0.5f,3.0f,0.5f},
		{0.5f,2.0f,0.5f}
	};

	rotation_degree_vector = 
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	colors = 
	{
		{0.7f,0.0f,0.0f,1.0f},
		{0.7f,0.7f,0.0f,1.0f},
		{0.7f,0.0f,0.7f,1.0f},
		{0.0f,0.7f,0.7f,1.0f}
	};

}

void Bone_Animation::update(float delta_time)
{
    //std::cout<<rotation_degree_vector[1][0]<<std::endl;
    
}

glm::mat4 Bone_Animation::get_model_mat(glm::mat4 m_model_mat,int t){
    float pi = 3.14f;
    //m_model_mat = glm::translate(m_model_mat,glm::vec3(-2.0,-3.5,-2.0));
    float xtheta = rotation_degree_vector[t][0]*pi/180.0;
    float ytheta = rotation_degree_vector[t][1]*pi/180.0;
    float ztheta = rotation_degree_vector[t][2]*pi/180.0;
    //m_model_mat[0][0] = 0.5;
    m_model_mat[0][0] = cos(ztheta)*cos(ytheta);
    m_model_mat[0][1] = cos(ztheta)*sin(ytheta)*sin(xtheta)-sin(ztheta)*cos(xtheta);
    m_model_mat[0][2] = cos(ztheta)*sin(ytheta)*cos(xtheta)+sin(ztheta)*sin(xtheta);
    m_model_mat[1][0] = sin(ztheta)*cos(ytheta);
    m_model_mat[1][1] = sin(ztheta)*sin(ytheta)*sin(xtheta)+cos(ztheta)*cos(xtheta);
    m_model_mat[1][2] = sin(ztheta)*sin(ytheta)*cos(xtheta)-cos(ztheta)*sin(xtheta);
    m_model_mat[2][0] = -sin(ytheta);
    m_model_mat[2][1] = cos(ytheta)*sin(xtheta);
    m_model_mat[2][2] = cos(ytheta)*cos(xtheta);
    //m_model_mat = glm::translate(m_model_mat,glm::vec3(2.0,1.5,2.0));
    return m_model_mat;
    
}
glm::mat4 Bone_Animation::combine_matrix1(glm::mat4 first_model_mat,glm::mat4 second_model_mat){
    glm::mat4 test = glm::mat4(0.0f);
    first_model_mat = glm::scale(first_model_mat,glm::vec3(2.0f,0.25f,2.0f));
    test = first_model_mat*second_model_mat;
    return test;
    
}
glm::mat4 Bone_Animation::combine_matrix2(glm::mat4 first_model_mat,glm::mat4 second_model_mat){
    glm::mat4 test = glm::mat4(0.0f);
    first_model_mat = glm::scale(first_model_mat,glm::vec3(2.0f,0.333f,2.0f));
    test = first_model_mat*second_model_mat;
    return test;
    
}

void Bone_Animation::reset()
{
}

