#version 130

in vec3 fragColor;  // Color passed from vertex shader
out vec4 color;     // Final output color

void main() {
    // Set the final fragment color
    color = vec4(fragColor, 1.0);  // RGBA, with 1.0 for alpha (fully opaque)
}
