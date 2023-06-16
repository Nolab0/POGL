#include "main.hh"

#include "waves.hh"
#include <vector>


// settings
const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

float mouse_x = SRC_WIDTH / 2;
float mouse_y = SRC_HEIGHT / 2;
float fov = 45.0f;
unsigned char mouse_action = 0;

float opt_speed = 0.8f;
float opt_amount = 0.01f;
float opt_height = 0.5f;
unsigned char opt_mesh = 0;


Camera* camera = new Camera();
GLFWwindow* window = NULL;

int main(void)
{
    init_opengl();

    float rec_width = 0.5f;

    /* Initialize the cubemap */
    Shader shader_cubemap("../shaders/vertex_cubemap.glsl", "../shaders/frag_cubemap.glsl");
    std::vector<std::string> faces
    {
        "../resources/cubemap/right.jpg",
        "../resources/cubemap/left.jpg",
        "../resources/cubemap/up.jpg",
        "../resources/cubemap/down.jpg",
        "../resources/cubemap/front.jpg",
        "../resources/cubemap/back.jpg"
    };
    unsigned int texture_cubemap = load_cubemap_texture(faces);
    unsigned int VAO_cubemap = load_cubemap();

    // Size of the ocean
    int width = 500;

    /* Initialize the water */
    Shader shader_water("../shaders/vertex_water.glsl", "../shaders/frag_water.glsl");
    unsigned int texture_water = load_texture("../resources/water.png");
    auto vertices_water = init_plane(width, rec_width, 4.0f);
    auto indices_water = init_indices(width);
    unsigned int VAO_water = load_object(vertices_water, indices_water);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);

    shader_cubemap.use();
    shader_cubemap.setInt("skybox", 2);

    shader_water.use();
    shader_water.setInt("TexWater", 0);
    shader_water.setInt("skybox", 2);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_water);
        glActiveTexture(GL_TEXTURE1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_cubemap);

        /* Water */
        shader_water.use();
        shader_water.updateView(fov, SRC_WIDTH, SRC_HEIGHT, camera->GetViewMatrix(), false);

        shader_water.setFloat("time", glfwGetTime());
        shader_water.setVec3("cameraPos", camera->Position);

        shader_water.setFloat("speed", opt_speed);
        shader_water.setFloat("amount", opt_amount);
        shader_water.setFloat("height", opt_height);

        glBindVertexArray(VAO_water);
        glDrawElements(GL_TRIANGLES, indices_water->size(), GL_UNSIGNED_INT, 0);

        /* Cubemap */
        glDepthFunc(GL_LEQUAL);
        shader_cubemap.use();
        shader_cubemap.updateView(fov, SRC_WIDTH, SRC_HEIGHT, camera->GetViewMatrix(), true);

        glBindVertexArray(VAO_cubemap);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    (void)window;

    static float last_time = glfwGetTime();

    float curr_time = glfwGetTime();
    float delta_time = curr_time - last_time;
    last_time = curr_time;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // -- Camera
        if (key == GLFW_KEY_RIGHT)
            camera->ProcessKeyboard(RIGHT, delta_time);
        else if (key == GLFW_KEY_LEFT)
            camera->ProcessKeyboard(LEFT, delta_time);
        else if (key == GLFW_KEY_UP)
            camera->ProcessKeyboard(FORWARD, delta_time);
        else if (key == GLFW_KEY_DOWN)
            camera->ProcessKeyboard(BACKWARD, delta_time);
        // --- Water
        // Speed
        else if (key == GLFW_KEY_Q && opt_speed < 2.0f)
            opt_speed += 0.1f;
        else if (key == GLFW_KEY_W && opt_speed > 0.0f)
            opt_speed -= 0.1f;
        // Amount
        else if (key == GLFW_KEY_A && opt_amount < 0.1f)
            opt_amount += 0.01f;
        else if (key == GLFW_KEY_S && opt_amount > 0.0f)
            opt_amount -= 0.1f;
        // Height
        else if (key == GLFW_KEY_Z && opt_height < 0.5f)
            opt_height += 0.1f;
        else if (key == GLFW_KEY_X && opt_height > 0.0f)
            opt_height -= 0.1f;
        // -- Misc
        // Mesh grid
        else if (key == GLFW_KEY_M)
        {
            if (opt_mesh)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            opt_mesh = opt_mesh ? 0 : 1;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void)window;

    if (!mouse_action)
        return;

    float xoffset = mouse_x - xpos;
    float yoffset = mouse_y - ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
    mouse_x = xpos;
    mouse_y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    (void)mods;
    (void)window;

    if (button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            mouse_action = 1;
    }
    else
        mouse_action = 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void init_opengl(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Water Simulation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // Set callbacks
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
}

unsigned int load_texture(const char* path)
{
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}

unsigned int load_cubemap_texture(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
            exit(1);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}