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
    this->test_cube_points_pos = {
        { 0.0,8.0,-1.0 },
        { -3.0, 11.0, 2.3 },
        { -6.0, 8.5, -2.5 },
        { -4.0, 5.5, 2.8 },
        { 1.0, 2.0, -4.0 },
        { 4.0, 2.0, 3.0 },
        { 7.0, 8.0, -2.0 },
        { 3.0, 10.0, 3.7 }
    };
    this->curve_pos = {
        { -6.0, 8.5, -2.5 },
        { 0.0, 8.5, -2.0 },
        { -3.0, 11.0, 2.3 },
        { -6.0, 8.5, -2.5 },
        { -4.0, 5.5, 2.8 },
        { 1.0, 2.0, -4.0 },
        { 4.0, 2.0, 3.0 },
        { 7.0, 8.0, -2.0 },
        { 3.0, 10.0, 3.7 },
        { 0.0, 8.5, -2.0 },
        { -3.0, 11.0, 2.3 }
    };
	calculate_curve();
    this->control_points_quaternion = {
        {0.13964   , 0.0481732 , 0.831429 , 0.541043 , },
        {0.0509038 , -0.033869 , -0.579695, 0.811295 , },
        {-0.502889 , -0.366766 , 0.493961 , 0.592445 , },
        {-0.636    , 0.667177  , -0.175206, 0.198922 , },
        {0.693492  , 0.688833  , -0.152595, -0.108237, },
        {0.752155  , -0.519591 , -0.316988, 0.168866 , },
        {0.542054  , 0.382705  , 0.378416 , 0.646269 , },
        {0.00417342, -0.0208652, -0.584026, 0.810619   }
    };
    //calculate_quaternion();
}

void Curve::calculate_curve()
{
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
}

glm::mat4 Curve::calculate_quaternion(glm::mat4 model_mat, int k){
    quaternion_matrix = glm::mat3(0.0f);
    //std::cout<<quaternion_matrix[0][0]<<std::endl;
    std::vector<glm::quat> pq = control_points_quaternion;
    /*
    glm::mat4 test = glm::toMat4(pq[0]);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<test[i][j]<<std::endl;
        }
    }
     */
    //std::cout<<pq[0][3]<<std::endl;
    
    float x = pq[k][0];
    float y = pq[k][1];
    float z = pq[k][2];
    float s = pq[k][3];
    quaternion_matrix[0][0] = 1-2*y*y-2*z*z;
    quaternion_matrix[0][1] = 2*x*y-2*s*z;
    quaternion_matrix[0][2] = 2*x*z+2*s*y;
    
    quaternion_matrix[1][0] = 2*x*y+2*s*z;
    quaternion_matrix[1][1] = 1-2*x*x-2*z*z;
    quaternion_matrix[1][2] = 2*y*z-2*s*x;
    
    quaternion_matrix[2][0] = 2*x*z-2*s*y;
    quaternion_matrix[2][1] = 2*y*z+2*s*x;
    quaternion_matrix[2][2] = 1-2*x*x-2*y*y;
    transpose();
    
    //std::cout<<quaternion_matrix<<std::endl;
    glm::vec3 testans = glm::vec3(0.0f); //= quaternion_matrix*control_points_pos[0];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            //testans[i] += quaternion_matrix[i][j]*control_points_pos[k][j];
            model_mat[i][j] = quaternion_matrix[i][j];
            //model_mat[i][j] = 0.0005;
        }
    }
    //std::cout<<" "<<std::endl;
    for(int i=0;i<3;i++){
        
        //std::cout<<testans[i]<<std::endl;
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //std::cout<<model_mat[i][j]<<std::endl;
        }
    }
    //glm::mat4 model_mat = glm::mat4(1.0f);
     
    return model_mat;
}
void Curve::transpose(){
    float temp1 = quaternion_matrix[0][1];
    quaternion_matrix[0][1] = quaternion_matrix[1][0];
    quaternion_matrix[1][0] = temp1;
    float temp2 = quaternion_matrix[0][2];
    quaternion_matrix[0][2] = quaternion_matrix[2][0];
    quaternion_matrix[2][0] = temp2;
    float temp3 = quaternion_matrix[1][2];
    quaternion_matrix[1][2] = quaternion_matrix[2][1];
    quaternion_matrix[2][1] = temp3;
    
    
}
