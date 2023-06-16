//
// Created by jeanf on 6/16/23.
//

#include "camera.h"


double distance = 17;
double angle_alpha = 0;
double angle_beta = 0;
double sky_up = 1;

int old_pos_x = 0;
int old_pos_y = 0;

void frustum(GLfloat data[16],
             const float &left, const float &right,
             const float &bottom, const float &top,
             const float &z_near, const float &z_far
)
{

    float a = (right+left)/(right-left);
    float b = (top+bottom)/(top-bottom);
    float c = -(z_far+z_near)/(z_far-z_near);
    float d = -(2*z_far*z_near)/(z_far-z_near);

    data[0] = 2*z_near/(right-left);
    data[1] = 0;
    data[2] = a;
    data[3] = 0;

    data[4] = 0;
    data[5] = 2*z_near/(top-bottom);
    data[6] = b;
    data[7] = 0;

    data[8] = 0;
    data[9] = 0;
    data[10] = c;
    data[11] = d;

    data[12] = 0;
    data[13] = 0;
    data[14] = -1;
    data[15] = 0;

    // std::cout << "data\n";
    // std::cout << data[0] << " " << data[1] << " " <<  data[2] << " " <<   data[3] <<  "\n";
    // std::cout << data[4] << " " << data[5] << " " <<  data[6] << " " <<   data[7] <<  "\n";
    // std::cout << data[8] << " " << data[9] << " " <<  data[10] << " " <<   data[11] <<  "\n";
    // std::cout << data[12] << " " << data[13] << " " <<  data[14] << " " <<   data[15] <<  "\n";
}



void look_at(GLfloat data[16],
             const float &eyeX, const float &eyeY, const float &eyeZ,
             const float &centerX, const float &centerY, const float &centerZ,
             float upX, float upY, float upZ
)
{
    float fx = centerX-eyeX;
    float fy = centerY-eyeY;
    float fz = centerZ-eyeZ;

    float sx, sy, sz;
    float sn;
    float ux, uy, uz;

    float nf = std::sqrt(fx*fx+fy*fy+fz*fz);

    float nu = std::sqrt(upX*upX+upY*upY+upZ*upZ);

    fx/=nf;
    fy/=nf;
    fz/=nf;

    upX/=nu;
    upY/=nu;
    upZ/=nu;

    sx = fy*upZ-fz*upY;
    sy = fz*upX-fx*upZ;
    sz = fx*upY-fy*upX;

    sn = std::sqrt(sx*sx+sy*sy+sz*sz);
    sx/=sn;
    sy/=sn;
    sz/=sn;

    ux = sy * fz - sz * fy;
    uy = sz * fx - sx * fz;
    uz = sx * fy - sy * fx;

    data[0] = sx;
    data[1] = sy;
    data[2] = sz;
    data[3] = 0;

    data[4] = ux;
    data[5] = uy;
    data[6] = uz;
    data[7] = 0;

    data[8] = -fx;
    data[9] = -fy;
    data[10] = -fz;
    data[11] = -distance;

    data[12] = 0;
    data[13] = 0;
    data[14] = 0;
    data[15] = 1;
}


void update_position() {
    GLfloat model_view_matrix[16];
    GLfloat projection_matrix[16];

    double p0=distance*cos(angle_alpha)*cos(angle_beta);
    double p1=distance*sin(angle_beta);
    double p2=distance*sin(angle_alpha)*cos(angle_beta);

    look_at(model_view_matrix,
            p0, p1, p2,
            0, 0, 0,
            0, sky_up, 0
    );
    glUseProgram(program_id);
    GLint model_view_matrix_location =
            glGetUniformLocation(program_id, "model_view_matrix");

    //std::cout << "model_view_matrix_location " << model_view_matrix_location << std::endl;
    glUniformMatrix4fv(model_view_matrix_location, 1, GL_TRUE, model_view_matrix);


    frustum(projection_matrix, -0.05, 0.05,
            -0.05, 0.05,
            0.5, 50);
    GLint projection_matrix_location =
            glGetUniformLocation(program_id, "projection_matrix");
    glUniformMatrix4fv(projection_matrix_location, 1, GL_TRUE, projection_matrix);
    //std::cout << "projection_matrix_location " << projection_matrix_location << std::endl;
}

void mouse_motion_callback(int x, int y) {
    double alpha=angle_alpha-(old_pos_x-x)*M_PI/50.0;
    double beta =angle_beta-(old_pos_y-y)*M_PI/50.0;
    double sky;

    if (beta>M_PI/2.0) {
        beta=M_PI/2.0;
        sky=-1;
    } else if (beta<-M_PI/2.0) {
        beta=-M_PI/2.0;
        sky=-1;
    } else sky=1;

    if (alpha>M_PI) alpha-=2*M_PI;
    if (alpha<0) alpha+=2*M_PI;

    angle_alpha = alpha;
    angle_beta = beta;
    sky_up = sky;

    old_pos_x = x;
    old_pos_y = y;
    //  std::cout << "motion" << std::endl;
    update_position();
    glutPostRedisplay();
}

void mouse_wheel_callback(int, int dir, int, int) {
    if (dir < 0) {
        distance --;
        if (distance <5) distance = 5;
    } else if (dir > 0) {
        distance ++;
        if (distance >50) distance = 50;
    }
    update_position();
    glutPostRedisplay();
}

void mouse_callback(int button, int, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        old_pos_x = x;
        old_pos_y = y;
    } if (button == 3 ) mouse_wheel_callback(button, -1, x, y);
    else if (button == 4 ) mouse_wheel_callback(button, 1, x, y);
}