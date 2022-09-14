#include "Aircraft_Animation.h"


Aircraft_Animation::Aircraft_Animation()
{
	this->m_model_mat = glm::mat4(1.0f);
}


Aircraft_Animation::~Aircraft_Animation()
{
}

void Aircraft_Animation::init()
{
    
	reset();
}

void Aircraft_Animation::init(Curve* animation_curve)
{
	m_animation_curve = animation_curve;
    make_table();
	reset();
}

void Aircraft_Animation::update(float delta_time)
{
    if(i<59*total_moving_time){
        m_model_mat = glm::translate(glm::mat4(1.0f),plane_pos[i]);
        i++;
    }else{
        
        reset();
    }

}

void Aircraft_Animation::reset()
{
	m_model_mat = glm::mat4(1.0f);

	if (m_animation_curve != nullptr && m_animation_curve->control_points_pos.size() > 0)
	{
		m_model_mat = glm::translate(m_model_mat, m_animation_curve->control_points_pos[0]);
        glm::mat4 test3 = glm::toMat4(m_animation_curve->control_points_quaternion[0]);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                m_model_mat[i][j] = test3[i][j];
                
            }
        }
        //m_model_mat = glm::translate(m_model_mat,m_animation_curve->control_points_pos[0]);
	}
}
void Aircraft_Animation::make_table()
{
    int counter = total_moving_time*60;
    float velocity = 2.0/(t2-t1+1);
    
    float increment = 1.0/counter;
    float begin_time = 0.0;
    float tempanswer;
    for(int i=0;i<counter;i++){
        //std::cout<<begin_time<<std::endl;
        //begin_time =i*increment;
        if(begin_time<=t1){
            tempanswer = velocity*begin_time*begin_time/2/t1;
            table1.insert(table1.end(),tempanswer);
        }else if(begin_time>t1&&begin_time<t2){
            tempanswer = velocity*t1/2+velocity*(begin_time-t1);
            table1.insert(table1.end(),tempanswer);
        }else if(begin_time>t2){
            float te = (begin_time-t2)/(1-t2)/2;
            tempanswer = velocity*t1/2+velocity*(t2-t1)+velocity*(begin_time-t2)*(1-te);
            //tempanswer.setprecision(3);
            table1.insert(table1.end(),tempanswer);
        }
        //std::cout<<tempanswer<<std::endl;
        begin_time = begin_time+increment;
    }
    //std::cout<<table1.size()<<std::endl;
    //std::vector<float> table2;
    table2.insert(table2.end(),0.0);
    float lasttemp = 0.0f;
    for(int i=1;i<1600;i++){
        //std::cout<<table1[i]<<std::endl;
        float first_x = m_animation_curve->curve_points_pos[i-1][0];
        float first_y = m_animation_curve->curve_points_pos[i-1][1];
        float first_z = m_animation_curve->curve_points_pos[i-1][2];
        //
        float second_x = m_animation_curve->curve_points_pos[i][0];
        float second_y = m_animation_curve->curve_points_pos[i][1];
        float second_z = m_animation_curve->curve_points_pos[i][2];
        float tempans = pow(first_x-second_x,2)+pow(first_y-second_y,2)+pow(first_z-second_z,2);
        tempans = sqrt(tempans);
        lasttemp +=tempans;
        table2.insert(table2.end(),lasttemp);
        //std::cout<<lasttemp<<std::endl;
    }
    //normalize table2
    for(int i=0;i<1600;i++){
        table2[i]=table2[i]/table2[1599];
        
    }
    
    plane_pos.insert(plane_pos.end(),m_animation_curve->curve_points_pos[0]);
    int j = 0;
    int count =0;
    int size = table2.size();
    for(int i=1;i<table1.size();i++){
        for(int j=1;j<table2.size();j++){
            if(table1[i]>table2[j-1]&&table1[i]<table2[j]){
                float frc = (table1[i]-table2[j-1])/(table2[j]-table2[j-1]);
                float planeX = (1-frc)*m_animation_curve->curve_points_pos[j-1][0]+frc*m_animation_curve->curve_points_pos[j][0];
                float planeY = (1-frc)*m_animation_curve->curve_points_pos[j-1][1]+frc*m_animation_curve->curve_points_pos[j][1];
                float planeZ = (1-frc)*m_animation_curve->curve_points_pos[j-1][2]+frc*m_animation_curve->curve_points_pos[j][2];
                glm::vec3 point = {planeX,planeY,planeZ};
                plane_pos.insert(plane_pos.end(),point);
                position_index.insert(position_index.end(),j);
                count++;
            }
        }
    }
    //position_index.insert(position_index.end(),0);
    
}



void Aircraft_Animation::clear_table(){
    i=0;
    //std::cout<<t1<<std::endl;
    table1 = {};
    table2 = {};
    plane_pos = {};
    position_index = {};
    
    
}

glm::mat4 Aircraft_Animation::getAirquaternion(glm::mat4 model_mat){
    std::vector<float> degree_between_segment;
    for(int i=0;i<7;i++){
        float x1 = m_animation_curve->control_points_pos[i][0];
        float y1 = m_animation_curve->control_points_pos[i][1];
        float z1 = m_animation_curve->control_points_pos[i][2];
        
        float x2 = m_animation_curve->control_points_pos[i+1][0];
        float y2 = m_animation_curve->control_points_pos[i+1][1];
        float z2 = m_animation_curve->control_points_pos[i+1][2];
        
        float dot = x1*x2 + y1*y2 +z1*z2;
        float lenSq1 = std::sqrt(x1*x1 + y1*y1 + z1*z1);
        float lenSq2 = std::sqrt(x2*x2 + y2*y2 + z2*z2);
        float angle = std::acos(dot/lenSq1/lenSq2);
        //angle = 180*angle/3.14159f;
        degree_between_segment.insert(degree_between_segment.end(),angle);
    }
    float x1 = m_animation_curve->control_points_pos[7][0];
    float y1 = m_animation_curve->control_points_pos[7][1];
    float z1 = m_animation_curve->control_points_pos[7][2];
    
    float x2 = m_animation_curve->control_points_pos[0][0];
    float y2 = m_animation_curve->control_points_pos[0][1];
    float z2 = m_animation_curve->control_points_pos[0][2];
    
    float dot = x1*x2 + y1*y2 +z1*z2;
    float lenSq1 = std::sqrt(x1*x1 + y1*y1 + z1*z1);
    float lenSq2 = std::sqrt(x2*x2 + y2*y2 + z2*z2);
    float angle = std::acos(dot/lenSq1/lenSq2);
    //angle = 180*angle/3.14159f;
    degree_between_segment.insert(degree_between_segment.end(),angle);
    std::cout<<position_index[i]<<std::endl;
    if(position_index[i]>=0&&position_index[i]<200){
        float fra = (position_index[i])/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[0];
        glm::quat q = m_animation_curve->control_points_quaternion[1];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        
        return Aircraft_Animation::rotateM(model_mat,z);
        
        
    }else if(position_index[i]>=200&&position_index[i]<400){
        float fra = (position_index[i]-200.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[1];
        glm::quat q = m_animation_curve->control_points_quaternion[2];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        //float degree = degree_between_segment[1];
        //glm::quat z = (sin((1-fra)*degree)*p+sin(fra*degree)*q)/sin(degree);
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }else if(position_index[i]>=400&&position_index[i]<600){
        float fra = (position_index[i]-400.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[2];
        glm::quat q = m_animation_curve->control_points_quaternion[3];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }else if(position_index[i]>=600&&position_index[i]<800){
        float fra = (position_index[i]-600.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[3];
        glm::quat q = m_animation_curve->control_points_quaternion[4];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }else if(position_index[i]>=800&&position_index[i]<1000){
        float fra = (position_index[i]-800.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[4];
        glm::quat q = m_animation_curve->control_points_quaternion[5];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }else if(position_index[i]>=1000&&position_index[i]<1200){
        float fra = (position_index[i]-1000.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[5];
        glm::quat q = m_animation_curve->control_points_quaternion[6];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }else if(position_index[i]>=1200&&position_index[i]<1400){
        float fra = (position_index[i]-1200.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[6];
        glm::quat q = m_animation_curve->control_points_quaternion[7];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }else if(position_index[i]>=1400&&position_index[i]<1600){
        float fra = (position_index[i]-1400.0)/200.0;
        glm::quat p = m_animation_curve->control_points_quaternion[7];
        glm::quat q = m_animation_curve->control_points_quaternion[0];
        glm::quat z = glm::mix(p,q,fra);
        //std::cout<<i<<std::endl;
        //std::cout<<fra<<std::endl;
        return Aircraft_Animation::rotateM(model_mat,z);
        
    }
    
    return model_mat;
    
}
glm::mat4 Aircraft_Animation::rotateM(glm::mat4 model_mat,glm::quat z){
    glm::mat4 test = glm::toMat4(z);
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            model_mat[i][j] = test[i][j];
        }
    }
    return model_mat;
    
}


