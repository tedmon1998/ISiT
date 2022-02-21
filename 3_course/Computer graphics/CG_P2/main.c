#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <SOIL/SOIL.h>

const GLuint WIDTH = 800, HEIGHT = 800;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


GLchar* glShaderLoad(char* path);

void glDraw()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Unbind starVAO
    glBindVertexArray(0);
}

void DrawCircle(float transX, float transY, float *pRgb, float size, GLfloat *circleVertices) {
    float points = 50;
    float x, y;

    int count = 0;
    for (float i = -1; i < points; i++) {
        x = (sin((M_PI * 2 / points) * i) / size) + transX;
        y = (cos((M_PI * 2 / points) * i) / size) + transY;
        circleVertices[count + 0] = x;
        circleVertices[count + 1] = y;
        circleVertices[count + 2] = 0.0f;
        circleVertices[count + 3] = pRgb[0];
        circleVertices[count + 4] = pRgb[1];
        circleVertices[count + 5] = pRgb[2];
        count+=6;
    }
}

void DrawSemicircleCircle(float transX, float transY, float *pRgb, float size, GLfloat *circleVertices) {
    float points = 50;
    float x, y;

    int count = 0;
    for (float i = -1; i < points; i++) {
        x = (sin((M_PI / points) * i) / size) + transX;
        y = (cos((M_PI / points) * i) / size) + transY;
        circleVertices[count + 0] = x;
        circleVertices[count + 1] = y;
        circleVertices[count + 2] = 0.0f;
        circleVertices[count + 3] = pRgb[0];
        circleVertices[count + 4] = pRgb[1];
        circleVertices[count + 5] = pRgb[2];
        count+=6;
    }
}

    int main() {
        // Init GLFW
        glfwInit();
        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Create a GLFWwindow object that we can use for GLFW's functions
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "CG_P2", NULL, NULL);
        glfwMakeContextCurrent(window);

        // Set the required callback functions
        glfwSetKeyCallback(window, key_callback);

        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;
        // Initialize GLEW to setup the OpenGL Function pointers
        glewInit();

        // Define the viewport dimensions
        glViewport(0, 0, WIDTH, HEIGHT);

        // Build and compile our shader program
        // Vertex shader
        const GLchar *vertexShaderSource = glShaderLoad("shaders/vertex.glsl");
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // Check for compile time errors
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
        }

        // Fragment shader
        const GLchar *fragmentShaderSource = glShaderLoad("shaders/fragment.glsl");
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // Check for compile time errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
        }

        // Link shaders
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // Check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        // Set up vertex data (and buffer(s)) and attribute pointers
        GLfloat backgroundVertices[] = {
                // Positions            // Colors
                1.0f, 0.783f, 0.0f, 0.83f, 0.39f, 0.21f,
                1.0f, -0.783f, 0.0f, 0.83f, 0.39f, 0.21f,
                -1.0f, -0.783f, 0.0f, 0.83f, 0.39f, 0.21f,
                -1.0f, 0.783f, 0.0f, 0.83f, 0.39f, 0.21f,
        };
        GLuint backgroundVBO, backgroundVAO;
        glGenVertexArrays(1, &backgroundVAO);
        glGenBuffers(1, &backgroundVBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(backgroundVAO);
        glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundVertices), backgroundVertices, GL_STATIC_DRAW);
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Unbind starVAO
        glBindVertexArray(0);


        // Set up vertex data (and buffer(s)) and attribute pointers
        GLfloat background2Vertices[] = {
                // Positions            // Colors
                -0.96f, 0.783f, 0.0f, 1.0f, 1.0f, 1.0f,
                -0.96f, -0.783f, 0.0f, 1.0f, 1.0f, 1.0f,
                0.96f, -0.783f, 0.0f, 1.0f, 1.0f, 1.0f,
                0.96f, 0.783f, 0.0f, 1.0f, 1.0f, 1.0f,
        };
        GLuint background2VBO, background2VAO;
        glGenVertexArrays(1, &background2VAO);
        glGenBuffers(1, &background2VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(background2VAO);
        glBindBuffer(GL_ARRAY_BUFFER, background2VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(background2Vertices), background2Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        float rgb[3] = {0.81f, 0.39f, 0.21f};
        GLfloat circleVertices[300] = {0};

        //body
        DrawCircle(0, 0, rgb, 2.5, circleVertices);


        GLuint circleVBO, circleVAO;
        glGenVertexArrays(1, &circleVAO);
        glGenBuffers(1, &circleVBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(circleVAO);
        glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        //head
        rgb[0] = 0.79f;
        rgb[1] = 0.39f;
        rgb[2] = 0.21f;
        DrawCircle(0.4, 0.3, rgb, 3.5, circleVertices);

        GLuint headVBO, headVAO;
        glGenVertexArrays(1, &headVAO);
        glGenBuffers(1, &headVBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(headVAO);
        glBindBuffer(GL_ARRAY_BUFFER, headVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        //nose
        rgb[0] = 0.15f;
        rgb[1] = 0.15f;
        rgb[2] = 0.15f;
        DrawCircle(0.4, 0.25, rgb, 34.0, circleVertices);

        GLuint noseVBO, noseVAO;
        glGenVertexArrays(1, &noseVAO);
        glGenBuffers(1, &noseVBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(noseVAO);
        glBindBuffer(GL_ARRAY_BUFFER, noseVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        //eyes
        rgb[0] = 1.0f;
        rgb[1] = 1.0f;
        rgb[2] = 1.0f;
        DrawCircle(0.5, 0.4, rgb, 16.5, circleVertices);

        GLuint eyes1VBO, eyes1VAO;
        glGenVertexArrays(1, &eyes1VAO);
        glGenBuffers(1, &eyes1VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(eyes1VAO);
        glBindBuffer(GL_ARRAY_BUFFER, eyes1VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        DrawCircle(0.3, 0.4, rgb, 16.5, circleVertices);

        GLuint eyes2VBO, eyes2VAO;
        glGenVertexArrays(1, &eyes2VAO);
        glGenBuffers(1, &eyes2VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(eyes2VAO);
        glBindBuffer(GL_ARRAY_BUFFER, eyes2VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        rgb[0] = 0.0f;
        rgb[1] = 0.0f;
        rgb[2] = 0.0f;
        DrawCircle(0.48, 0.38, rgb, 50.5, circleVertices);

        GLuint eyes3VBO, eyes3VAO;
        glGenVertexArrays(1, &eyes3VAO);
        glGenBuffers(1, &eyes3VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(eyes3VAO);
        glBindBuffer(GL_ARRAY_BUFFER, eyes3VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        DrawCircle(0.28, 0.38, rgb, 50.5, circleVertices);

        GLuint eyes4VBO, eyes4VAO;
        glGenVertexArrays(1, &eyes4VAO);
        glGenBuffers(1, &eyes4VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(eyes4VAO);
        glBindBuffer(GL_ARRAY_BUFFER, eyes4VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        rgb[0] = 1.0f;
        rgb[1] = 1.0f;
        rgb[2] = 1.0f;

        DrawCircle(0.475, 0.375, rgb, 170.5, circleVertices);

        GLuint eyes5VBO, eyes5VAO;
        glGenVertexArrays(1, &eyes5VAO);
        glGenBuffers(1, &eyes5VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(eyes5VAO);
        glBindBuffer(GL_ARRAY_BUFFER, eyes5VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        DrawCircle(0.275, 0.375, rgb, 170.5, circleVertices);

        GLuint eyes6VBO, eyes6VAO;
        glGenVertexArrays(1, &eyes6VAO);
        glGenBuffers(1, &eyes6VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(eyes6VAO);
        glBindBuffer(GL_ARRAY_BUFFER, eyes6VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        //tail
        rgb[0] = 0.87f;
        rgb[1] = 0.39f;
        rgb[2] = 0.21f;
        DrawSemicircleCircle(0.0, 0.6, rgb, 3,  circleVertices);
        GLuint tailVBO, tailVAO;
        glGenVertexArrays(1, &tailVAO);
        glGenBuffers(1, &tailVBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(tailVAO);
        glBindBuffer(GL_ARRAY_BUFFER, tailVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        //legs
        rgb[0] = 0.15f;
        rgb[1] = 0.15f;
        rgb[2] = 0.15f;
        DrawSemicircleCircle(-0.40, 0.3, rgb, 6,  circleVertices);
        GLuint legs1VBO, legs1VAO;
        glGenVertexArrays(1, &legs1VAO);
        glGenBuffers(1, &legs1VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(legs1VAO);
        glBindBuffer(GL_ARRAY_BUFFER, legs1VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        DrawSemicircleCircle(-0.40, -0.35, rgb, 6,  circleVertices);
        GLuint legs2VBO, legs2VAO;
        glGenVertexArrays(1, &legs2VAO);
        glGenBuffers(1, &legs2VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(legs2VAO);
        glBindBuffer(GL_ARRAY_BUFFER, legs2VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        rgb[0] = 0.0f;
        rgb[1] = 0.0f;
        rgb[2] = 0.0f;
        DrawSemicircleCircle(-0.5, 0.15, rgb, 6,  circleVertices);
        GLuint legs3VBO, legs3VAO;
        glGenVertexArrays(1, &legs3VAO);
        glGenBuffers(1, &legs3VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(legs3VAO);
        glBindBuffer(GL_ARRAY_BUFFER, legs3VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        DrawSemicircleCircle(-0.45, -0.25, rgb, 6,  circleVertices);
        GLuint legs4VBO, legs4VAO;
        glGenVertexArrays(1, &legs4VAO);
        glGenBuffers(1, &legs4VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(legs4VAO);
        glBindBuffer(GL_ARRAY_BUFFER, legs4VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        //ears
        GLfloat earsVertices[] = {
                // Positions            // Colors
                0.4f, 0.625f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.4f, 0.47f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.5f, 0.475f, 0.0f, 0.15f, 0.15f, 0.15f,
        };

        GLuint earsVBO, earsVAO;
        glGenVertexArrays(1, &earsVAO);
        glGenBuffers(1, &earsVBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(earsVAO);
        glBindBuffer(GL_ARRAY_BUFFER, earsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(earsVertices), earsVertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        GLfloat ears2Vertices[] = {
                // Positions            // Colors
                0.35f, 0.64f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.45f, 0.79f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.45f, 0.635f, 0.0f, 0.15f, 0.15f, 0.15f,
        };

        GLuint ears2VBO, ears2VAO;
        glGenVertexArrays(1, &ears2VAO);
        glGenBuffers(1, &ears2VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(ears2VAO);
        glBindBuffer(GL_ARRAY_BUFFER, ears2VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ears2Vertices), ears2Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();

        // strips
        GLfloat strips1Vertices[] = {
                // Positions            // Colors
                0.0f, 0.4f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.1f, 0.395f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.05f, 0.05f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint strips1VBO, strips1VAO;
        glGenVertexArrays(1, &strips1VAO);
        glGenBuffers(1, &strips1VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(strips1VAO);
        glBindBuffer(GL_ARRAY_BUFFER, strips1VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(strips1Vertices), strips1Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------
        GLfloat strips2Vertices[] = {
                // Positions            // Colors
                0.0f, 0.4f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.1f, 0.395f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.05f, 0.05f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint strips2VBO, strips2VAO;
        glGenVertexArrays(1, &strips2VAO);
        glGenBuffers(1, &strips2VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(strips2VAO);
        glBindBuffer(GL_ARRAY_BUFFER, strips2VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(strips2Vertices), strips2Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------
        GLfloat strips3Vertices[] = {
                // Positions            // Colors
                0.05f, 0.4f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.15f, 0.38f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.1f, 0.05f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint strips3VBO, strips3VAO;
        glGenVertexArrays(1, &strips3VAO);
        glGenBuffers(1, &strips3VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(strips3VAO);
        glBindBuffer(GL_ARRAY_BUFFER, strips3VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(strips3Vertices), strips3Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------

        GLfloat strips4Vertices[] = {
                // Positions            // Colors
                -0.5f, 0.675f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.6f, 0.66f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.55f, 0.45f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint strips4VBO, strips4VAO;
        glGenVertexArrays(1, &strips4VAO);
        glGenBuffers(1, &strips4VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(strips4VAO);
        glBindBuffer(GL_ARRAY_BUFFER, strips4VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(strips4Vertices), strips4Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------
        GLfloat strips5Vertices[] = {
                // Positions            // Colors
                -0.65f, 0.33f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.75f, 0.305f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.65f, 0.1f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint strips5VBO, strips5VAO;
        glGenVertexArrays(1, &strips5VAO);
        glGenBuffers(1, &strips5VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(strips5VAO);
        glBindBuffer(GL_ARRAY_BUFFER, strips5VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(strips5Vertices), strips5Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------
        GLfloat strips6Vertices[] = {
                // Positions            // Colors
                -0.55f, 0.18f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.65f, 0.17f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.55f, -0.05f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint strips6VBO, strips6VAO;
        glGenVertexArrays(1, &strips6VAO);
        glGenBuffers(1, &strips6VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(strips6VAO);
        glBindBuffer(GL_ARRAY_BUFFER, strips6VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(strips6Vertices), strips6Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();


        // mustache
        GLfloat mustache1Vertices[] = {
                // Positions            // Colors
                0.1f, 0.13f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.1f, 0.15f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.8f, 0.15f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.8f, 0.13f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint mustache1VBO, mustache1VAO;
        glGenVertexArrays(1, &mustache1VAO);
        glGenBuffers(1, &mustache1VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(mustache1VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mustache1VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mustache1Vertices), mustache1Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------
        GLfloat mustache2Vertices[] = {
                // Positions            // Colors
                -0.0f, 0.33f, 0.0f, 0.15f, 0.15f, 0.15f,
                -0.0f, 0.35f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.7f, 0.35f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.7f, 0.33f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint mustache2VBO, mustache2VAO;
        glGenVertexArrays(1, &mustache2VAO);
        glGenBuffers(1, &mustache2VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(mustache2VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mustache2VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mustache2Vertices), mustache2Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();
        // ---------------------------------------------------------------------------------------------------
        GLfloat mustache3Vertices[] = {
                // Positions            // Colors
                0.05f, 0.245f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.05f, 0.265f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.75f, 0.265f, 0.0f, 0.15f, 0.15f, 0.15f,
                0.75f, 0.245f, 0.0f, 0.15f, 0.15f, 0.15f,
        };
        GLuint mustache3VBO, mustache3VAO;
        glGenVertexArrays(1, &mustache3VAO);
        glGenBuffers(1, &mustache3VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(mustache3VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mustache3VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mustache3Vertices), mustache3Vertices, GL_STATIC_DRAW);
        // Position attribute
        glDraw();



        // Game loop
        while (!glfwWindowShouldClose(window)) {
            // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
            glfwPollEvents();

            // Render
            // Clear the colorbuffer
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            glUseProgram(shaderProgram);
            GLint translationLocation = glGetUniformLocation(shaderProgram, "translation");
            GLint scaleLocation = glGetUniformLocation(shaderProgram, "scale");
            GLint angleLocation = glGetUniformLocation(shaderProgram, "angle");
            glUniform3f(translationLocation, 0.0f, 0.0f, 0.0f);
            glUniform3f(scaleLocation, 1.0f, 1.0f, 1.0f);
            glUniform1f(angleLocation, 0.0f * M_PI);

            // Draw background
            glBindVertexArray(backgroundVAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindVertexArray(0);

            // Draw the constellation
            glBindVertexArray(background2VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(circleVAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(headVAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(noseVAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(eyes1VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(eyes2VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(eyes3VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(eyes4VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(eyes5VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glBindVertexArray(eyes6VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glUniform1f(angleLocation, 1.3f);
            glBindVertexArray(tailVAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            // Draw the constellation
            glUniform1f(angleLocation, 1.5f);
            glBindVertexArray(legs1VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            glUniform1f(angleLocation, 1.5f);
            glBindVertexArray(legs2VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            glUniform1f(angleLocation, 1.5f);
            glBindVertexArray(legs3VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            glUniform1f(angleLocation, 1.4f);
            glBindVertexArray(legs4VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
            glBindVertexArray(0);
            //ears
            glUniform1f(angleLocation, 0.25f);
            glBindVertexArray(earsVAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);
            glUniform1f(angleLocation, -0.15f);
            glBindVertexArray(ears2VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);
            //strips
            glUniform1f(angleLocation, 0.35f);
            glBindVertexArray(strips1VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);

            glUniform1f(angleLocation, 0.65f);
            glBindVertexArray(strips2VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);

            glUniform1f(angleLocation, 0.12f);
            glBindVertexArray(strips3VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);
            //----------------------------------

            glUniform1f(angleLocation, 0.33f);
            glBindVertexArray(strips4VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);

            glUniform1f(angleLocation, -0.265f);
            glBindVertexArray(strips5VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);

            glUniform1f(angleLocation, -0.54f);
            glBindVertexArray(strips6VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
            glBindVertexArray(0);

            //mustache
            glUniform1f(angleLocation, 0.25f);
            glBindVertexArray(mustache1VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindVertexArray(0);
            glUniform1f(angleLocation, -0.25f);
            glBindVertexArray(mustache2VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindVertexArray(0);
            glUniform1f(angleLocation, 0.0f);
            glBindVertexArray(mustache3VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindVertexArray(0);


            // Swap the screen buffers
            glfwSwapBuffers(window);
        }
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &backgroundVAO);
        glDeleteBuffers(1, &backgroundVBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &background2VAO);
        glDeleteBuffers(1, &background2VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &circleVAO);
        glDeleteBuffers(1, &circleVBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &headVAO);
        glDeleteBuffers(1, &headVBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &noseVAO);
        glDeleteBuffers(1, &noseVBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &eyes1VAO);
        glDeleteBuffers(1, &eyes1VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &eyes2VAO);
        glDeleteBuffers(1, &eyes2VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &eyes3VAO);
        glDeleteBuffers(1, &eyes3VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &eyes4VAO);
        glDeleteBuffers(1, &eyes4VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &eyes5VAO);
        glDeleteBuffers(1, &eyes5VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &eyes6VAO);
        glDeleteBuffers(1, &eyes6VBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &tailVAO);
        glDeleteBuffers(1, &tailVBO);
        // Properly de-allocate all resources once they've outlived their purpose
        glDeleteVertexArrays(1, &legs1VAO);
        glDeleteBuffers(1, &legs1VBO);
        glDeleteVertexArrays(1, &legs2VAO);
        glDeleteBuffers(1, &legs2VBO);
        glDeleteVertexArrays(1, &legs3VAO);
        glDeleteBuffers(1, &legs3VBO);
        glDeleteVertexArrays(1, &legs4VAO);
        glDeleteBuffers(1, &legs4VBO);
        //ears
        glDeleteVertexArrays(1, &earsVAO);
        glDeleteBuffers(1, &earsVBO);
        glDeleteVertexArrays(1, &ears2VAO);
        glDeleteBuffers(1, &ears2VBO);
        //strips
        glDeleteVertexArrays(1, &strips1VAO);
        glDeleteBuffers(1, &strips1VBO);
        glDeleteVertexArrays(1, &strips2VAO);
        glDeleteBuffers(1, &strips2VBO);
        glDeleteVertexArrays(1, &strips3VAO);
        glDeleteBuffers(1, &strips3VBO);

        glDeleteVertexArrays(1, &strips4VAO);
        glDeleteBuffers(1, &strips4VBO);
        glDeleteVertexArrays(1, &strips5VAO);
        glDeleteBuffers(1, &strips5VBO);
        glDeleteVertexArrays(1, &strips6VAO);
        glDeleteBuffers(1, &strips6VBO);

        // mustache
        glDeleteVertexArrays(1, &mustache1VAO);
        glDeleteBuffers(1, &mustache1VBO);
        glDeleteVertexArrays(1, &mustache2VAO);
        glDeleteBuffers(1, &mustache2VBO);
        glDeleteVertexArrays(1, &mustache3VAO);
        glDeleteBuffers(1, &mustache3VBO);


        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate();
        return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    glfwSetWindowSize(window, 600, 600);
}

//Параметры, с которыми производились расчеты, лежат в заголовочном файле
//нужно возращать ошибку!
GLchar*
glShaderLoad(char* path)
{
    GLchar*shaderSource = NULL;

    int descriptor = open(path, O_RDONLY);

    if (descriptor != -1) {
        FILE *file = fdopen(descriptor, "rb");

        if (file) {
            struct stat statistics;

            if (fstat(descriptor, &statistics) != -1) {
                shaderSource = (GLchar*)malloc(statistics.st_size);
                fread(shaderSource, sizeof(char), statistics.st_size, file);
            }
            fclose(file);
        }
        close(descriptor);
    }
    printf("%s\n", path);
    printf("%s\n", shaderSource);
    return shaderSource;
}