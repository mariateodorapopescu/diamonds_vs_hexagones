#version 330

// Input
in vec3 frag_position;
in vec3 frag_color;
in vec3 frag_normal;
in vec2 frag_texture;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    out_color = vec4(frag_color, 1);
    // Alternativ, puteți utiliza o culoare bazată pe normala obiectului
    // out_color = vec4(normalize(frag_normal), 1);
}
