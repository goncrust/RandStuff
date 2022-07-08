#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void loadShaderSource(unsigned int id, const std::string &source) {
    const char *shader_src[] = {&source[0]};

    glShaderSource(id, 1, shader_src, NULL); // Load source code
    glCompileShader(id); // Compile
    
    /* Check and print compilation errors */
    int error;
    glGetShaderiv(id, GL_COMPILE_STATUS, &error); // Check if errors occurred
    if (error == GL_FALSE) {
        std::cout << "Error compiling shader:" << std::endl;

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); // Get error log legth

        char *error_message = (char*) malloc(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, error_message); // Get actual error message

        std::cout << error_message << std::endl; // print

        free(error_message);

        // TODO: handle error
    }
}

unsigned int createShader(const std::string &vertexShader,
        const std::string &fragmentShader) {
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
    glValidateProgram(program); // Validate (result will be stored as part of the
                                // program object's state)

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

int main(void) {
    GLFWwindow *window;

    /* Initialize glfw */
    if (!glfwInit())
        return -1;

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

    /* -------------- Setup Vertex Buffers ----------------- */
    float vertices[] = {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5};

    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id);              // Generate one buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id); // Select the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW); // Write data to buffer

    glEnableVertexAttribArray(0); // Enable vertex attribute array
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); // Define vertex attributes

    /* Vertex shader source code */
    std::string vertexShader = 
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;"
        "void main() {"
        "   gl_Position = position;"
        "}";

    /* Fragment shader source code */
    std::string fragmentShader = 
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;"
        "void main() {"
        "   color = vec4(1.0, 0.0, 0.0, 0.1);"
        "}";

    /* Create and load shader (program) */
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* ------------------- Draw ------------------------ */
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw vertices (from 0 to third)

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
