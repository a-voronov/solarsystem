//Adam Coffman 
//Particle System Class
////////////////////////////////////////////////////////////////////////
//This Class is used to represent the particle system. It contains 
//an array of particle structs. Each with their own translation from the
//origin, azimuth, and zenith, as well as velocities and lifetimes.
//An array was a better choice than a linked list here as there are
//always a constant number of particles (when one dies, it is immediately
//replaced by another) and we do not need to perform sorted insertions
//and deletions.
/////////////////////////////////////////////////////////////////////////
#pragma once



const int NUMBER_OF_PARTICLES = 800;
const float MAX_ROTATION = 360;
const float MIN_ROTATION = 0;
const float MIN_TRANS = .005;
const float MAX_TRANS = .03;
const float MIN_DELTA_ROTATION = 0.5;
const float MAX_DELTA_ROTATION = 3.0;
const float MIN_DELTA_SURFACE = .005;
const float MAX_DELTA_SURFACE = .01;
const int MIN_LIFETIME = 10;
const int MAX_LIFETIME = 25;
const int DELTA_LIFETIME = 1;


struct Particle{
		//Used For Randomizing The Initial Position of the Particle
		float azimuthRoation, zenithRotation, surfaceTranslationFactor;

		//Used For Randomizing The Delta or Change In Position of Each Particle
		float deltaAz, deltaZe, deltaSurface;

		//Lifetime In "Refreshes"
		int lifetime;
};
		
class ParticleSystem{
	
	public: 
		//Gets the next particle in the array
		Particle getNextParticle();
		//Modify all particles by their deltas, destroy old ones and create new ones
		//if the lifetime is 0
		void updateAll();
		int getNumberOfParticles();
		ParticleSystem();


	private:
		//Marker used by getNextParticle to keep track of position.
		int currentParticle;

		//Array of all particle structs
		Particle particles[NUMBER_OF_PARTICLES];

	  //This is your random number generator from the last program
		float generateRandomNumber(float lower, float upper);
		
		//Get a new Particle struct with new randomized values.
		Particle generateNewParticle();

};
