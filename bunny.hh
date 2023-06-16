static std::vector<GLfloat> vertex_buffer_data {
    // Front face
    -0.5f, -0.5f, 0.5f,  // Bottom-left
    0.5f, -0.5f, 0.5f,   // Bottom-right
    0.5f, 0.5f, 0.5f,    // Top-right

    0.5f, 0.5f, 0.5f,    // Top-right
    -0.5f, 0.5f, 0.5f,   // Top-left
    -0.5f, -0.5f, 0.5f,  // Bottom-left

    // Back face
    -0.5f, -0.5f, -0.5f, // Bottom-left
    0.5f, -0.5f, -0.5f,  // Bottom-right
    0.5f, 0.5f, -0.5f,   // Top-right

    0.5f, 0.5f, -0.5f,   // Top-right
    -0.5f, 0.5f, -0.5f,  // Top-left
    -0.5f, -0.5f, -0.5f, // Bottom-left

    // Left face
    -0.5f, 0.5f, 0.5f,   // Top-right
    -0.5f, 0.5f, -0.5f,  // Top-left
    -0.5f, -0.5f, -0.5f, // Bottom-left

    -0.5f, -0.5f, -0.5f, // Bottom-left
    -0.5f, -0.5f, 0.5f,  // Bottom-right
    -0.5f, 0.5f, 0.5f,   // Top-right

    // Right face
    0.5f, 0.5f, 0.5f,    // Top-left
    0.5f, 0.5f, -0.5f,   // Top-right
    0.5f, -0.5f, -0.5f,  // Bottom-right

    0.5f, -0.5f, -0.5f,  // Bottom-right
    0.5f, -0.5f, 0.5f,   // Bottom-left
    0.5f, 0.5f, 0.5f,    // Top-left

    // Top face
    -0.5f, 0.5f, 0.5f,   // Bottom-right
    0.5f, 0.5f, 0.5f,    // Bottom-left
    0.5f, 0.5f, -0.5f,   // Top-left

    0.5f, 0.5f, -0.5f,   // Top-left
    -0.5f, 0.5f, -0.5f,  // Top-right
    -0.5f, 0.5f, 0.5f,   // Bottom-right

    // Bottom face
    -0.5f, -0.5f, 0.5f,  // Top-right
    0.5f, -0.5f, 0.5f,   // Top-left
    0.5f, -0.5f, -0.5f,  // Bottom-left

    0.5f, -0.5f, -0.5f,  // Bottom-left
    -0.5f, -0.5f, -0.5f, // Bottom-right
    -0.5f, -0.5f, 0.5f   // Top-right
};

static std::vector<GLfloat> normal_smooth_buffer_data {
      // Front face
      0.0f, 0.0f, 1.0f,  // Bottom-left
      0.0f, 0.0f, 1.0f,  // Bottom-right
      0.0f, 0.0f, 1.0f,  // Top-right

      0.0f, 0.0f, 1.0f,  // Top-right
      0.0f, 0.0f, 1.0f,  // Top-left
      0.0f, 0.0f, 1.0f,  // Bottom-left

      // Back face
      0.0f, 0.0f, -1.0f, // Bottom-left
      0.0f, 0.0f, -1.0f, // Bottom-right
      0.0f, 0.0f, -1.0f, // Top-right

      0.0f, 0.0f, -1.0f, // Top-right
      0.0f, 0.0f, -1.0f, // Top-left
      0.0f, 0.0f, -1.0f, // Bottom-left

      // Left face
      -1.0f, 0.0f, 0.0f, // Top-right
      -1.0f, 0.0f, 0.0f, // Top-left
      -1.0f, 0.0f, 0.0f, // Bottom-left

      -1.0f, 0.0f, 0.0f, // Bottom-left
      -1.0f, 0.0f, 0.0f, // Bottom-right
      -1.0f, 0.0f, 0.0f, // Top-right

      // Right face
      1.0f, 0.0f, 0.0f,  // Top-left
      1.0f, 0.0f, 0.0f,  // Top-right
      1.0f, 0.0f, 0.0f,  // Bottom-right

      1.0f, 0.0f, 0.0f,  // Bottom-right
      1.0f, 0.0f, 0.0f,  // Bottom-left
      1.0f, 0.0f, 0.0f,  // Top-left

      // Top face
      0.0f, 1.0f, 0.0f,  // Bottom-right
      0.0f, 1.0f, 0.0f,  // Bottom-left
      0.0f, 1.0f, 0.0f,  // Top-left

      0.0f, 1.0f, 0.0f,  // Top-left
      0.0f, 1.0f, 0.0f,  // Top-right
      0.0f, 1.0f, 0.0f,  // Bottom-right

      // Bottom face
      0.0f, -1.0f, 0.0f, // Top-right
      0.0f, -1.0f, 0.0f, // Top-left
      0.0f, -1.0f, 0.0f, // Bottom-left

      0.0f, -1.0f, 0.0f, // Bottom-left
      0.0f, -1.0f, 0.0f, // Bottom-right
      0.0f, -1.0f, 0.0f  // Top-right
};