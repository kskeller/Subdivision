#pragma once

class HE_Texture
{
public:
	HE_Texture();
	HE_Texture(float s, float t);
	float s, t;
	HE_Texture * child;
};