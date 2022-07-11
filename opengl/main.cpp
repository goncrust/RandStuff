#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

typedef struct ShaderSource {
    char *vertex_source;
    char *fragment_source;
} ShaderSource;

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

/* Create ShaderSource with vertex and fragment shader */
ShaderSource readShaderSource(const char *folder_path) {
    std::string vertex_path = folder_path;
    vertex_path += "/vertex.shader";

    std::string fragment_path = folder_path;
    fragment_path += "/fragment.shader";

    ShaderSource ss = {.vertex_source = readSourceFile(&vertex_path[0]),
                       .fragment_source = readSourceFile(&fragment_path[0])};

    return ss;
}

/* Free vertex and fragment source of ShaderSource */
void freeShaderSource(ShaderSource &ss) {
    free(ss.fragment_source);
    free(ss.vertex_source);
}

/* Load source to shader and compile */
void loadShaderSource(unsigned int id, const char *source) {
    glShaderSource(id, 1, &source, NULL); // Load source code
    glCompileShader(id);                  // Compile

    /* Check and print compilation errors */
    int error;
    glGetShaderiv(id, GL_COMPILE_STATUS, &error); // Check if errors occurred
    if (error == GL_FALSE) {
        std::cout << "Error compiling shader:" << std::endl;

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); // Get error log legth

        char *error_message = (char *)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length,
                           error_message); // Get actual error message

        std::cout << error_message << std::endl; // print

        free(error_message);

        // TODO: handle error
    }
}

/* Create program and compile shaders */
unsigned int createShader(char *vertexShader, char *&fragmentShader) {
    unsigned int program;
    unsigned int vertex_shader;
    unsigned int fragment_shader;

    /* Create a program */
    program = glCreateProgram();

    /* Create vertex shader and load source code */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    loadShaderSource(vertex_shader, vertexShader);

    /* Create fragment shader and load source code */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    loadShaderSource(fragment_shader, fragmentShader);

    /* Load shaders into program */
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);     // Link program
    glValidateProgram(program); // Validate (result will be stored as part of
                                // the program object's state)

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

int main(void) {
    GLFWwindow *window;

    /* Initialize glfw */
    if (!glfwInit())
        return -1;

    /* Select version and profile */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 760, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize glew */
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    /* Print version */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* -------------- Setup Vertex Array ------------------ */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* -------------- Setup Vertex Buffer ----------------- */
    float vertices[] = {-0.5, -0.5, 0.0, 0.5,  -0.5, 0.0,
                        0.5,  0.5,  0.0, -0.5, 0.5,  0.0};

    unsigned int VBO;
    glGenBuffers(1, &VBO);              // Generate one buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Select the buffer
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vertices,
                 GL_STATIC_DRAW); // Write data to buffer

    glEnableVertexAttribArray(0); // Enable vertex attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          0); // Define vertex attributes

    /* -------------- Setup Index Buffer ----------------- */
    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    unsigned int IBO;
    glGenBuffers(1, &IBO);                      // Generate one buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); // Select the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW); // Write data to buffer

    /* -------- Setup Vertex and Fragment Shaders ----------- */
    ShaderSource basic = readShaderSource("resources/shaders/basic");

    /* Create and load shader (program) */
    unsigned int shader =
        createShader(basic.vertex_source, basic.fragment_source);
    glUseProgram(shader);

    freeShaderSource(basic);

    /* --------------- Reset all binds --------------------- */
    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glClearColor(0.3, 0.3, 0.4, 1); // Set background color
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* ------------------- Bind ------------------------ */
        glUseProgram(shader);
        glBindVertexArray(VAO);

        /* ------------------- Draw ------------------------ */
        // glDrawArrays(GL_TRIANGLES, 0, 3); // Draw vertices (from index 0, 3
        // vectors)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
