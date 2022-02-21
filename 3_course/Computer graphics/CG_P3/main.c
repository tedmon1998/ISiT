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


const int WIDTH = 960, HEIGHT = 540;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

GLchar *glShaderLoad(char *path, int *length);

void getShader(GLuint *shader, char *path, int typeShader);

void getShaderProgram(GLuint *shaderProgram, int n, ...);

void glDrawT()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid *) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid *) (6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Unbind planetVBO
    glBindVertexArray(0);
}

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

void DrawCircleT(float transX, float transY, float *pRgb, float size, GLfloat *circleVertices, float tX, float tY) {
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
        circleVertices[count + 6] = (x+tX)*(size/2.5);
        circleVertices[count + 7] = (y+tY)*(size/2.5);
        count+=8;
    }
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

void DrawSemicircleCircleT(float transX, float transY, float *pRgb, float size, GLfloat *circleVertices, float tX, float tY) {
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
        circleVertices[count + 6] = (x+tX)*(size/2.5);
        circleVertices[count + 7] = (y+tY)*(size/2.5);
        count+=8;
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

int main()
{
    // Init GLFW
    if (!glfwInit())
        exit(EXIT_FAILURE);
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFW window object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "CG_P3", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, keyCallback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to set up the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    GLuint vertexShader;
    getShader(&vertexShader, "shaders/vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader;
    getShader(&fragmentShader, "shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    GLuint shaderProgram;
    getShaderProgram(&shaderProgram, 2, &vertexShader, &fragmentShader);

    GLfloat planets[] = {
            // Positions          // Colors           // Texture Coords
            1.f, 1.f, 0.0f, 1.0f, 1.0f, 1.0f, 1.f, 0.f, // Top Right
            1.f, -1.f, 0.0f, 1.0f, 1.0f, 1.0f, 1.f, 1.f, // Bottom Right
            -1.f, -1.f, 0.0f, 1.0f, 1.0f, 1.0f, 0.f, 1.f, // Bottom Left
            -1.f, 1.f, 0.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, // Top Left
    };

    GLuint planetVBO, planetVAO;
    glGenVertexArrays(1, &planetVAO);
    glGenBuffers(1, &planetVBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(planetVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planetVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planets), planets, GL_STATIC_DRAW);
    // Position attribute
    glDrawT();


    // Load and create a texture
    GLuint planetTexture;
    glGenTextures(1, &planetTexture);
    glBindTexture(GL_TEXTURE_2D,
                  planetTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    int width, height;
    unsigned char *image = SOIL_load_image("textures/planets.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentally mess up our texture.

    // ---------------------------------------Body---------------------------------------------------------------------
    float rgb[3] = {0.81f, 0.39f, 0.21f};
    GLfloat circleVertices[410] = {0};

    //body
    DrawCircleT(0, 0, rgb, 2.5, circleVertices, 0.5, 0.5);


    GLuint circleVBO, circleVAO;
    glGenVertexArrays(1, &circleVAO);
    glGenBuffers(1, &circleVBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(circleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    // Position attribute
    glDrawT();

    GLuint circleTexture;
    glGenTextures(1, &circleTexture);
    glBindTexture(GL_TEXTURE_2D,
                  circleTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    image = SOIL_load_image("textures/window_star.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentally mess up our texture.

    // ----------------------------------------HEAD--------------------------------------------------------------

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

    // -------------------------------------------NOSE---------------------------------------------------------------
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
    // -------------------------------------------EYES---------------------------------------------------------------
    rgb[0] = 1.0f;
    rgb[1] = 1.0f;
    rgb[2] = 1.0f;
    DrawCircleT(0.5, 0.4, rgb, 16.5, circleVertices,0.485, 0.59);

    GLuint eyes1VBO, eyes1VAO;
    glGenVertexArrays(1, &eyes1VAO);
    glGenBuffers(1, &eyes1VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(eyes1VAO);
    glBindBuffer(GL_ARRAY_BUFFER, eyes1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    // Position attribute
    glDrawT();

    GLuint eyes1Texture;
    glGenTextures(1, &eyes1Texture);
    glBindTexture(GL_TEXTURE_2D,
                  eyes1Texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    image = SOIL_load_image("textures/eyes.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentally mess up our texture.

    rgb[0] = 1.0f;
    rgb[1] = 1.0f;
    rgb[2] = 1.0f;

    DrawCircleT(0.3, 0.4, rgb, 16.5, circleVertices,0.385, 0.59);

    GLuint eyes2VBO, eyes2VAO;
    glGenVertexArrays(1, &eyes2VAO);
    glGenBuffers(1, &eyes2VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(eyes2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, eyes2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    // Position attribute
    glDrawT();

    GLuint eyes2Texture;
    glGenTextures(1, &eyes2Texture);
    glBindTexture(GL_TEXTURE_2D,
                  eyes2Texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    image = SOIL_load_image("textures/eyes.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentally mess up our texture.
    // -------------------------------------------TAIL---------------------------------------------------------------
    rgb[0] = 0.87f;
    rgb[1] = 0.39f;
    rgb[2] = 0.21f;
    DrawSemicircleCircleT(0.0, 0.6, rgb, 3,  circleVertices, 0.3, 0.65);
    GLuint tailVBO, tailVAO;
    glGenVertexArrays(1, &tailVAO);
    glGenBuffers(1, &tailVBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(tailVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tailVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    // Position attribute
    glDrawT();

    GLuint tailTexture;
    glGenTextures(1, &tailTexture);
    glBindTexture(GL_TEXTURE_2D,
                  tailTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    image = SOIL_load_image("textures/tail.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentally mess up our texture.
    // -------------------------------------------LEGS---------------------------------------------------------------
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
    // -------------------------------------------EARS---------------------------------------------------------------
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
    // -------------------------------------------MUSTACHE---------------------------------------------------------------
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
    // --------------------------------------------------------------------------------------------------------------

    // FPS-related variables (Frame per second)
    const double FPS = 1.0/30.0;
    register double startTime = glfwGetTime(), currentTime = 0;
    // SRR-related variables (Screen refresh rate)
    const double SRR = 2.0;
    register double endTime = 0.0, deltaTime = 0.0;
    register int frameCount = 0;

    float starMove = 0;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Update time delay according to FPS
        do
        {
            currentTime = glfwGetTime();
        } while (currentTime - startTime < FPS);
        startTime = currentTime;

        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        // Render
        // Clear the colourful
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        GLint translationLocation = glGetUniformLocation(shaderProgram, "translation");
        GLint scaleLocation = glGetUniformLocation(shaderProgram, "scale");
        GLint angleLocation = glGetUniformLocation(shaderProgram, "angle");

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, planetTexture);

        glUniform3f(translationLocation, 0.0f, 0.0f, 0.0f);
        glUniform3f(scaleLocation, 1.0f, 1.0f, 1.0f);
        glUniform1f(angleLocation, 0.0f*M_PI);

        glBindVertexArray(planetVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, circleTexture);
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
        glBindVertexArray(0);

        glBindVertexArray(headVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
        glBindVertexArray(0);
        // Draw the constellation
        glBindVertexArray(noseVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
        glBindVertexArray(0);
        // Draw the constellation
        glBindTexture(GL_TEXTURE_2D, eyes1Texture);
        glBindVertexArray(eyes1VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, eyes2Texture);
        glBindVertexArray(eyes2VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
        glBindVertexArray(0);
        // Draw the constellation
        glUniform1f(angleLocation, 1.3f);
        glBindTexture(GL_TEXTURE_2D, tailTexture);
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

        // Bind Texture

        glUniform3f(translationLocation, 0.6f, -0.3f, 0.0f);
        glUniform3f(scaleLocation, 0.3f, 0.3f, 1.0f);
        glUniform1f(angleLocation, 0.25f*M_PI);


        starMove += 0.001f;
        glUniform3f(translationLocation, 0.8f - starMove, 0.7f, 0.0f);
        glUniform3f(scaleLocation, 0.1f, 0.1f, 1.0f);
        glUniform1f(angleLocation, 0.6f*M_PI);


        // Swap the screen buffers
        glfwSwapBuffers(window);

        // Message update time delay according to SRR
        frameCount++;
        deltaTime += glfwGetTime() - startTime;
        if (startTime - endTime > SRR)
        {
            printf("setFPS: %5.2f \trealFPS: %5.2f \tframeTime: %5.8f\n",
                   1.0/FPS, frameCount/(startTime - endTime), deltaTime/frameCount);
            endTime = startTime;
            deltaTime = 0;
            frameCount = 0;
        }



    }

    // Properly de-allocate all resources once they've outlived their purpose
    // 1. VAO, VBO and IBO
    glDeleteVertexArrays(1, &planetVAO);
    glDeleteBuffers(1, &planetVBO);

    glDeleteVertexArrays(1, &circleVAO);
    glDeleteBuffers(1, &circleVBO);

    glDeleteVertexArrays(1, &headVAO);
    glDeleteBuffers(1, &headVBO);
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &noseVAO);
    glDeleteBuffers(1, &noseVBO);
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &eyes1VAO);
    glDeleteBuffers(1, &eyes1VBO);
    glDeleteVertexArrays(1, &eyes2VAO);
    glDeleteBuffers(1, &eyes2VBO);
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

    // mustache
    glDeleteVertexArrays(1, &mustache1VAO);
    glDeleteBuffers(1, &mustache1VBO);
    glDeleteVertexArrays(1, &mustache2VAO);
    glDeleteBuffers(1, &mustache2VBO);
    glDeleteVertexArrays(1, &mustache3VAO);
    glDeleteBuffers(1, &mustache3VBO);

    // 2. Textures
    glDeleteTextures(1, &planetTexture);
    glDeleteTextures(1, &circleTexture);
    glDeleteTextures(1, &eyes1Texture);
    glDeleteTextures(1, &eyes2Texture);
    glDeleteTextures(1, &tailTexture);
    // 3. Shader Program
    glDeleteProgram(shaderProgram);
    // 4. Terminate GLFW, clearing any resources allocated by GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    glfwSetWindowSize(window, WIDTH, HEIGHT);
}

//Параметры, с которыми производились расчеты, лежат в заголовочном файле
//нужно возращать ошибку!
GLchar *
glShaderLoad(char *path, int *length)
{
    GLchar *shaderSource = NULL;
    int descriptor = open(path, O_RDONLY);
    if (descriptor != -1)
    {
        FILE *file = fdopen(descriptor, "rb");
        if (file)
        {
            struct stat statistics;
            if (fstat(descriptor, &statistics) != -1)
            {
                shaderSource = (GLchar *) malloc(statistics.st_size);
                fread(shaderSource, sizeof(char), statistics.st_size, file);
                *length = (statistics.st_size);
            }
            fclose(file);
        }
        close(descriptor);
    }
//    printf("%s\n", path);
//    printf("%s\n", shaderSource);
    return shaderSource;
}


void
getShader(GLuint *shader, char *path, int typeShader)
{
    // Build and compile our shader program
    // Shader
    GLint length = 0;
    const GLchar *shaderSource = glShaderLoad(path, &length);
    *shader = glCreateShader(typeShader);
    glShaderSource(*shader, 1, &shaderSource, &length);
    glCompileShader(*shader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }
}

void
getShaderProgram(GLuint *shaderProgram, int n, ...)
{
    // Link shaders
    *shaderProgram = glCreateProgram();

    va_list argPtr;
    va_start(argPtr, n);
    for (int i = 0; i < n; ++i)
    {
        GLuint *shader = va_arg(argPtr, GLuint *);
        glAttachShader(*shaderProgram, *shader);
    }
    va_end(argPtr);
    glLinkProgram(*shaderProgram);

    GLint success;
    GLchar infoLog[512];
    // Check for linking errors
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    va_start(argPtr, n);
    for (int i = 0; i < n; ++i)
    {
        GLuint *shader = va_arg(argPtr, GLuint *);
        glDeleteShader(*shader);
    }
    va_end(argPtr);
}