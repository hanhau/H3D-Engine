#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Graphics/Color.hpp"
#include "../../H3D/Graphics/Texture.hpp"
#include "../../H3D/Graphics/Shader.hpp"
#include "../../H3D/Graphics/Program.hpp"
#include <vector>
#include <queue>
#include <math.h>

#include <GL/glew.h>
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
			class impl;
			std::unique_ptr<impl> m_impl;
		public:
			// Setup 
			H3D_API Emitter();
			H3D_API ~Emitter();
			
			static const int MaxParticle = 128 * 128;

			enum class Type {
				Spot,Quad,Line
			};

			enum class FadeType {
				Sin,Cos,Linear
			};

			void H3D_API create(h3d::Vec3<float> pos,
								int particle_count,
								Type type,bool gravity,
								h3d::Vec3<float> size,
								float strength);

			void H3D_API setParticle(h3d::Texture& tex,
									 h3d::Vec3<float> size,
									 float fadetime,FadeType ftype,
									 h3d::Color<GLfloat> col);

			void H3D_API update(float deltaTime);
			void H3D_API render();
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
		// Contains every avaliable Particle (which is not a point)
		class tagParticleLib
		{
		private:
			tagParticleLib();
		public:
			~tagParticleLib();

			static tagParticleLib& GetInstance()
			{
			#ifdef DLL_EXPORT
				typedef tagParticleLib* (*GetPLibFn)();
				HMODULE mod = GetModuleHandle(NULL);
				GetPLibFn getPLib = (GetPLibFn)::GetProcAddress(mod, "GetPLib");
				tagParticleLib* Instance = getPLib();
				return *Instance;
			#else
				static tagParticleLib Instance;
				return Instance;
			#endif
			}
		};
		#define ParticleLib tagParticleLib::GetInstance()
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
			void H3D_API addToQueue(h3d::PE::Emitter& emitter);

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
