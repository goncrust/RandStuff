#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

/* Because I know I'm just going to create 1 handle I will not return GLuint* */
GLuint createVertexBuffer() {
    GLfloat vertice[] = {0.0, 0.0, 0.0};
    GLuint VBO[1];

    glGenBuffers(1, VBO);                  // Create handle
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // Bind to target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice,
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

    GLuint VBO = createVertexBuffer();

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind handle to target
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_POINTS, 0, 1);
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