#version 1.2.0

// Input fragment attributes
varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;

// Output fragment attributes
out vec4 o_color;

// Uniforms
uniform vec3 u_lightDirection;
uniform vec4 u_diffuseColor;
uniform vec4 u_shadowColor;

void main()
{
    // Compute the diffuse lighting
    float diffuse = max(dot(normalize(v_normal), normalize(u_lightDirection)), 0.0);
    vec4 color = u_diffuseColor * diffuse;

    // Compute the shadow
    float shadow = clamp((1.0 + dot(v_normal, u_lightDirection)) / 2.0, 0.0, 1.0);
    color = mix(color, u_shadowColor, shadow);

    o_color = color;
}