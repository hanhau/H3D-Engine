#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <fstream>
#include <vector>
#include <string>
#include "../../H3D/Vector.hpp"

#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
// .md5 3D File Format Handling Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace ModelType{
		class MD5
		{
		private:
			// Vertex Class
			struct Vertex {
				Vec3<float>      normal,pos;
				Vec2<float>	     texCoord;
				int				 startWeight;
				int				 weightCount;
			};
			// Joint Class
			struct Joint {
				std::string      name;
				int				 parentIndex;
				h3d::Vec3<float> position;
				h3d::Vec3<float> orientation;
				float orientation_quaternion;
			};
			// Weight Class
			struct Weight {
				int jointID;
				float bias;
				Vec3<float> pos;
			};
			// Mesh Class
			struct Mesh {
				// Material
				std::string					texture;
				GLuint						mesh_id;

				// Storage of Vertices
				std::vector<Vertex>			vertex_vec;
				std::vector<Vec3<int>>		triangle_vec;
				std::vector<Weight>			weight_vec;

				// Buffer Vecs
				std::vector<int>			index_vec;
				std::vector<Vec2<float>>	tex_vec;
				std::vector<Vec3<float>>	position_vec;
				std::vector<Vec3<float>>    normal_vec;
			};
			
			// Data from Animations
			struct Animation
			{
			private:
				// Header Data
				int m_MD5Version;
				int m_NumFrames;
				int m_NumJoints;
				int m_Framerate;
				int m_NumAnimatedComponents;

				float m_AnimDuration;
				float m_FrameDuration;
				float m_AnimTime;

				// OpenGL Buffer


				// Joint_Info
				struct Joint_Info {
					std::string m_Name;
					int			m_ParentID;
					int			m_Flags;
					int			m_StartIndex;
				};
				// Bound
				struct Bound {
					h3d::Vec3<float> m_Min;
					h3d::Vec3<float> m_Max;
				};
				// BaseFrame
				struct BaseFrame {
					h3d::Vec3<float> m_Pos;
					h3d::Vec3<float> m_Quat_vec3;
					float		     m_Quat_w;
				};
				// FrameData
				struct FrameData {
					int				   m_FrameID;
					std::vector<float> m_FrameData;
				};
				// SkeletonJoint
				struct SkeletonJoint : public BaseFrame{
					int m_Parent;

					SkeletonJoint();
					SkeletonJoint(const BaseFrame& copy);
				};
				// FrameSkeleton
				struct FrrameSkeleton {
					std::vector<SkeletonJoint> m_Joints;
				};

				// Lists, Vecs and Buffers
				std::vector<Joint_Info>     m_JointInfos;
				std::vector<Bound>			m_Bounds;
				std::vector<BaseFrame>      m_BaseFrames;
				std::vector<FrameData>      m_Frames;
				std::vector<FrrameSkeleton> m_Skeletons;

				FrrameSkeleton              m_AnimatedSkeleton;

			public:
				bool loadFromFile(char Path[]);

				void BuildFrameskeleton(std::vector<FrrameSkeleton>&   skeletons,
										const std::vector<Joint_Info>& jointInfos,
										const std::vector<BaseFrame>&  baseFrames,
										const FrameData&			   frameData);

				void update(float delta_time);
			};
			std::vector<Animation>animation_vec;

			// Paths
			char mesh_path[24];
			char anim_path[24];

			// Container and Data
			std::vector<Joint>		joint_vec;
			unsigned int			joint_count;
			Joint 				    joint_root;
			std::vector<Mesh>	    mesh_vec;
			unsigned int			mesh_count;
			std::vector<Vec3<int>>  triangle_vec;

			// Intel
			int  md5_version;
			char commandline[50];
			
			// Preperation Functions
			bool prepareMesh(Mesh& mesh);
			bool prepareNormals(Mesh& mesh);

			// Rendering single Mesh
			void renderMesh(const Mesh &mesh);
		public:
			_declspec(dllexport) MD5();
			_declspec(dllexport)~MD5();
			
			bool _declspec(dllexport) loadFromFile(const char path[]);
			bool _declspec(dllexport) checkAnimations();

			bool _declspec(dllexport) addAnimation(char Path[]);
			
			bool _declspec(dllexport) setCurrentAnimation(char name[]);
			bool _declspec(dllexport) playAnimation();
		};
	}
}
/////////////////////////////////////////////////////////////////