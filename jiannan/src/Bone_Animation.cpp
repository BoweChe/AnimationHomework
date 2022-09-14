#include "Bone_Animation.h"



Bone_Animation::Bone_Animation()
{
    
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
    object_position = {3.0f,8.0f,3.0f};

	scale_vector =
	{
		{1.0f,1.0f,1.0f},
		{0.5f,4.0f,0.5f},
		{0.5f,3.0f,0.5f},
		{0.5f,2.0f,0.5f}
	};

	rotation_degree_vector = 
	{
		{20.0f,10.0f,30.0f},
		{10.0f,10.0f,30.0f},
		{30.0f,10.0f,30.0f}
	};
    
    delta_angle =
    {
        {.5f,.0f,.0f},
        {.0f,.0f,.0f},
        {.0f,.0f,.0f}
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
    delta_angle =
    {
        {.0f,.0f,.0f},
        {.0f,.0f,.0f},
        {.0f,.0f,.0f}
    };
    glm::vec3 endposition;
    glm::mat4 tp_Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    
    endposition[0] = tp_Turquoise_bone_obj_mat[3][0];
    endposition[1] = tp_Turquoise_bone_obj_mat[3][1];
    endposition[2] = tp_Turquoise_bone_obj_mat[3][2];
    glm::vec3 distance_between_ge = object_position-endposition;
    
    float distance = sqrt(distance_between_ge[0]*distance_between_ge[0]+distance_between_ge[1]*distance_between_ge[1]+distance_between_ge[2]*distance_between_ge[2]);
    Eigen::MatrixXf jacobian = get_jacobian();
    anglesVector = jacobian.transpose()*goalVector;
    anglesVector = anglesVector*alpha;
    glm::mat3 ttest = test_a(anglesVector);
    //std::cout <<double(ttest[0][0])<< std::endl;
    //std::cout <<delta_angle[0][0]<< std::endl;
    
    
    delta_angle[0][0] = ttest[0][0]+delta_angle[0][0];
    std::cout <<delta_angle[0][0]<< std::endl;
    //float t = 0.0f;
    
    rotation_degree_vector[0][0] = rotation_degree_vector[0][0]/1000000.0f+delta_angle[0][0];
    //t = ttest[0][0]+t;
    std::cout <<rotation_degree_vector[0][0]<< std::endl;
    
    //std::cout <<rotation_degree_vector[0][0]<< std::endl;
    //std::cout <<delta_angle[0][2]<< std::endl;
    
    //delta_angle[0][2] = int(anglesVector(0,0))+delta_angle[0][2];
    //std::cout << std::setprecision(5)<< anglesVector(0,0)<< std::endl;
    //std::cout <<(delta_angle[0][0]<-10000.0f)<< std::endl;
    //std::cout << std::setprecision(5)<< delta_angle[0][2]<< std::endl;
  
    //std::cout <<delta_angle[0][2]<< std::endl;
    //std::cout <<anglesVector(0,0)<< std::endl;
    if(distance>0.01){
        //rotation_degree_vector[0][2] = rotation_degree_vector[0][2]+anglesVector(0,0);
        /*
        rotation_degree_vector[0][0] += anglesVector(6,0);
        
        rotation_degree_vector[0][1] += anglesVector(3,0);
        rotation_degree_vector[0][2] += anglesVector(0,0);
        
        rotation_degree_vector[1][0] += anglesVector(7,0);
        rotation_degree_vector[1][1] += anglesVector(4,0);
        rotation_degree_vector[1][2] += anglesVector(1,0);
        
        rotation_degree_vector[2][0] += anglesVector(8,0);
        rotation_degree_vector[2][1] += anglesVector(5,0);
        rotation_degree_vector[2][2] += anglesVector(2,0);
        
        rotation_degree_vector[0][0] += 1.0f;
        
        rotation_degree_vector[0][1] += 1.0f;
        rotation_degree_vector[0][2] += 1.0f;
        
        rotation_degree_vector[1][0] += 1.0f;
        rotation_degree_vector[1][1] += 1.0f;
        rotation_degree_vector[1][2] += 1.0f;
        
        rotation_degree_vector[2][0] += 1.0f;
        rotation_degree_vector[2][1] += 1.0f;
        rotation_degree_vector[2][2] += 1.0f;
         */

    }
}

void Bone_Animation::setvalue(float temp1){
    std::cout <<temp1<< std::endl;
    float temp2 = rotation_degree_vector[0][2];
    std::cout <<&temp1<< std::endl;
    //rotation_degree_vector[0][2] = *&temp1;
}

float Bone_Animation::delta_theta(float temp1,float temp2){
    temp1 = temp1+temp2;
    std::cout<<temp1+temp2<<std::endl;
    return temp1;
    
}

glm::mat3 Bone_Animation::test_a(Eigen::MatrixXf anglesVector){
    glm::mat3 ttest = glm::mat3(0.0f);
    ttest[0][0] = anglesVector(6,0);
    
    ttest[0][1] = anglesVector(3,0);
    ttest[0][2] = anglesVector(0,0);
    
    ttest[1][0] = anglesVector(7,0);
    ttest[1][1] = anglesVector(4,0);
    ttest[1][2] = anglesVector(1,0);
    
    ttest[2][0] = anglesVector(8,0);
    ttest[2][1] = anglesVector(5,0);
    ttest[2][2] = anglesVector(2,0);
    return ttest;
}
glm::mat4 Bone_Animation::Yellow_Bone(){
    Yellow_bone_obj_mat = glm::mat4(1.0f);
    Yellow_bone_obj_mat = glm::translate(Yellow_bone_obj_mat,glm::vec3(2.0f,1.5f,2.0f));
    Yellow_bone_obj_mat = get_model_mat(Yellow_bone_obj_mat,0);
    Yellow_bone_obj_mat = glm::translate(Yellow_bone_obj_mat,glm::vec3(0.0f,2.0f,0.0f));
    Yellow_bone_obj_mat = glm::scale(Yellow_bone_obj_mat,scale_vector[1]);
    //std::cout<<Yellow_bone_obj_mat[3][1]<<std::endl;
    return Yellow_bone_obj_mat;
}
glm::mat4 Bone_Animation::Pink_Bone(glm::mat4 Yellow_bone_obj_mat){
    Pink_bone_obj_mat = glm::mat4(1.0f);
    Pink_bone_obj_mat = glm::translate(Pink_bone_obj_mat,glm::vec3(0.0f,2.0f,0.0f));
    Pink_bone_obj_mat = get_model_mat(Pink_bone_obj_mat,1);
    Pink_bone_obj_mat = combine_matrix1(Yellow_bone_obj_mat,Pink_bone_obj_mat);
    //Pink_bone_obj_mat = m_bone_animation->get_model_mat(Pink_bone_obj_mat,2);
    Pink_bone_obj_mat = glm::translate(Pink_bone_obj_mat,glm::vec3(0.0f,1.5f,0.0f));
    Pink_bone_obj_mat = glm::scale(Pink_bone_obj_mat,scale_vector[2]);
    return Pink_bone_obj_mat;
    
}

glm::mat4 Bone_Animation::Turquoise_Bone(glm::mat4 Pink_bone_obj_mat){
    Turquoise_bone_obj_mat = glm::mat4(1.0f);
    Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,1.5f,0.0f));
    Turquoise_bone_obj_mat = get_model_mat(Turquoise_bone_obj_mat,2);
    Turquoise_bone_obj_mat = combine_matrix2(Pink_bone_obj_mat,Turquoise_bone_obj_mat);
    Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,1.0f,0.0f));
    Turquoise_bone_obj_mat = glm::scale(Turquoise_bone_obj_mat,scale_vector[3]);
    return Turquoise_bone_obj_mat;
    //顶点还要再加上（0.0f,1.5f,0.0f)
}
Eigen::MatrixXf Bone_Animation::get_jacobian(){
    
    Eigen::MatrixXf jacobian = Eigen::MatrixXf::Zero(3, 9);
    //world_matrix
    glm::mat4 Wrold_Red_bone_obj_mat = glm::translate(Red_bone_obj_mat,root_position);
    Wrold_Red_bone_obj_mat = glm::translate(Wrold_Red_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    glm::mat4 tp_Yellow_bone_obj_mat = glm::translate(Yellow_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    glm::mat4 tp_Pink_bone_obj_mat = glm::translate(Pink_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    glm::mat4 tp_Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    
    glm::vec3 test = glm::vec3(tp_Turquoise_bone_obj_mat[3]);
    
    glm::vec4 End_for_Yellow = tp_Turquoise_bone_obj_mat[3]-Wrold_Red_bone_obj_mat[3];
    glm::vec4 End_for_Pink = tp_Turquoise_bone_obj_mat[3]-tp_Yellow_bone_obj_mat[3];
    glm::vec4 End_for_blue = tp_Turquoise_bone_obj_mat[3]-tp_Pink_bone_obj_mat[3];
    
    glm::vec3 v1 = glm::cross(glm::normalize(glm::vec3(tp_Yellow_bone_obj_mat[2])),glm::vec3(End_for_Yellow));
    glm::vec3 v2 = glm::cross(glm::normalize(glm::vec3(tp_Pink_bone_obj_mat[2])),glm::vec3(End_for_Pink));
    glm::vec3 v3 = glm::cross(glm::normalize(glm::vec3(tp_Turquoise_bone_obj_mat[2])),glm::vec3(End_for_blue));
    
    glm::vec3 v4 = glm::cross(glm::normalize(glm::vec3(tp_Yellow_bone_obj_mat[1])),glm::vec3(End_for_Yellow));
    glm::vec3 v5 = glm::cross(glm::normalize(glm::vec3(tp_Pink_bone_obj_mat[1])),glm::vec3(End_for_Pink));
    glm::vec3 v6 = glm::cross(glm::normalize(glm::vec3(tp_Turquoise_bone_obj_mat[1])),glm::vec3(End_for_blue));
    
    glm::vec3 v7 = glm::cross(glm::normalize(glm::vec3(tp_Yellow_bone_obj_mat[0])),glm::vec3(End_for_Yellow));
    glm::vec3 v8 = glm::cross(glm::normalize(glm::vec3(tp_Pink_bone_obj_mat[0])),glm::vec3(End_for_Pink));
    glm::vec3 v9 = glm::cross(glm::normalize(glm::vec3(tp_Turquoise_bone_obj_mat[0])),glm::vec3(End_for_blue));
    
    glm::vec3 goal = glm::vec3(object_position-glm::vec3(tp_Turquoise_bone_obj_mat[3]));
    goalVector << goal.x,
                  goal.y,
                  goal.z;
    jacobian <<
        v1.x, v2.x, v3.x, v4.x, v5.x, v6.x, v7.x, v8.x, v9.x,
        v1.y, v2.y, v3.y, v4.y, v5.y, v6.y, v7.y, v8.y, v9.y,
        v1.z, v2.z, v3.z, v4.z, v5.z, v6.z, v7.z, v8.z, v9.z;
    
    return jacobian;
}

glm::mat4 Bone_Animation::get_model_mat(glm::mat4 m_model_mat,int t){
    float pi = 3.14f;
    //m_model_mat = glm::translate(m_model_mat,glm::vec3(-2.0,-3.5,-2.0));
    float xtheta = rotation_degree_vector[t][0];
    float ytheta = rotation_degree_vector[t][1];
    float ztheta = rotation_degree_vector[t][2];
    m_model_mat = glm::rotate(m_model_mat,glm::radians(xtheta),glm::vec3(1.0f,0.0f,0.0f));
    m_model_mat = glm::rotate(m_model_mat,glm::radians(ztheta),glm::vec3(0.0f,0.0f,1.0f));
    m_model_mat = glm::rotate(m_model_mat,glm::radians(ytheta),glm::vec3(0.0f,1.0f,0.0f));
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
    first_model_mat = glm::scale(first_model_mat,glm::vec3(2.0f,0.333333f,2.0f));
    test = first_model_mat*second_model_mat;
    return test;
    
}
void Bone_Animation::reset()
{
}

