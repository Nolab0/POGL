#include "init.h"

GLuint program_id;

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

std::vector<Vertex> loadOBJ(const std::string& filePath) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<Vertex> vertices;

    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            positions.push_back(position);
        } else if (type == "vt") {
            glm::vec2 uv;
            iss >> uv.x >> uv.y;
            uvs.push_back(uv);
        } else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (type == "f") {
            std::string faceData[3];
            iss >> faceData[0] >> faceData[1] >> faceData[2];

            for (int i = 0; i < 3; i++) {
                std::istringstream faceIss(faceData[i]);
                std::string vertexData[3];
                std::getline(faceIss, vertexData[0], '/');
                std::getline(faceIss, vertexData[1], '/');
                std::getline(faceIss, vertexData[2], '/');

                Vertex vertex;
                vertex.position = positions[std::stoi(vertexData[0]) - 1];
                vertex.uv = uvs[std::stoi(vertexData[1]) - 1];
                vertex.normal = normals[std::stoi(vertexData[2]) - 1];
                vertices.push_back(vertex);
            }
        }
    }

    return vertices;
}

GLFWwindow* init_glfw(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Object Viewer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    return window;
}

void init_glew(){
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
}

View init_obj_and_shaders(){
    std::vector<Vertex> vertices = loadOBJ("../test.obj");

    std::string vertexShaderSource = load("../vertex.shd");
    std::string fragmentShaderSource = load("../fragment.shd");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCode = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCode = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    program_id = glCreateProgram();
    glAttachShader(program_id, vertexShader);
    glAttachShader(program_id, fragmentShader);
    glLinkProgram(program_id);
    glUseProgram(program_id);

    // Create vertex array object (VAO)
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create vertex buffer object (VBO)
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Specify vertex attributes
    GLint positionAttrib = glGetAttribLocation(program_id, "position");
    glEnableVertexAttribArray(positionAttrib);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

    GLint uvAttrib = glGetAttribLocation(program_id, "uv");
    glEnableVertexAttribArray(uvAttrib);
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

    GLint normalAttrib = glGetAttribLocation(program_id, "normal");
    glEnableVertexAttribArray(normalAttrib);
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    GLint projectionUniform = glGetUniformLocation(program_id, "projection");
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    // Model and view matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    GLint modelUniform = glGetUniformLocation(program_id, "model");
    GLint viewUniform = glGetUniformLocation(program_id, "view");
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));

    return {
        view, viewUniform, static_cast<int>(vertices.size())
    };
}