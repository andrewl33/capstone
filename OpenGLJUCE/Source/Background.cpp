/*
  ==============================================================================

    Background.cpp
    Created: 17 Nov 2019 11:25:29am
    Author:  Andrew Lee

  ==============================================================================
*/

#include "Background.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
//==============================================================================
BackgroundComponent::BackgroundComponent()
{
    shader_program_source = parse_shaders();
    openGL_context.setOpenGLVersionRequired(juce::OpenGLContext::openGL3_2);
    openGL_context.setRenderer(this);
    openGL_context.setContinuousRepainting(true);
    
    // Benchmarking-only
    setPaintingIsUnclipped(true);
    setOpaque(true);
    init_button();
    startTimerHz(software_fps_requested);
    
    setSize(screen_resolution.x, screen_resolution.y);
    
    
    r = Random();
    // Fill pair array
    for (auto i = 0; i < blobCount; ++i)
    {
        blobState.push_back(std::make_pair(std::vector<float>{0.0, 0.0, 0.0, 0.0}, std::vector<float>{0.0, 0.0, 0.0, 0.0}));
        curState.push_back(std::vector<float>{0.0,0.0,0.0,0.0});
    }

    createNextState();
    copyNextToCurState();
    translate(0);

    startTimer(1000 / updatePerSecond);
}

BackgroundComponent::~BackgroundComponent()
{
    openGL_context.detach();
}
void BackgroundComponent::newOpenGLContextCreated()
{
    // Create the shader program and specify the CPU-computed variables (uniforms) required for animation.
    shader_prog_ID = create_program(shader_program_source);
    GL::glUseProgram(shader_prog_ID);
    
    // The resolution is static, computed at app initialization, and thus can afford to be sent just once here.
    uf_resolution = GL::glGetUniformLocation(shader_prog_ID, "resolution");
    GL::glUniform2f(uf_resolution, screen_resolution.x, screen_resolution.y);

    // The distance variable is dynamic, and thus is only declared here.
    // Sending it to the GPU is deferred as it must be computed and sent at each draw call.
    uf_distance = GL::glGetUniformLocation(shader_prog_ID, "distance");
    
    // Explicitly generate a vertex array (rather than use the default created one) to specify the vertex buffer layout in each draw call.
    // Otherwise, using the default requires that each draw call must bind the vertex buffer, enable the attrib array, and specify the attrib pointers.
    GL::glGenVertexArrays(1, &vertex_arr_ID);
    GL::glBindVertexArray(vertex_arr_ID);
    
    // Load the (x, y) positions (which are just the corners of the screen), into a static area of GPU memory.
    GL::glGenBuffers(1, &vertex_buff_ID);
    GL::glBindBuffer(GL_ARRAY_BUFFER, vertex_buff_ID);
    GL::glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions_count, positions, GL_STATIC_DRAW);
    
    // Specify the attribute layout of the currently bound vertex buffer object (there's only one attribute - position).
    // The currently instantiated vertex array object will use this specification for each draw call.
    GL::glEnableVertexAttribArray(pos_attrib_id);
    GL::glVertexAttribPointer(pos_attrib_id, num_floats_per_pos_attrib, GL_FLOAT, GL_FALSE,
                              sizeof(GLfloat) * num_floats_per_pos_attrib, (const void*)0);     // For more that one attrib, can use a struct with a C++ macro to determine this void* offset.

    // Specify which (x, y) positions are used to draw two triangles in the shape of a rectangle (the screen) using the positions in the currently bound vertex buffer object.
    GL::glGenBuffers(1, &index_buff_ID);
    GL::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buff_ID);
    GL::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements_count, elements, GL_STATIC_DRAW);
    
    // No need to unbind the array, buffer, or shader program thanks to JUCE.
}
void BackgroundComponent::renderOpenGL()
{
    // Bind shader program and send the CPU-computed distance variable (it needs for this frame) for animation.
    GL::glUseProgram(shader_prog_ID);
    const auto distance = std::abs(std::sin(Time::currentTimeMillis() / 1000.) * screen_resolution.y * 2);
    GL::glUniform1f(uf_distance, distance / 2);
        // Binding the array simultaneously tells the GPU which vertex buffer to use as well as the specification of the buffer's memory layout.
    GL::glBindVertexArray(vertex_arr_ID);
    
    // The element (or index) buffer is still required to be bound at each draw call to specify how to use the positions in the buffer to draw the correct shape.
    GL::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buff_ID);
    glDrawElements(GL_TRIANGLES, elements_count, GL_UNSIGNED_INT, nullptr);
    // Benchmark the software renderer against the OpenGL renderer
    time_frames();
}
void BackgroundComponent::openGLContextClosing()
{   // Destroying GL objects require that the openGL_context is not yet destroyed, i.e. cannot delete in the destructor.
    GL::glDeleteProgram(shader_prog_ID);
    GL::glDeleteBuffers(1, &vertex_buff_ID);
    GL::glDeleteBuffers(1, &index_buff_ID);
}
void BackgroundComponent::paint(Graphics& g)
{
    if (! openGL_context.isAttached()) {
        const auto bounds = getLocalBounds().toFloat();
        g.setColour(Colours::black);
        g.fillRect(bounds);
        g.setColour(Colours::red);

        for (int i = 0; i < blobState.size(); i++)
        {
            g.fillEllipse(curState[i][0], curState[i][1], curState[i][2], curState[i][3]);
        }
    }
}
void BackgroundComponent::resized()
{
    openGL_button.setBoundsRelative(0.f, 0.f, 0.1f, 0.1f);
}
void BackgroundComponent::timerCallback()
{
    if (transitionCounter++ > translateTimeHz + pauseTimeHz) {
        copyNextToCurState();
        createNextState();
        transitionCounter = 0;
    }
    else if (transitionCounter > translateTimeHz) {
        return;
    }
    translate((transitionCounter/(float)translateTimeHz));
    repaint();
}
BackgroundComponent::ShaderProgramSource BackgroundComponent::parse_shaders()
{
    return { String::createStringFromData(BinaryData::Vert_vert, BinaryData::Vert_vertSize), String::createStringFromData(BinaryData::Frag_frag, BinaryData::Frag_fragSize) };
}
GLuint BackgroundComponent::create_shader(const GLenum type, const GLchar* source, const GLint source_length)
{
    const auto shID = GL::glCreateShader(type);
    GL::glShaderSource(shID, 1, &source, &source_length);
    GL::glCompileShader(shID);
    
    // Check shader compilation success
    GLint success;
    GL::glGetShaderiv(shID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        GL::glGetShaderInfoLog(shID, 512, nullptr, infoLog);
        DBG(infoLog);
        jassertfalse;
    }
    return shID;
}
GLuint BackgroundComponent::create_program(const ShaderProgramSource& source)
{
    const auto vxID = create_shader(GL_VERTEX_SHADER, source.VertexSource.getCharPointer(),
                                    sizeof(GLchar) * source.VertexSource.length());
    const auto fsID = create_shader(GL_FRAGMENT_SHADER, source.FragmentSource.getCharPointer(),
                                    sizeof(GLchar) * source.FragmentSource.length());
    const auto spID = GL::glCreateProgram();
    GL::glAttachShader(spID, vxID);
    GL::glAttachShader(spID, fsID);
    GL::glLinkProgram(spID);
    
    // Check program linking success
    GLint success;
    GL::glGetProgramiv(spID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        GL::glGetProgramInfoLog(spID, 512, nullptr, infoLog);
        DBG(infoLog);
        jassertfalse;
    }
    GL::glDeleteShader(vxID);
    GL::glDeleteShader(fsID);
    return spID;
}
void BackgroundComponent::init_button()
{
    addAndMakeVisible(openGL_button);
    auto&& laf = getLookAndFeel();
    laf.setColour(TextButton::buttonColourId, Colours::black);
    laf.setColour(TextButton::buttonOnColourId, Colours::black);
    laf.setColour(TextButton::textColourOnId, Colours::limegreen);
    laf.setColour(TextButton::textColourOffId, Colours::white);

    openGL_button.setClickingTogglesState(true);
    openGL_button.onClick = [this] {
        if (openGL_button.getToggleState()) {
            stopTimer();
            openGL_context.attachTo(*this);
        }
        else {
            openGL_context.detach();
            startTimerHz(software_fps_requested);
        }
    };
}
void BackgroundComponent::time_frames()
{
    const auto current_time = Time::currentTimeMillis();
    frame_count++;
    if (current_time - prev_time >= 1000. ){
        frame_time = 1000. / frame_count;
        DBG(String::formatted("%f ms/frame", frame_time));
        frame_count = 0;
        prev_time = current_time;
    }
}

void BackgroundComponent::createNextState()
{
    auto padding = 70;
    auto height = getBounds().getHeight() - padding;
    auto width = getBounds().getWidth() - padding;
    auto midpoint = width / 2 + padding / 2;
    auto difference = width - midpoint - padding / 2;
    auto circleMaxDim = 80;
    auto circleMinDim = 5;

    for (int i = 0; i < blobState.size(); i+=2)
    {
        auto x = r.nextFloat() * difference;
        auto y = r.nextFloat() * height + padding / 2;
        auto dim = (r.nextFloat() * (circleMaxDim - circleMinDim)) + circleMinDim;

        auto& left = blobState[i].second;
        auto& right = blobState[(int64)i + (int64)1].second;

        left[0] = midpoint + x - dim / 2;
        left[1] = y - dim / 2;
        left[2] = dim;
        left[3] = dim;

        right[0] = midpoint - x - dim / 2;
        right[1] = y - dim / 2;
        right[2] = dim;
        right[3] = dim;
    }
}

void BackgroundComponent::copyNextToCurState()
{
    for (int i = 0; i < blobState.size(); ++i)
    {
        auto& oldState = blobState[i].first;
        auto& newState = blobState[i].second;

        for (int j = 0; j < oldState.size(); j++)
        {
            oldState[j] = newState[j];
        }
    }
}


void BackgroundComponent::translate(float progress)
{

    for (int i = 0; i < blobState.size(); i++)
    {
        auto from = blobState[i].first;
        auto to = blobState[i].second;

        // Create a new distance between points
        //auto distance = sqrt(pow((to[0] - from[0]), 2.0) + pow((to[1] - from[1]), 2.0));
        auto boxSize = to[2] - from[2];


        curState[i][0] = from[0] +  progress * (float)((double)to[0] - from[0]);
        
        curState[i][1] = from[1] +  progress * (float)((double)to[1] - from[1]);
        curState[i][2] = curState[i][3] = progress * boxSize + from[2];
    }
}

