#include "Bone_Animation.h"



Bone_Animation::Bone_Animation()
{
    //this->m_model_mat = glm::mat4(1.0f);
    //this->Yellow_bone_obj_mat = glm::mat4(1.0f);
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

	rotation_degree_vector = //把这个改成3*3！
	{
		{20.0f,30.0f,30.0f},
		{10.0f,5.0f,30.0f},
		{40.0f,50.0f,30.0f}
	};

	colors = 
	{
		{0.7f,0.0f,0.0f,1.0f},
		{0.7f,0.7f,0.0f,1.0f},
		{0.7f,0.0f,0.7f,1.0f},
		{0.0f,0.7f,0.7f,1.0f}
	};
    //Yellow_Bone();
    //Yellow_bone_obj_mat = glm::mat4(1.0f);
    Jacobian_matrix();

}

void Bone_Animation::update(float delta_time)
{
    //如果tur和g的距离大于一个值，就更新这里。
    //Yellow_Bone();
    //std::cout<<Turquoise_bone_obj_mat[3][1]<<std::endl;
    glm::vec3 endposition;
    glm::mat4 tp_Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    
    endposition[0] = tp_Turquoise_bone_obj_mat[3][0];
    endposition[1] = tp_Turquoise_bone_obj_mat[3][1];
    endposition[2] = tp_Turquoise_bone_obj_mat[3][2];
    glm::vec3 distance_between_ge = object_position-endposition;
    
    float distance = sqrt(distance_between_ge[0]*distance_between_ge[0]+distance_between_ge[1]*distance_between_ge[1]+distance_between_ge[2]*distance_between_ge[2]);
    //std::cout<<distance<<std::endl;
    float origiendX = distance_between_ge[0];
    float origiendY = distance_between_ge[1];
    float origiendZ = distance_between_ge[2];
    
    Jacobian_matrix();
    
    if(distance<0.01){
        glm::mat3 temp = Jacobian_matrix();
        float alpha = delta_theta(temp);
        glm::mat3 Inverse_jacobian = transpose(temp);
        Inverse_jacobian = 0.1f*Inverse_jacobian;
        rotation_degree_vector[0][1] += Inverse_jacobian[0][1]*origiendY;
        rotation_degree_vector[1][1] += Inverse_jacobian[1][1]*origiendY;
        rotation_degree_vector[2][1] += Inverse_jacobian[2][1]*origiendY;
        //std::cout<<<<std::endl;
        rotation_degree_vector[0][2] += Inverse_jacobian[0][2]*origiendZ;
        rotation_degree_vector[1][2] += Inverse_jacobian[1][2]*origiendZ;
        rotation_degree_vector[2][2] += Inverse_jacobian[2][2]*origiendZ;
        
        rotation_degree_vector[0][0] += Inverse_jacobian[0][0]*origiendX;
        rotation_degree_vector[1][0] += Inverse_jacobian[1][0]*origiendX;
        rotation_degree_vector[2][0] += Inverse_jacobian[2][0]*origiendX;
        //afterendX = tp_Turquoise_bone_obj_mat[3][0]
    }
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


glm::mat4 Bone_Animation::get_model_mat(glm::mat4 m_model_mat,int t){
    float pi = 3.14f;
    //m_model_mat = glm::translate(m_model_mat,glm::vec3(-2.0,-3.5,-2.0));
    float xtheta = rotation_degree_vector[t][0];
    float ytheta = rotation_degree_vector[t][1];
    float ztheta = rotation_degree_vector[t][2];
    
    //glm::mat4 rotate_matrix_X = glm::mat4(1.0f);
    


    //float ytheta = -1.0*rotation_degree_vector[t][1]*pi/180.0;
    //float ztheta = -1.0*rotation_degree_vector[t][2]*pi/180.0;
    //m_model_mat[0][0] = 0.5;
    /*
    m_model_mat[0][0] = cos(ztheta)*cos(ytheta);
    m_model_mat[0][1] = cos(ztheta)*sin(ytheta)*sin(xtheta)-sin(ztheta)*cos(xtheta);
    m_model_mat[0][2] = cos(ztheta)*sin(ytheta)*cos(xtheta)+sin(ztheta)*sin(xtheta);
    m_model_mat[1][0] = sin(ztheta)*cos(ytheta);
    m_model_mat[1][1] = sin(ztheta)*sin(ytheta)*sin(xtheta)+cos(ztheta)*cos(xtheta);
    m_model_mat[1][2] = sin(ztheta)*sin(ytheta)*cos(xtheta)-cos(ztheta)*sin(xtheta);
    m_model_mat[2][0] = -sin(ytheta);
    m_model_mat[2][1] = cos(ytheta)*sin(xtheta);
    m_model_mat[2][2] = cos(ytheta)*cos(xtheta);
    */
    //m_model_mat = glm::rotate(m_model_mat,glm::radians(ytheta),glm::vec3(0.0f,1.0f,0.0f));
    //m_model_mat = glm::rotate(m_model_mat,glm::radians(ztheta),glm::vec3(0.0f,0.0f,1.0f));
    m_model_mat = glm::rotate(m_model_mat,glm::radians(xtheta),glm::vec3(1.0f,0.0f,0.0f));
    m_model_mat = glm::rotate(m_model_mat,glm::radians(ztheta),glm::vec3(0.0f,0.0f,1.0f));
    m_model_mat = glm::rotate(m_model_mat,glm::radians(ytheta),glm::vec3(0.0f,1.0f,0.0f));
    //m_model_mat = glm::translate(m_model_mat,glm::vec3(2.0,1.5,2.0));
    return m_model_mat;
    
}
glm::mat3 Bone_Animation::Jacobian_matrix(){
    //三乘三，第一行yellow，第二行pink，第三行tur，第一列x，第二列y，第三列z
    //把其他两个都像tur一样弄就好了
    //先更新Y，再更新z，最后更新x
    glm::vec4 tp_object_position = glm::vec4(0.0f);
    for(int i=0;i<3;i++){
        tp_object_position[i] = object_position[i];
    }
    //vector
    glm::vec4 world_vec_x = glm::vec4(0.0f);
    world_vec_x[0] = 1.0f;
    glm::vec4 world_vec_y = glm::vec4(0.0f);
    world_vec_y[1] = 1.0f;
    glm::vec4 world_vec_z = glm::vec4(0.0f);
    world_vec_z[2] = 1.0f;
    
    //world matrix
    glm::mat4 Wrold_Red_bone_obj_mat = glm::translate(Red_bone_obj_mat,root_position);
    Wrold_Red_bone_obj_mat = glm::translate(Wrold_Red_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    glm::mat4 tp_Yellow_bone_obj_mat = glm::translate(Yellow_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    glm::mat4 tp_Pink_bone_obj_mat = glm::translate(Pink_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    glm::mat4 tp_Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    //这里对了
    
    //e-g
    glm::mat3 jacobian = glm::mat3(1.0f);
    glm::vec4 dx_forYellow = tp_Turquoise_bone_obj_mat[3]-Wrold_Red_bone_obj_mat[3];//5.5-8 = -2.5
    dx_forYellow[1] = 0.0f;
    dx_forYellow[2] = 0.0f;
    glm::vec4 dy_forYellow = tp_Turquoise_bone_obj_mat[3]-Wrold_Red_bone_obj_mat[3];
    dy_forYellow[0] = 0.0f;
    dy_forYellow[2] = 0.0f;
    glm::vec4 dz_forYellow = tp_Turquoise_bone_obj_mat[3]-Wrold_Red_bone_obj_mat[3];    //
    dz_forYellow[0] = 0.0f;
    dz_forYellow[1] = 0.0f;
    
    glm::vec4 dx_forPink = tp_Turquoise_bone_obj_mat[3]-tp_Yellow_bone_obj_mat[3];
    dx_forPink[1] = 0.0f;
    dx_forPink[2] = 0.0f;
    glm::vec4 dy_forPink = tp_Turquoise_bone_obj_mat[3]-tp_Yellow_bone_obj_mat[3];
    dy_forPink[0] = 0.0f;
    dy_forPink[2] = 0.0f;
    glm::vec4 dz_forPink = tp_Turquoise_bone_obj_mat[3]-tp_Yellow_bone_obj_mat[3];
    dz_forPink[0] = 0.0f;
    dz_forPink[1] = 0.0f;
    
    glm::vec4 dx_forTur = tp_Turquoise_bone_obj_mat[3]-tp_Pink_bone_obj_mat[3];
    dx_forTur[1] = 0.0f;
    dx_forTur[2] = 0.0f;
    glm::vec4 dy_forTur = tp_Turquoise_bone_obj_mat[3]-tp_Pink_bone_obj_mat[3];
    dy_forTur[0] = 0.0f;
    dy_forTur[2] = 0.0f;
    glm::vec4 dz_forTur = tp_Turquoise_bone_obj_mat[3]-tp_Pink_bone_obj_mat[3];
    dz_forTur[0] = 0.0f;
    dz_forTur[1] = 0.0f;
    
    //Rx,Ry,Rz for yellow (Rotation Matrix);
    glm::mat4 Rotate_X_Yellow = glm::mat4(1.0f);
    glm::mat4 Rotate_Y_Yellow = glm::mat4(1.0f);
    glm::mat4 Rotate_Z_Yellow = glm::mat4(1.0f);
    
    float xtheta_Yellow = rotation_degree_vector[0][0];
    float ytheta_Yellow = rotation_degree_vector[0][1];
    float ztheta_Yellow = rotation_degree_vector[0][2];
    
    Rotate_X_Yellow = glm::rotate(Rotate_X_Yellow,glm::radians(xtheta_Yellow),glm::vec3(1.0f,0.0f,0.0f));
    Rotate_Y_Yellow = glm::rotate(Rotate_Y_Yellow,glm::radians(ytheta_Yellow),glm::vec3(0.0f,1.0f,0.0f));
    Rotate_Z_Yellow = glm::rotate(Rotate_Z_Yellow,glm::radians(ztheta_Yellow),glm::vec3(0.0f,0.0f,1.0f));
    
    //Rx,Ry,Rz for pink
    glm::mat4 Rotate_X_Pink = glm::mat4(1.0f);
    glm::mat4 Rotate_Y_Pink = glm::mat4(1.0f);
    glm::mat4 Rotate_Z_Pink = glm::mat4(1.0f);
    
    float xtheta_Pink = rotation_degree_vector[1][0];
    float ytheta_Pink = rotation_degree_vector[1][1];
    float ztheta_Pink = rotation_degree_vector[1][2];
    
    Rotate_X_Pink = glm::rotate(Rotate_X_Pink,glm::radians(xtheta_Pink),glm::vec3(1.0f,0.0f,0.0f));
    Rotate_Y_Pink = glm::rotate(Rotate_Y_Pink,glm::radians(ytheta_Pink),glm::vec3(0.0f,1.0f,0.0f));
    Rotate_Z_Pink = glm::rotate(Rotate_Z_Pink,glm::radians(ztheta_Pink),glm::vec3(0.0f,0.0f,1.0f));
    
    //Rx,Ry,Rz for Turp
    glm::mat4 Rotate_X_Turp = glm::mat4(1.0f);
    glm::mat4 Rotate_Y_Turp = glm::mat4(1.0f);
    glm::mat4 Rotate_Z_Turp = glm::mat4(1.0f);
    
    float xtheta_Turp = rotation_degree_vector[2][0];
    float ytheta_Turp = rotation_degree_vector[2][1];
    float ztheta_Turp = rotation_degree_vector[2][2];
    
    Rotate_X_Turp = glm::rotate(Rotate_X_Turp,glm::radians(xtheta_Turp),glm::vec3(1.0f,0.0f,0.0f));
    Rotate_Y_Turp = glm::rotate(Rotate_Y_Turp,glm::radians(ytheta_Turp),glm::vec3(0.0f,1.0f,0.0f));
    Rotate_Z_Turp = glm::rotate(Rotate_Z_Turp,glm::radians(ztheta_Turp),glm::vec3(0.0f,0.0f,1.0f));
    
    
    //alpha是end point
    //下面计算jacobian matrix
    //glm::vec4 temp = Wrold_Red_bone_obj_mat*world_vec_x;

    glm::vec4 temp = glm::vec4(0.0f);
    //float temt = crossproduct(temp,dx_forYellow);
    //std::cout<<temt<<std::endl;
    //std::cout<<dx_forYellow[0]<<std::endl;
    //Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    for(int i=0;i<4;i++){
        //std::cout<<dx_forYellow[i]<<std::endl;
        //std::cout<<temp[i]<<std::endl;
        //std::cout<<Wrold_Red_bone_obj_mat[3][i]<<std::endl;
    }
    //std::cout<<temp[3]<<std::endl;
    //std::cout<<dx_forYellow[1]<<std::endl;
    /*
    jacobian[0][0] = crossproduct(four_Times_two_matrix(Wrold_Red_bone_obj_mat,world_vec_x),dx_forYellow);
    
    temp = four_Times_two_matrix(Rotate_Z_Yellow,world_vec_y);
    temp = four_Times_two_matrix(Rotate_X_Yellow,temp);
    
    temp = four_Times_two_matrix(Wrold_Red_bone_obj_mat,temp);
    jacobian[1][0] = crossproduct(temp,dy_forYellow);
    
    
    temp = four_Times_two_matrix(Rotate_X_Yellow,world_vec_z);
    temp = four_Times_two_matrix(Wrold_Red_bone_obj_mat,temp);
    jacobian[2][0] = crossproduct(temp,dz_forYellow);//这个有问题
    
    //
    
    jacobian[0][1] = crossproduct(four_Times_two_matrix(tp_Yellow_bone_obj_mat,world_vec_x),dx_forPink);
    
    temp = four_Times_two_matrix(Rotate_Z_Pink,world_vec_y);
    temp = four_Times_two_matrix(Rotate_X_Pink,temp);
    temp = four_Times_two_matrix(tp_Yellow_bone_obj_mat,temp);
    jacobian[1][1] = crossproduct(temp,dy_forPink);
    
    temp = four_Times_two_matrix(Rotate_X_Pink,world_vec_z);
    temp = four_Times_two_matrix(tp_Yellow_bone_obj_mat,temp);
    jacobian[2][1] = crossproduct(temp,dz_forPink);
    //
    
    jacobian[0][2] = crossproduct(four_Times_two_matrix(tp_Pink_bone_obj_mat,world_vec_x),dx_forTur);
    
    temp = four_Times_two_matrix(Rotate_Z_Turp,world_vec_y);
    temp = four_Times_two_matrix(Rotate_X_Turp,temp);
    temp = four_Times_two_matrix(tp_Pink_bone_obj_mat,temp);
    jacobian[1][2] = crossproduct(temp,dy_forTur);
    
    temp = four_Times_two_matrix(Rotate_X_Turp,world_vec_z);
    temp = four_Times_two_matrix(tp_Pink_bone_obj_mat,temp);
    jacobian[2][2] = crossproduct(temp,dz_forTur);
    
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            std::cout<<jacobian[i][j]<<std::endl;
        }
    }
    std::cout<<" "<<std::endl;
     */
    glm::vec3 v1 = glm::cross(glm::normalize(glm::vec3(tp_Yellow_bone_obj_mat[2])),dx_forYellow);
    
    std::cout<<v1.x<<std::endl;
    
    
    return jacobian;
    
}



float Bone_Animation::delta_theta(glm::mat3 jacobian){
    //先算alpha
    //只要用alpha乘以jacobian就可以了
    glm::vec3 endposition;
    glm::mat4 tp_Turquoise_bone_obj_mat = glm::translate(Turquoise_bone_obj_mat,glm::vec3(0.0f,0.5f,0.0f));
    
    endposition[0] = tp_Turquoise_bone_obj_mat[3][0];
    endposition[1] = tp_Turquoise_bone_obj_mat[3][1];
    endposition[2] = tp_Turquoise_bone_obj_mat[3][2];
    glm::vec3 distance_between_ge = object_position-endposition;
    glm::mat3 Inverse_jacobian = transpose(jacobian);
    glm::vec3 uppervec = three_times_three_vec(Inverse_jacobian,distance_between_ge);
    
    float uppermode = sqrt(uppervec[0]*uppervec[0]+uppervec[1]*uppervec[1]+uppervec[2]*uppervec[2]);
    
    glm::vec3 lowervec = three_times_three_vec(jacobian*Inverse_jacobian,distance_between_ge);
    
    float lowermode = sqrt(lowervec[0]*lowervec[0]+lowervec[1]*lowervec[1]+lowervec[2]);
    
    //std::cout<<uppermode/lowermode<<std::endl;
    return uppermode/lowermode;
    
}

glm::mat3 Bone_Animation::transpose(glm::mat3 jacobian){
    glm::mat3 temp_jacobian = glm::mat3(0.0f);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp_jacobian[j][i] = jacobian[i][j];
        }
    }
    return temp_jacobian;
    
}
glm::vec3 Bone_Animation::three_times_three_vec(glm::mat3 jacobian,glm::vec3 distance){
    glm::vec3 temp_vec = glm::vec3(0.0f);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp_vec[i] +=jacobian[i][j]*distance[j];
        }
    }
    return temp_vec;
    
}
glm::vec4 Bone_Animation::four_Times_two_matrix(glm::mat4 temp1,glm::vec4 temp2){
    glm::vec4 temp3 = glm::vec4(0.0f);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp3[i] += temp1[i][j]*temp2[j];
        }
    }
    return temp3;
    
}
float Bone_Animation::crossproduct(glm::vec4 tempv1, glm::vec4 tempv2){
    return tempv1[1]*tempv2[2]-tempv1[2]*tempv2[1]+tempv1[2]*tempv2[0]-tempv1[0]*tempv2[2]+tempv1[0]*tempv2[1]-tempv1[1]*tempv2[0];
    //return tempv1[2]*tempv2[0];
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
    rotation_degree_vector =
    {
        //{0.0f,0.0f,0.0f},
        {0.0f,0.0f,0.0f},
        {0.0f,0.0f,0.0f},
        {0.0f,0.0f,0.0f}
    };
}

