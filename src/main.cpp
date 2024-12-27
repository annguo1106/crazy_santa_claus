#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "header/cube.h"
#include "header/object.h"
#include "header/shader.h"
#include "header/stb_image.h"

#define DEFAULT 0
#define BOMB 1
#define BOMB_RANDOM 2
#define COLORBALL 3
#define SNOWBALL 4

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
unsigned int loadCubemap(std::vector<string> &mFileName);

struct material_t{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float gloss;
};
struct light_t{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
struct model_t{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    Object* object;
};
struct camera_t{
    glm::vec3 position;
    glm::vec3 up;
    float rotationY;
};

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

// cube map 
unsigned int cubemapTexture;
unsigned int cubemapVAO, cubemapVBO;

// shader programs 
int shaderProgramIndex = 1;
std::vector<shader_program_t*> shaderPrograms;
shader_program_t* cubemapShader;

// additional dependencies
light_t light;
material_t material;
camera_t camera;
model_t tree;
model_t colorball;
model_t snowball;

// model matrix
glm::mat4 cameraModel;
glm::mat4 treeModel;
glm::mat4 colorballModel;
glm::mat4 snowballModel;

// update's variables
float timing = 0;
float time_countdown = 0.0001;
bool tree_IsRotate = true;
glm::vec3 explosionCenter(0.0f, 0.0f, 0.0f);
float angleSpeed = 0.1f;
float rotationAngle = 0;
float treeRotateDegree = 0.5f;

int colorball_amount = 1000;
int snowball_amount = 500;

float colorball_radius = 50.0f;
float colorball_offset = 10.0f;

float snowball_radius = 50.0f;
float snowball_offset = 25.0f;
float snowball_heaven = 50;
float snowball_ground = 0;
float* verticalSpeeds;
float lastFrameTime = 0.0f;

glm::mat4* snowballMatrices;
glm::mat4* colorballMatrices;

// frame control
float tree_render_duration = 2.5;
float colorball_render_duration = 3;
float snowball_render_duration = 3;

//////////////////////////////////////////////////////////////////////////
// Parameter setup, 
// You can change any of the settings if you want

void camera_setup(){
    camera.position = glm::vec3(0.0, 20.0, 100.0);
    camera.up = glm::vec3(0.0, 1.0, 0.0);
    camera.rotationY = 0;
}

void light_setup(){
    light.position = glm::vec3(0.0, 1000.0, 0.0);
    light.ambient = glm::vec3(1.0);
    light.diffuse = glm::vec3(1.0);
    light.specular = glm::vec3(1.0);
}

void material_setup(){
    material.ambient = glm::vec3(0.2);
    material.diffuse = glm::vec3(1.0);
    material.specular = glm::vec3(0.7);
    material.gloss = 10.5;
}
//////////////////////////////////////////////////////////////////////////

void tree_setup(){

// Load the object and texture for each model here 

#if defined(__linux__) || defined(__APPLE__)
    std::string objDir = "../../src/asset/obj/";
    std::string textureDir = "../../src/asset/texture/";
#else
    std::string objDir = "..\\..\\src\\asset\\obj\\";
    std::string textureDir = "..\\..\\src\\asset\\texture\\";
#endif
    treeModel = glm::mat4(1.0f);

    tree.position = glm::vec3(0, -10, 0);
    tree.scale = glm::vec3(1, 1, 1);
    tree.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    tree.object = new Object(objDir + "tree.obj");
    tree.object->load_to_buffer();
    tree.object->load_texture(textureDir + "tree.jpg");
}

void colorball_setup(){

// Load the object and texture for each model here 

#if defined(__linux__) || defined(__APPLE__)
    std::string objDir = "../../src/asset/obj/";
    std::string textureDir = "../../src/asset/texture/";
#else
    std::string objDir = "..\\..\\src\\asset\\obj\\";
    std::string textureDir = "..\\..\\src\\asset\\texture\\";
#endif
    colorballModel = glm::mat4(1.0f);

    colorball.position = glm::vec3(0, -10, 0);
    colorball.scale = glm::vec3(1, 1, 1);
    colorball.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    colorball.object = new Object(objDir + "earth.obj");
    colorball.object->load_to_buffer();
    colorball.object->load_texture(textureDir + "helicopter_red.jpg");
}

void snowball_setup(){

// Load the object and texture for each model here 

#if defined(__linux__) || defined(__APPLE__)
    std::string objDir = "../../src/asset/obj/";
    std::string textureDir = "../../src/asset/texture/";
#else
    std::string objDir = "..\\..\\src\\asset\\obj\\";
    std::string textureDir = "..\\..\\src\\asset\\texture\\";
#endif
    snowballModel = glm::mat4(1.0f);

    snowball.position = glm::vec3(0, -10, 0);
    snowball.scale = glm::vec3(1, 1, 1);
    snowball.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    snowball.object = new Object(objDir + "earth.obj");
    snowball.object->load_to_buffer();
    snowball.object->load_texture(textureDir + "helicopter_red.jpg");
}

void shader_setup(){

// Setup the shader program for each shading method

#if defined(__linux__) || defined(__APPLE__)
    std::string shaderDir = "../../src/shaders/";
#else
    std::string shaderDir = "..\\..\\src\\shaders\\";
#endif

    std::vector<std::string> shadingMethod = {
        "default",                              // default shading
        "bomb", "bomb_random",                  // bomb shading
        "colorball",                            // colorball shading
        "snowball"                              // snowball shading
    };

    for(int i=0; i<shadingMethod.size(); i++){
        std::string vpath = shaderDir + shadingMethod[i] + ".vert";
        std::string gpath = shaderDir + shadingMethod[i] + ".geom";
        std::string fpath = shaderDir + shadingMethod[i] + ".frag";

        shader_program_t* shaderProgram = new shader_program_t();
        shaderProgram->create();
        shaderProgram->add_shader(vpath, GL_VERTEX_SHADER);
        shaderProgram->add_shader(gpath, GL_GEOMETRY_SHADER);
        shaderProgram->add_shader(fpath, GL_FRAGMENT_SHADER);
        shaderProgram->link_shader();
        shaderPrograms.push_back(shaderProgram);
    } 
}

void cubemap_setup(){

// Setup all the necessary things for cubemap rendering
// Including: cubemap texture, shader program, VAO, VBO

#if defined(__linux__) || defined(__APPLE__)
    std::string cubemapDir = "../../src/asset/texture/skybox/";
    std::string shaderDir = "../../src/shaders/";
#else
    std::string cubemapDir = "..\\..\\src\\asset\\texture\\skybox\\";
    std::string shaderDir = "..\\..\\src\\shaders\\";
#endif

    // setup texture for cubemap
    std::vector<std::string> faces
    {
        cubemapDir + "right.jpg",
        cubemapDir + "left.jpg",
        cubemapDir + "top.jpg",
        cubemapDir + "bottom.jpg",
        cubemapDir + "front.jpg",
        cubemapDir + "back.jpg"
    };
    cubemapTexture = loadCubemap(faces);   

    // setup shader for cubemap
    std::string vpath = shaderDir + "cubemap.vert";
    std::string fpath = shaderDir + "cubemap.frag";
    
    cubemapShader = new shader_program_t();
    cubemapShader->create();
    cubemapShader->add_shader(vpath, GL_VERTEX_SHADER);
    cubemapShader->add_shader(fpath, GL_FRAGMENT_SHADER);
    cubemapShader->link_shader();

    glGenVertexArrays(1, &cubemapVAO);
    glGenBuffers(1, &cubemapVBO);
    glBindVertexArray(cubemapVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubemapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubemapVertices), &cubemapVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}

void setup(){

    // Initialize shader model camera light material
    light_setup();
    tree_setup();
    colorball_setup();
    snowball_setup();
    shader_setup();
    camera_setup();
    cubemap_setup();
    material_setup();

    // Enable depth test, face culling ...
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Debug: enable for debugging
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback([](  GLenum source, GLenum type, GLuint id, GLenum severity, 
    //                             GLsizei length, const GLchar* message, const void* userParam) {

    // std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") 
    //           << "type = " << type 
    //           << ", severity = " << severity 
    //           << ", message = " << message << std::endl;
    // }, nullptr);
}

glm::mat4* colorballMatrices_generate(int amount) {
    float radius = colorball_radius;
    float offset = colorball_offset;

    glm::mat4* particleMatrices = new glm::mat4[amount];
    for (int i = 0; i < amount; ++i) {
        float angle = (float)i / (float)amount * 360.0f + rotationAngle;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;

        float x = sin(glm::radians(angle)) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.2f;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(glm::radians(angle)) * radius + displacement;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, z));

        float scale = (rand() % 20) / 300.0f + 0.05f;
        model = glm::scale(model, glm::vec3(scale));

        float rotAngle = (rand() % 360);
        model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0.4f, 0.6f, 0.8f));

        particleMatrices[i] = model;
    }
    return particleMatrices;
}

glm::mat4* snowballMatrices_generate(int amount) {
    float radius = snowball_radius;
    float offset = snowball_offset;
    float initialHeight = snowball_heaven;
    float groundLevel = snowball_ground;

    glm::mat4* particleMatrices = new glm::mat4[amount];
    verticalSpeeds = new float[amount];
    for (int i = 0; i < amount; i++) verticalSpeeds[i] = (rand() % 50) / 100.0f + 0.5f;
    // for (int i = 0; i < amount; i++) verticalSpeeds[i] = 10;
    for (int i = 0; i < amount; i++) {
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;

        float x = sin(glm::radians(angle)) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = initialHeight;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(glm::radians(angle)) * radius + displacement;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, z));
        float scale = (rand() % 20) / 300.0f + 0.05f;
        model = glm::scale(model, glm::vec3(scale));
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0.4f, 0.6f, 0.8f));

        particleMatrices[i] = model;
    }
    return particleMatrices;
}

void snowball_update(float deltaTime) {
    float initialHeight = snowball_heaven;
    float groundLevel = snowball_ground;

    for (int i = 0; i < snowball_amount; i++) {
        glm::vec3 position = glm::vec3(snowballMatrices[i][3]);
        position.y -= verticalSpeeds[i] * deltaTime;

        if (position.y <= groundLevel) {
            // printf("position.y <= groundLevel\n");
            position.y = initialHeight;
            
            float angle = (float)i / (float)snowball_amount * 360.0f;
            float radius = snowball_radius;
            float offset = snowball_offset;
            float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            
            position.x = sin(glm::radians(angle)) * radius + displacement;
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            position.z = cos(glm::radians(angle)) * radius + displacement;
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);

        float scale = (rand() % 20) / 300.0f + 0.05f;
        model = glm::scale(model, glm::vec3(scale));

        float rotAngle = (rand() % 360);
        model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0.4f, 0.6f, 0.8f));

        snowballMatrices[i] = model;
    } 
}

void update(){
    
// Update the heicopter position, camera position, rotation, etc.
    camera.rotationY = (camera.rotationY > 360.0) ? 0.0 : camera.rotationY;
    cameraModel = glm::mat4(1.0f);
    cameraModel = glm::rotate(cameraModel, glm::radians(camera.rotationY), camera.up);
    cameraModel = glm::translate(cameraModel, camera.position);

    // tree bomb time counter update
    timing += 0.005;
    time_countdown = (timing > 100 || (time_countdown != 0 && time_countdown < 4)) ? time_countdown + 0.01 : 0;
    timing = (time_countdown != 0) ? 0 : timing;

    // colorball rotate update
    colorball.rotation.y = (1) ? colorball.rotation.y + 10 : colorball.rotation.y;
    colorball.rotation.y = (colorball.rotation.y > 360.0) ? 0 : colorball.rotation.y;
    colorballModel = glm::mat4(1.0f);
    colorballModel = glm::scale(colorballModel, colorball.scale);
    colorballModel = glm::rotate(colorballModel, glm::radians(colorball.rotation.y), glm::vec3(0, 1, 0));
    colorballModel = glm::translate(colorballModel, colorball.position);

    // tree rotate update
    treeRotateDegree = max(0.5, time_countdown * time_countdown * 3.0);
    tree.rotation.y = (tree_IsRotate && time_countdown) ? tree.rotation.y + treeRotateDegree : tree.rotation.y;
    tree.rotation.y = (tree.rotation.y > 360.0) ? 0 : tree.rotation.y;
    treeModel = glm::mat4(1.0f);
    treeModel = glm::rotate(treeModel, glm::radians(tree.rotation.y), glm::vec3(0, 1, 0));
    treeModel = glm::scale(treeModel, tree.scale);
    treeModel = glm::translate(treeModel, tree.position);

    // colorball update
    /*rotationAngle = glfwGetTime() * angleSpeed;
    if (colorballMatrices) {
        for (int i = 0; i < colorball_amount; ++i) {
            float angle = (float)i / (float)colorball_amount * 360.0f + rotationAngle;
            float x = sin(glm::radians(angle)) * colorball_radius;
            float z = cos(glm::radians(angle)) * colorball_radius;

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x, 0.0f, z));
            model = glm::scale(model, glm::vec3(0.1f));
            float rotAngle = (rand() % 360);
            model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0.4f, 0.6f, 0.8f));

            colorballMatrices[i] = model;
        }
    }*/

    // snowball update
    float deltaTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();
    if (snowballMatrices) snowball_update(deltaTime * 4);
}

void render(){
    srand(glfwGetTime());
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate view, projection matrix
    glm::mat4 view = glm::lookAt(glm::vec3(cameraModel[3]), glm::vec3(0.0), camera.up);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

    // Default tree render
    shaderPrograms[DEFAULT]->use();
    shaderPrograms[DEFAULT]->set_uniform_value("model", treeModel);
    shaderPrograms[DEFAULT]->set_uniform_value("view", view);
    shaderPrograms[DEFAULT]->set_uniform_value("projection", projection);
    shaderPrograms[DEFAULT]->set_uniform_value("timing", timing);
    glUniform3fv(glGetUniformLocation(DEFAULT, "explosionCenter"), 1, glm::value_ptr(explosionCenter));
    if (timing < tree_render_duration) tree.object->render();
    shaderPrograms[DEFAULT]->release();

    // Bomb tree render
    shaderPrograms[BOMB_RANDOM]->use();
    shaderPrograms[BOMB_RANDOM]->set_uniform_value("model", treeModel);
    shaderPrograms[BOMB_RANDOM]->set_uniform_value("view", view);
    shaderPrograms[BOMB_RANDOM]->set_uniform_value("projection", projection);
    shaderPrograms[BOMB_RANDOM]->set_uniform_value("timing", timing);
    glUniform3fv(glGetUniformLocation(BOMB_RANDOM, "explosionCenter"), 1, glm::value_ptr(explosionCenter));
    for (int _ = 0; _ < 6; _++) {
        float angle = 5 * _;
        auto subtreeModel = glm::rotate(treeModel, glm::radians(angle), glm::vec3(0, 1, 0));
        shaderPrograms[BOMB_RANDOM]->set_uniform_value("model", subtreeModel);
        if (timing < tree_render_duration) tree.object->render();
    }
    shaderPrograms[BOMB_RANDOM]->release();

    // Colorball render
    // if (colorballMatrices) delete[] colorballMatrices;
    colorballMatrices = colorballMatrices_generate(colorball_amount);
    shaderPrograms[COLORBALL]->use();
    shaderPrograms[COLORBALL]->set_uniform_value("view", view);
    shaderPrograms[COLORBALL]->set_uniform_value("projection", projection);

    for (int i = 0; i < colorball_amount; i++) {
        float rand1 = rand() % 100 / 100.0f;
        float rand2 = rand() % 100 / 100.0f;
        float rand3 = rand() % 100 / 100.0f;
        shaderPrograms[COLORBALL]->set_uniform_value("model", colorballMatrices[i]);
        shaderPrograms[COLORBALL]->set_uniform_value("rand1", rand1);
        shaderPrograms[COLORBALL]->set_uniform_value("rand2", rand2);
        shaderPrograms[COLORBALL]->set_uniform_value("rand3", rand3);
        if (timing < colorball_render_duration) colorball.object->render();
    }
    shaderPrograms[COLORBALL]->release();

    // Snowball render
    // if (snowballMatrices) delete[] snowballMatrices;
    if (!snowballMatrices) snowballMatrices = snowballMatrices_generate(snowball_amount);
    shaderPrograms[SNOWBALL]->use();
    shaderPrograms[SNOWBALL]->set_uniform_value("view", view);
    shaderPrograms[SNOWBALL]->set_uniform_value("projection", projection);

    for (int i = 0; i < snowball_amount; i++){
        float rand1 = rand() % 100 / 100.0f;
        float rand2 = rand() % 100 / 100.0f;
        float rand3 = rand() % 100 / 100.0f;
        shaderPrograms[SNOWBALL]->set_uniform_value("model", snowballMatrices[i]);
        shaderPrograms[SNOWBALL]->set_uniform_value("rand1", rand1);
        shaderPrograms[SNOWBALL]->set_uniform_value("rand2", rand2);
        shaderPrograms[SNOWBALL]->set_uniform_value("rand3", rand3);
        if (timing < snowball_render_duration) snowball.object->render();
    }
    shaderPrograms[SNOWBALL]->release();

    /*// cubemap
    // glm::mat4 cubemapView = glm::mat4(glm::mat3(view));
    // glm::mat4 cubemapProjection = projection;

    // cubemapShader->use();
    // cubemapShader->set_uniform_value("view", cubemapView);
    // cubemapShader->set_uniform_value("projection", cubemapProjection);

    // glBindVertexArray(cubemapVAO);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // glBindVertexArray(0);

    // cubemapShader->release();
    */
}

int main() {
    
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Crazy Santa Claus", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set viewport
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Setup texture, model, shader ...e.t.c
    setup();
    
    // Render loop, main logic can be found in update, render function
    while (!glfwWindowShouldClose(window)) {
        update(); 
        render(); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Add key callback
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    // The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.
    // Events with GLFW_PRESS and GLFW_RELEASE actions are emitted for every key press.
    // Most keys will also emit events with GLFW_REPEAT actions while a key is held down.
    // https://www.glfw.org/docs/3.3/input_guide.html

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // shader program selection
    if (key == GLFW_KEY_R && (action == GLFW_REPEAT || action == GLFW_PRESS)) 
        tree_IsRotate = !tree_IsRotate;

    if (key == GLFW_KEY_1 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        timing = 0;
        time_countdown = 0.0001;
    }

    // camera movement
    float cameraSpeed = 0.5f;
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.position.z -= 10.0;
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.position.z += 10.0;
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.rotationY -= 10.0;
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
        camera.rotationY += 10.0;
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

// Loading cubemap texture
unsigned int loadCubemap(vector<std::string>& faces){

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture;
}  
