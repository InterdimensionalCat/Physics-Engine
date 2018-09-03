#pragma once
struct MassData
{
public:
	MassData();
	~MassData();
	float mass;
	float inv_mass;

	// For rotations (not covered in this article)
	float inertia;
	float inverse_inertia;
};

