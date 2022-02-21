#include <cstdio>
#include <string>
#include <vector>

#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"


const int WIDTH = 800, HEIGHT = 600;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

GLchar *glShaderLoad(const char *path, int *length);
void getShader(GLuint *shader, const char *path, int typeShader);
void getShaderProgram(GLuint *shaderProgram, int n, ...);


// Class template using macros
#define DEFINE_GL_ARRAY_HELPER(name, gen, del)                                 \
  struct name : public std::vector<GLuint> {                                   \
    name(size_t n) : std::vector<GLuint>(n) { gen(n, data()); }                \
    ~name() { del(size(), data()); }                                           \
  };

// These objects use similar interface
DEFINE_GL_ARRAY_HELPER(Buffers, glGenBuffers, glDeleteBuffers)
DEFINE_GL_ARRAY_HELPER(VertexArrays, glGenVertexArrays, glDeleteVertexArrays)
DEFINE_GL_ARRAY_HELPER(Textures, glGenTextures, glDeleteTextures)
DEFINE_GL_ARRAY_HELPER(Framebuffers, glGenFramebuffers, glDeleteFramebuffers)



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
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "CG_P4", nullptr, nullptr);
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

    GLuint vertexShader, fragmentShader;
    getShader(&vertexShader, "shaders/s1_vert.glsl", GL_VERTEX_SHADER);
    getShader(&fragmentShader, "shaders/s1_frag.glsl", GL_FRAGMENT_SHADER);
    GLuint mainProgram;
    getShaderProgram(&mainProgram, 2, &vertexShader, &fragmentShader);

    getShader(&vertexShader, "shaders/s2_vert.glsl", GL_VERTEX_SHADER);
    getShader(&fragmentShader, "shaders/s2_frag.glsl", GL_FRAGMENT_SHADER);
    GLuint postProgram;
    getShaderProgram(&postProgram, 2, &vertexShader, &fragmentShader);


  Buffers buffers(3);
  VertexArrays vertexArrays(2);
  Textures textures(2);
  Framebuffers framebuffers(1);
  GLint attribLocation;

  glBindVertexArray(vertexArrays[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
  {
    GLfloat fillTriangle[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        3.0f,  -1.0f, 2.0f, 0.0f,
        -1.0f, 3.0f,  0.0f, 2.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(fillTriangle), fillTriangle, GL_STATIC_DRAW);
  }
  attribLocation = glGetAttribLocation(postProgram, "vertexPosition");
  glEnableVertexAttribArray(attribLocation);
  glVertexAttribPointer(attribLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

  attribLocation = glGetAttribLocation(postProgram, "vertexTextureCoords");
  glEnableVertexAttribArray(attribLocation);
  glVertexAttribPointer(attribLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));

  glBindVertexArray(vertexArrays[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

  GLuint indexCount;
  {
    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile("models/Chest.obj", aiProcess_Triangulate);
    const aiMesh *mesh = scene->mMeshes[0];
    glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * 3 * sizeof(GLfloat),
                 mesh->mVertices, GL_STATIC_DRAW);
    std::vector<GLuint> indices;
    for (int i = 0; i < mesh->mNumFaces; ++i)
      for (int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
        indices.push_back(mesh->mFaces[i].mIndices[j]);
    indexCount = indices.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);
  }
  attribLocation = glGetAttribLocation(mainProgram, "vertexPosition");
  glEnableVertexAttribArray(attribLocation);
  glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  const int MAX_WIDTH = 4096;
  const int MAX_HEIGHT = 4096;
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MAX_WIDTH, MAX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, MAX_WIDTH, MAX_HEIGHT, 0,
               GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[0], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textures[1], 0);
  GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(sizeof(drawBuffers) / sizeof(drawBuffers[0]), drawBuffers);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glBindVertexArray(vertexArrays[1]);
  glUseProgram(postProgram);
  glUniform1i(glGetUniformLocation(postProgram, "renderTexture"), 0);
  glUniform1i(glGetUniformLocation(postProgram, "depthTexture"), 1);
  glUniform2f(glGetUniformLocation(postProgram, "reverseMaxSize"), 1.0f / MAX_WIDTH, 1.0f / MAX_HEIGHT);
  glUseProgram(0);
  glBindVertexArray(0);


  GLint ulMatModel = glGetUniformLocation(mainProgram, "matModel");
  GLint ulMatView = glGetUniformLocation(mainProgram, "matView");
  GLint ulMatProjection = glGetUniformLocation(mainProgram, "matProjection");
  GLint ulTextureScale = glGetUniformLocation(postProgram, "textureScale");
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.875f, 0.875f, 0.875f, 0.0f);

  while (!glfwWindowShouldClose(window))
  {
      glfwPollEvents();

      int framebufferWidth, framebufferHeight;
      glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
      glViewport(0, 0, framebufferWidth, framebufferHeight);

      glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glBindVertexArray(vertexArrays[0]);
      glUseProgram(mainProgram);

      float angle = 0.5f * glfwGetTime();

      glm::mat4 matModel(1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

      matModel= glm::rotate(matModel, angle,glm::vec3(0,1,0));

      glm::vec3 camera_position(0.0, 0.0, -0.1);
      glm::vec3 camera_target(0, 0.0, 0);
      glm::vec3 n = glm::normalize(camera_position - camera_target);
      glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
      glm::vec3 u = glm::normalize(glm::cross(n, camera_up));
      glm::vec3 v = glm::normalize(glm::cross(u, n));

      glm::mat4 matView = glm::mat4 (
                        u.x, v.x, n.x, 0.0f,
                        u.y, v.y, n.y, 0.0f,
                        u.z, v.z, n.z, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);
      matView *= glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           -camera_position.x, -camera_position.y, -camera_position.z, 1.0f);

      glm::mat4 matProjection(1.0f);
      matProjection[2][3]=0.09f;
      glm::mat4 matOrtho=glm::ortho(-2.f,2.f,-2.f,6.f,-2.f,2.f);
      matProjection=matOrtho*matProjection;

      glUniformMatrix4fv(ulMatModel, 1, GL_FALSE, &matModel[0][0]);
      glUniformMatrix4fv(ulMatView, 1, GL_FALSE, &matView[0][0]);
      glUniformMatrix4fv(ulMatProjection, 1, GL_FALSE, &matProjection[0][0]);

      glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glBindTexture(GL_TEXTURE_2D, textures[0]);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, textures[1]);
      glBindVertexArray(vertexArrays[1]);
      glUseProgram(postProgram);
      glUniform2f(ulTextureScale,
                  1.0f * framebufferWidth / MAX_WIDTH,
                  1.0f * framebufferHeight / MAX_HEIGHT);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      
      glBindTexture(GL_TEXTURE_2D, 0);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, 0);

      glfwSwapBuffers(window);
  }

  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    glfwSetWindowSize(window, WIDTH, HEIGHT);
}

GLchar *
glShaderLoad(const char *path, int *length)
{
    GLchar *shaderSource = nullptr;
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
getShader(GLuint *shader, const char *path, int typeShader)
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
        glGetShaderInfoLog(*shader, 512, nullptr, infoLog);
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
        glGetProgramInfoLog(*shaderProgram, 512, nullptr, infoLog);
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