/*
  ==============================================================================

    BackgroundComponent.h
    Created: 17 Nov 2019 11:20:13am
    Author:  Andrew Lee

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
using GL = juce::OpenGLExtensionFunctions;
class BackgroundComponent:   public Component,
                    public OpenGLRenderer,
                    public Timer
{
public:
    BackgroundComponent();
    ~BackgroundComponent();
    
    // Open methods
    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;
    void paint(Graphics &g) override;
    void resized() override;
    void timerCallback() override;
    
    
private:
    struct ShaderProgramSource
    {
        String VertexSource;
        String FragmentSource;
    };
    //==============================================================================

    // OpenGL
    OpenGLContext openGL_context;
    ShaderProgramSource shader_program_source;
    Point<int> screen_resolution { 800, 600 };
    
    GLuint vertex_arr_ID, vertex_buff_ID, index_buff_ID, shader_prog_ID;
    GLint uf_distance, uf_resolution;
    
    static constexpr int positions_count = 8;
    GLfloat positions[positions_count] = {
       -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
    };
    
    static constexpr int elements_count = 6;
    GLuint elements[elements_count] = {
        0, 1, 2,
        0, 2, 3
    };
    // "Position" vertex attribute parameters
    static constexpr int pos_attrib_id = 0;
    static constexpr int num_floats_per_pos_attrib = 2;

    // Benchmark-only
    TextButton openGL_button{ "OpenGL" };
    double prev_time{}, frame_time{};
    int frame_count{}, software_fps_requested = 200; // Try to max out repaint speed.
    
    //==============================================================================

    static ShaderProgramSource parse_shaders();
    static GLuint create_shader(const GLenum type, const GLchar* source, const GLint source_length);
    static GLuint create_program(const ShaderProgramSource& source);
    void init_button();
    void time_frames();
    
    
    // blobState
    void createNextState();
    void copyNextToCurState();
    void translate(float elapsed);
    Random r;
    int blobCount = 150; // Has to be divisible by 2
    std::vector<std::pair<std::vector<float>, std::vector<float>>> blobState; // now, before<x loc, y loc, size, size>
    std::vector<std::vector<float>> curState; // x offset, x loc, y loc, size, size
    int translateTimeHz = 180; // hz it takes for blobs to travel from one state to next
    int updatePerSecond = 60;
    int pauseTimeHz = 2 * 60;
    int transitionCounter = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackgroundComponent)
};
