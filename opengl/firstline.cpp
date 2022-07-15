#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLuint createVertexBuffer() {
    GLfloat vertices[] = {0.5, 0.5, 0.0, -0.5, -0.5, 0.0};
    GLuint VBO[1];

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    return VBO[0];
}

int main() {
    if (!glfwInit()) {
        std::cout << "Error initializing glfw" << std::endl;
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(800, 800, "First Line", NULL, NULL);
    if (!window) {
        std::cout << "Error creating window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing glew" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLuint VBO = createVertexBuffer();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}