#version 130

in vec3 position;  // Vertex position
out vec3 fragColor;  // Pass color to fragment shader

uniform mat4 modelViewProjection;

void main() {
    // Apply the transformation matrix to the vertex position
    gl_Position = modelViewProjection * vec4(position, 1.0);

    // Create a gradient based on the vertex position (for example, using the x, y, and z position components)
    fragColor = (position + 1.0) / 2.0;  // Normalize the position to be in the range [0,1]
}
