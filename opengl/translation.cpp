#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

/* Read source file to buffer */
char *readSourceFile(const char *file_path) {
    /* Load file */
    FILE *src_file = fopen(file_path, "r");
    if (src_file == NULL) {
        std::cout << "Error loading shader source file: " << file_path
                  << std::endl;
    }

    /* Get file size */
    fseek(src_file, 0, SEEK_END);
    int length = ftell(src_file);
    fseek(src_file, 0, SEEK_SET); // return to beginning of file

    /* Read file */
    char *src = (char *)malloc((length + 1) * sizeof(char)); // Allocate memory
    fread(src, sizeof(char), length, src_file);
    src[length] = '\0';

    fclose(src_file);

    return src;
}

/* Check and print compilation errors */
void debug_shader(GLuint shader, GLuint error_type) {
    GLint success;
    glGetShaderiv(shader, error_type,
                  &success); // Check if errors occurred
    if (success == GL_FALSE) {
        std::cout << "Shader error(" << error_type << "):" << std::endl;

        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH,
                      &length); // Get error log legth

        char *error_message = (char *)malloc(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length,
                           error_message); // Get actual error message

        std::cout << error_message << std::endl; // print

        free(error_message);
        exit(1);
    }
}

/* Check and print compilation errors */
void debug_program(GLuint program, GLuint error_type) {
    GLint success;
    glGetProgramiv(program, error_type,
                   &success); // Check if errors occurred
    if (success == GL_FALSE) {
        std::cout << "Program error(" << error_type << "):" << std::endl;

        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH,
                       &length); // Get error log legth

        char *error_message = (char *)malloc(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length,
                            error_message); // Get actual error message

        std::cout << error_message << std::endl; // print

        free(error_message);
        exit(1);
    }
}

void addShader(GLuint shader_program, const char *shader_text,
               GLenum shader_type) {
    GLuint shader_obj = glCreateShader(shader_type); // Create shader handle

    // System may run out of resources
    if (!shader_obj) {
        std::cout << "Error creating Shader Program" << std::endl;
        exit(1);
    }

    const char *texts[] = {shader_text};
    GLint lengths[1];
    lengths[0] = strlen(shader_text);
    glShaderSource(shader_obj, 1, texts,
                   lengths); // Load shader text into shader hangle

    glCompileShader(shader_obj); // Compile
    debug_shader(shader_obj, GL_COMPILE_STATUS);

    glAttachShader(shader_program, shader_obj);
}

GLuint compileShaders() {
    GLuint shader_program = glCreateProgram(); // Allocate handle to the program

    // System may run out of resources
    if (!shader_program) {
        std::cout << "Error creating Shader Program" << std::endl;
        exit(1);
    }

    char *vertex_shader =
        readSourceFile("resources/shaders/transformations/translation.vs");
    addShader(shader_program, vertex_shader, GL_VERTEX_SHADER);
    free(vertex_shader);

    char *fragment_shader =
        readSourceFile("resources/shaders/basic/fragment.shader");
    addShader(shader_program, fragment_shader, GL_FRAGMENT_SHADER);
    free(fragment_shader);

    glLinkProgram(shader_program); // Link
    debug_program(shader_program, GL_LINK_STATUS);

    // Check if it's compatible with the current state of the OpenGL runtime
    glValidateProgram(shader_program);
    debug_program(shader_program, GL_VALIDATE_STATUS);

    glUseProgram(
        shader_program); // Make program and it's shaders active on the GPU

    return shader_program;
}

/* Because I know I'm just going to create 1 handle I will not return GLuint* */
GLuint createVertexBuffer() {
    GLfloat vertices[] = {-1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0, -1.0, 0.0};
    GLuint VBO[1];

    glGenBuffers(1, VBO);                  // Create handle
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // Bind to target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW); // Write data to the target

    return VBO[0];
}

int main() {
    // Init GLFW and create window
    if (!glfwInit())
        return -1;
    GLFWwindow *window = glfwCreateWindow(800, 800, "First Dot", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize glew
    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing glew" << std::endl;
    }

    // Print version
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* VBO */
    GLuint VBO = createVertexBuffer();

    /* SHADER */
    GLuint program = compileShaders();

    /* GET POSITIONS */
    GLuint loc_TranslationMatrix =
        glGetUniformLocation(program, "TranslationMatrix");
    if (loc_TranslationMatrix == -1) {
        std::cout << "Error getting uniform location of 'TranslationMatrix'"
                  << std::endl;
        exit(1);
    }
    std::cout << "TranslationMatrix: " << loc_TranslationMatrix << std::endl;

    /* SETUP TRANSLATION TRANSFORMATION */
    GLfloat scaleX = 0.5;
    GLfloat scaleY = 0.8;
    GLfloat scaleZ = 0.0;
    GLfloat translation_matrix[4][4] = {{1.0, 0.0, 0.0, scaleX},
                                        {0.0, 1.0, 0.0, scaleY},
                                        {0.0, 0.0, 1.0, scaleZ},
                                        {0.0, 0.0, 0.0, 1.0}};
    GLfloat *matrices = {&translation_matrix[0][0]};

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        glUniformMatrix4fv(loc_TranslationMatrix, 1, GL_TRUE, matrices);

        glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind handle to target
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);

        // Retrieve events
        glfwPollEvents();
    }

    // Close glfw
    glfwTerminate();
    return 0;
}