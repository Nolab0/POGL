//
// Created by jeanf on 6/16/23.
//

#include "init.h"

void test_opengl_error(std::string func, std::string file, int line);

#define TEST_OPENGL_ERROR()                                                             \
  do {                                                              		  							\
     test_opengl_error(__func__, __FILE__, __LINE__);                                   \
  } while(0)


GLuint bunny_vao_id;
GLuint program_id;

void window_resize(int width, int height) {
    glViewport(0,0,width,height);TEST_OPENGL_ERROR();
}

void display() {
    glUseProgram(program_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);TEST_OPENGL_ERROR();
    glBindVertexArray(bunny_vao_id);TEST_OPENGL_ERROR();
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data.size()/3);TEST_OPENGL_ERROR();
    glBindVertexArray(0);TEST_OPENGL_ERROR();
    glutSwapBuffers();
}

void init_glut(int &argc, char *argv[]) {
    //glewExperimental = GL_TRUE;
    glutInit(&argc, argv);
    glutInitContextVersion(4,5);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition ( 100, 100 );
    glutCreateWindow("Shader Programming");
    glutDisplayFunc(display);
    glutReshapeFunc(window_resize);
    glutMouseFunc(mouse_callback);
    glutMotionFunc(mouse_motion_callback);
}

bool init_glew() {
    if (glewInit()) {
        std::cerr << " Error while initializing glew";
        return false;
    }
    return true;
}

void init_GL() {
    glEnable(GL_DEPTH_TEST);TEST_OPENGL_ERROR();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);TEST_OPENGL_ERROR();
    glEnable(GL_CULL_FACE);TEST_OPENGL_ERROR();
    glClearColor(0.4,0.4,0.4,1.0);TEST_OPENGL_ERROR();
}


void init_object() {
    int max_nb_vbo = 5;
    int nb_vbo = 0;
    int index_vbo = 0;
    GLuint vbo_ids[max_nb_vbo];

    GLint vertex_location = glGetAttribLocation(program_id,"position");TEST_OPENGL_ERROR();
    GLint normal_smooth_location = glGetAttribLocation(program_id,"normalSmooth");TEST_OPENGL_ERROR();

    glGenVertexArrays(1, &bunny_vao_id);TEST_OPENGL_ERROR();
    glBindVertexArray(bunny_vao_id);TEST_OPENGL_ERROR();

    if (vertex_location!=-1) nb_vbo++;
    if (normal_smooth_location!=-1) nb_vbo++;
    glGenBuffers(nb_vbo, vbo_ids);TEST_OPENGL_ERROR();

    if (vertex_location!=-1) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);TEST_OPENGL_ERROR();
        glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(float), vertex_buffer_data.data(), GL_STATIC_DRAW);TEST_OPENGL_ERROR();
        glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, 0);TEST_OPENGL_ERROR();
        glEnableVertexAttribArray(vertex_location);TEST_OPENGL_ERROR();
    }

    if (normal_smooth_location!=-1) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_vbo++]);TEST_OPENGL_ERROR();
        glBufferData(GL_ARRAY_BUFFER, normal_smooth_buffer_data.size()*sizeof(float), normal_smooth_buffer_data.data(), GL_STATIC_DRAW);TEST_OPENGL_ERROR();
        glVertexAttribPointer(normal_smooth_location, 3, GL_FLOAT, GL_FALSE, 0, 0);TEST_OPENGL_ERROR();
        glEnableVertexAttribArray(normal_smooth_location);TEST_OPENGL_ERROR();
    }

    glBindVertexArray(0);
}


std::string load(const std::string &filename) {
    std::ifstream input_src_file(filename, std::ios::in);
    std::string ligne;
    std::string file_content="";
    if (input_src_file.fail()) {
        std::cerr << "FAILURE: can not load " << filename << "\n";
        return "";
    }
    while(getline(input_src_file, ligne)) {
        file_content = file_content + ligne + "\n";
    }
    file_content += '\0';
    input_src_file.close();
    return file_content;
}

bool load_and_compile_shader(const GLenum shader_type,const std::string shader_src_filename, GLuint &shader_id) {
    GLint compile_status = GL_TRUE;
    std::string shader_src = load(shader_src_filename);
    const GLchar *sources[1];
    sources[0] = shader_src.c_str();
    shader_id = glCreateShader(shader_type);TEST_OPENGL_ERROR();
    glShaderSource(shader_id, 1, sources, 0);TEST_OPENGL_ERROR();
    glCompileShader(shader_id);TEST_OPENGL_ERROR();
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE) {
        GLint log_size;
        char *shader_log;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);
        shader_log = (char*)std::malloc(log_size+1); /* +1 pour le caractere de fin de chaine '\0' */
        if(shader_log != 0) {
            glGetShaderInfoLog(shader_id, log_size, &log_size, shader_log);
            std::cerr << "FAILURE can not compile shader " << shader_src_filename << ": " << shader_log << std::endl;
            std::free(shader_log);
        }
        glDeleteShader(shader_id);
        return false;
    }
    return true;
}

bool attach_and_link_program(const std::vector<GLuint> &shaders_id, GLuint &program_id) {
    GLint link_status=GL_TRUE;
    program_id=glCreateProgram();TEST_OPENGL_ERROR();
    if (program_id==0) return false;
    for(unsigned int i = 0 ; i < shaders_id.size() ; i++) {
        glAttachShader(program_id, shaders_id[i]);TEST_OPENGL_ERROR();
    }
    glLinkProgram(program_id);TEST_OPENGL_ERROR();
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status!=GL_TRUE) {
        GLint log_size;
        char *program_log;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
        program_log = (char*)std::malloc(log_size+1); /* +1 pour le caractere de fin de chaine '\0' */
        if(program_log != 0) {
            glGetProgramInfoLog(program_id, log_size, &log_size, program_log);
            std::cerr << "FAILURE: Program can not be linked " << program_log << std::endl;
            std::free(program_log);
        }
        for(unsigned int i = 0 ; i < shaders_id.size() ; i++) {
            glDetachShader(program_id, shaders_id[i]);TEST_OPENGL_ERROR();
        }
        glDeleteProgram(program_id);TEST_OPENGL_ERROR();
        program_id=0;
        return false;
    }
    //glUseProgram(program_id);TEST_OPENGL_ERROR();
    return true;
}

bool init_shaders() {
    GLuint vertex_shader_id, fragment_shader_id;
    if (!load_and_compile_shader(GL_VERTEX_SHADER, "../vertex.shd", vertex_shader_id)) {
        return false;
    }
    if (!load_and_compile_shader(GL_FRAGMENT_SHADER, "../fragment.shd", fragment_shader_id)) {
        return false;
    }

    std::vector<GLuint> shaders_id;
    shaders_id.push_back(vertex_shader_id);
    shaders_id.push_back(fragment_shader_id);


    if (!attach_and_link_program(shaders_id, program_id)) {
        for(unsigned int i = 0 ; i < shaders_id.size() ; i++) {
            glDeleteShader(shaders_id[i]);TEST_OPENGL_ERROR();
        }
        return false;
    }

    for(unsigned int i = 0 ; i < shaders_id.size() ; i++) {
        glDetachShader(program_id, shaders_id[i]);TEST_OPENGL_ERROR();
    }

    for(unsigned int i = 0 ; i < shaders_id.size() ; i++) {
        glDeleteShader(shaders_id[i]);TEST_OPENGL_ERROR();
    }
    return true;
}


void test_opengl_error(std::string func, std::string file, int line) {
    GLenum err = glGetError();
    switch (err) {
        case GL_NO_ERROR: return;
        case GL_INVALID_ENUM: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_INVALID_ENUM\n";
            break;
        case GL_INVALID_VALUE: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_INVALID_VALUE\n";
            break;
        case GL_INVALID_OPERATION: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_INVALID_OPERATION\n";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
            break;
        case GL_OUT_OF_MEMORY: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_OUT_OF_MEMORY\n";
            break;
        case GL_STACK_UNDERFLOW: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_STACK_UNDERFLOW\n";
            break;
        case GL_STACK_OVERFLOW: std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "GL_STACK_OVERFLOW\n";
            break;
        default:std::cerr << file << ":" << line << "(" << func << ") ";
            std::cerr << "UNKONWN ERROR\n";
            break;
    }

}

