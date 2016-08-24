#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <..\H3D\Vector.hpp>
#include <..\H3D\Color.hpp>
#include <..\H3D\Texture.hpp>
#include <..\H3D\Shader.hpp>
#include <..\H3D\Program.hpp>
#include <gl\glew.h>
#include <vector>
#include <queue>
#include <math.h>
/////////////////////////////////////////////////////////////////
// Particle System for Particle Simulation
/////////////////////////////////////////////////////////////////
namespace h3d { // Part of H3D
	namespace PE {
		class Emitter;			// Emmits particles
		class ParticleBase;			// Base class of a particle
		class ParticleLib;		// 
		class ParticleUpdater;  // Updates Particles provided by Emitters
		class ParticleRenderer;	// For effective rendering
		/////////////////////////////////////////////////////////
		// Contains a type of a particle and emmits them
		class Emitter
		{
			friend ParticleUpdater;
		private:
			// Buffers for Shaders
			GLuint m_ssPositions;
			GLuint m_ssSpeed;
			GLuint m_ssColor;
			GLuint m_ssSize;

			
			// Emitter settings
			float m_gravity;
			int   m_particleType;

			// List of particles
			unsigned long m_particleCount;
			//std::vector<Particle> m_particleVec;
		public:
			// Setup 
			H3D_API Emitter();
			H3D_API ~Emitter();

			// Comparing containing particle type
			bool H3D_API operator<(Emitter& emitter);

			// Upload arrays to gpu
			bool H3D_API uploadDataToGPU();
		};
		/////////////////////////////////////////////////////////
		// Base class for a particle
		class ParticleBase
		{
			friend ParticleUpdater;
		private:
			h3d::Vec3<float>  m_pos;
			h3d::Vec3<float>  m_speed;
			h3d::Color<float> m_color;
			float             m_size;
			float             m_lifetime;
			int               m_type;
		public:
			H3D_API static int getID();
		};
		/////////////////////////////////////////////////////////
		// extensible particles
		namespace Particle
		{
			class Normal : public ParticleBase
			{
			private:

			public:

			};
			class PointSprite : public ParticleBase
			{
			private:

			public:

			};
		}
		/////////////////////////////////////////////////////////
		// Contains every avaliable Particle (wich is not a point)
		class ParticleLib
		{
		private:
			
		public:
			
		};
		/////////////////////////////////////////////////////////
		// Updates Particles efficently
		class ParticleUpdater
		{
		private:
			// Compute Shader Stuff
			h3d::Program m_program;
			h3d::Shader  m_computeShader;
			GLuint m_particleBuffers[2];
			h3d::Vec3<int> m_maxWorkerCount;
			h3d::Vec3<int> m_maxWorkerSize;

			// Computing type
			// 0 = computing shader
			// 1 = cpu shader
			int m_computingType;

			// Emitter queue
			std::priority_queue<h3d::PE::Emitter> m_EmitterQueue;
		public:
			// Setup
			H3D_API ParticleUpdater();
			H3D_API ~ParticleUpdater();

			// Add Emitter to the queue
			void H3D_API addToQueue(const h3d::PE::Emitter& emitter);

			// Clear the update queue
			void H3D_API clearQueue();

			// Update all Emitters
			void H3D_API update();
		};
		/////////////////////////////////////////////////////////
		// GPU Rendering
		class ParticleRenderer
		{
		private:
			// Shader routine
			h3d::Program m_program;
			h3d::Shader  m_vertexShader;
			h3d::Shader  m_fragmentShader;

			// Queue of Emitters
			std::queue<Emitter> m_emitterQueue;

			// Reference to ParticleLib
			ParticleLib &m_particleLib;
		public:
			// Setup
			H3D_API ParticleRenderer();
			H3D_API ~ParticleRenderer();

			// render all
			void H3D_API render();
		};
	}
}
/////////////////////////////////////////////////////////////////
