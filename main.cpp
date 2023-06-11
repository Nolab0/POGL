#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

GLuint programID;
GLuint vaoID;
GLuint vboID;

int windowWidth = 800;
int windowHeight = 600;

std::string readShaderFile(const char* filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void initialize() {
    glewInit();

    // Create vertex array object (VAO)
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    // Create vertex buffer object (VBO)
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Vertex data
    GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f,
            1.0f,  1.0f, 0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Load shaders
    std::string vertexShaderSource = readShaderFile("../vertexshader.glsl");
    std::string fragmentShaderSource = readShaderFile("../fragmentshader.glsl");
    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    // Create vertex shader
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShaderID);

    // Check for vertex shader compilation errors
    GLint vertexShaderStatus;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexShaderStatus);
    if (vertexShaderStatus == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);
        std::string errorLog(maxLength, ' ');
        glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, &errorLog[0]);
        std::cerr << "Vertex shader compilation failed: " << errorLog << std::endl;
        return;
    }

    // Create fragment shader
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderID);

    // Check for fragment shader compilation errors
    GLint fragmentShaderStatus;
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fragmentShaderStatus);
    if (fragmentShaderStatus == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);
        std::string errorLog(maxLength, ' ');
        glGetShaderInfoLog(fragmentShaderID, maxLength, &maxLength, &errorLog[0]);
        std::cerr << "Fragment shader compilation failed: " << errorLog << std::endl;
        return;
    }

    // Create program and attach shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    glUseProgram(programID);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    windowWidth = width;
    windowHeight = height;
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Water Simulation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    initialize();

    glutMainLoop();

    return 0;
}
