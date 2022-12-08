#version 1.2.0

// Input vertex attributes
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

// Output vertex attributes
varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;

// Uniforms
uniform mat4 u_modelViewMatrix;
uniform mat4 u_projectionMatrix;

void main()
{
    // Compute the vertex position in screen space
    v_position = (u_modelViewMatrix * vec4(a_position, 1.0)).xyz;
    v_normal = (u_modelViewMatrix * vec4(a_normal, 0.0)).xyz;
    v_texCoord = a_texCoord;
    gl_Position = u_projectionMatrix * vec4(v_position, 1.0);
}