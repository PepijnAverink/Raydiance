#include "./pch.h"
#include "./graphics/RHI/resource/shader/shader_asset.h"


// Core includes
#include "./core/files/byte_stream.h"


// Graphics includes
#include "./graphics/gfx/render_backend.h"
#include "./graphics/RHI/resource/shader/compiler/DXC/RHI_DXC_shader_compiler.h"


// Util includes
#include "./util/hash_util.h"


namespace Raydiance
{
	namespace Graphics
	{
		Result ShaderAsset::CreateEmpty(std::shared_ptr<ShaderAsset>& _asset)
		{
			_asset = std::make_unique<ShaderAsset>();
			_asset->m_UUID = UUID();

			return Result::RESULT_GOOD;
		}


		Result ShaderAsset::Load(const FilePath& _filepath, std::shared_ptr<ShaderAsset>& _asset)
		{
			return Result::RESULT_GOOD;
		}


		Result ShaderAsset::Save()
		{
			// Generate filepath based on UUID - hash
			FilePath filepath = FilePath("./assets/" + to_hex_mix2((uint64)m_UUID) + ".rash");


			// File VERSION(1, 0, 0, 0)
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// Shader Format Version   - 4 bytes
			// File Size			   - 8 bytes
			// 						   
			// Engine Version		   - 4 bytes
			// Byte order			   - 1 byte
			// Encryption  Type		   - 1 byte
			// Hash Type			   - 1 byte
			// Compression Type		   - 1 byte
			// Compression Size		   - 8 bytes
			// 						   
			// Dependency  Count	   - 4 bytes
			// Checksum (CRC32)		   - 4 bytes			
			// UUID					   - 8 bytes
			// --------------------------------- + 
			//					        48 bytes


			// ... BOX (... ... box)
			// MAGIC ID: '....'
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// box Format Version      - 4 bytes
			// File Size			   - 8 bytes
			// Flags				   - 4 bytes
			// --------------------------------- + 
			//					        20 bytes


			// Initialize the stream
			// -----------------------------------------------------------------------
			ByteStream  stream = ByteStream(filepath, ByteStreamState::BYTE_STREAM_STATE_WRITE);
			uint64 streamBegin = stream.GetPosition();


			// Write file header
			// ----------------------------------------------------------------------
			{
				// Magic number
				stream.Write_char('R');
				stream.Write_char('A');
				stream.Write_char('S');
				stream.Write_char('H');


				// Get the (version)ID of the current scene data strucuture 
				stream.Write_uint32(SHADER_ASSET_ACTIVE_VERSION.GetVersionID());
				stream.Write_uint64(0); // Skip size for now


				// TODO:: implement the rest of the file header
				// Skip the rest of the header for now.
				stream.Skip(32);
			}


			// SHDR BOX (Shader info box)
			// SHDR BOX VERSION(1, 0, 0, 0)
			// MAGIC ID: 'SHDR'
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// box Format Version      - 4 bytes
			// Box Size				   - 8 bytes
			// Flags				   - 4 bytes
			// ---------------------------------
			// Shader Stage			   - 1 byte
			// Shader Stage flags	   - 1 byte
			// Padding				   - 2 bytes
			// Shader Model			   - 4 bytes
			// 			   	
			// Entry Point Length	   - 2 bytes
			// Entry point[]		   - . bytes
			// 
			// SourceLanguage		   - 1 byte
			// Padding				   - 3 bytes
			// 
			// Thread Group SizeX	   - 2 bytes
			// Thread Group SizeY	   - 2 bytes
			// Thread Group SizeZ	   - 2 bytes
			// Padding				   - 2 bytes
			// ---------------------------------
			

			// Write shader info box
			// ----------------------------------------------------------------------  			        
			{
				// Magic number
				stream.Write_char('S');
				stream.Write_char('H');
				stream.Write_char('D');
				stream.Write_char('R');


				// Get the (version)ID of the current scene data strucuture 
				stream.Write_uint32(Version::One().GetVersionID());
				stream.Write_uint64(0); // Skip  size for now
				stream.Write_uint32(0); // Skip flags for now

				// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
				
				stream.Write_uint8((uint8)m_ShaderType);
				stream.Write_uint8(0);
				stream.Write_uint16(0);
				stream.Write_uint32(0);


				stream.Write_uint16((uint16)m_EntryPoint.length());
				stream.Write_string(m_EntryPoint);


				stream.Write_uint8(0);
				stream.Write_uint8(0);
				stream.Write_uint8(0);
				stream.Write_uint8(0);

				stream.Write_uint16(0);
				stream.Write_uint16(0);
				stream.Write_uint16(0);
				stream.Write_uint16(0);
			}


			// SSRC BOX (Shader source box)
			// SSRC BOX VERSION(1, 0, 0, 0)
			// MAGIC ID: 'SSRC'
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// box Format Version      - 4 bytes
			// Box Size				   - 8 bytes
			// Flags				   - 4 bytes
			// ---------------------------------
			// Path Length			   - 2 bytes
			// Path[]				   - . bytes
			// 
			// Content Hash				- 8 bytes
			// Time Stamp				- 8 bytes
			// 
			// Hot reload				- 1 byte
			// Reserved Flags			- 3 bytes
			// 
			// Source Length			- 4 bytes
			// Source					- . bytes
			// ---------------------------------

			std::string source;
			// Write shader source box
			// ----------------------------------------------------------------------  		
			{
				// Magic number
				stream.Write_char('S');
				stream.Write_char('S');
				stream.Write_char('R');
				stream.Write_char('C');


				// Get the (version)ID of the current scene data strucuture 
				stream.Write_uint32(Version::One().GetVersionID());
				stream.Write_uint64(0); // Skip  size for now
				stream.Write_uint32(0); // Skip flags for now

				// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

				stream.Write_uint16((uint16)m_ShaderFilePath.GetPath().length());
				stream.Write_string(m_ShaderFilePath.GetPath());

				stream.Write_uint64(0);
				stream.Write_uint64(0);

				stream.Write_bool(false);
				stream.Write_uint8(0);
				stream.Write_uint8(0);
				stream.Write_uint8(0);

				stream.Write_uint32(0);
				uint64 srcSizePosition = stream.GetPosition();

				std::ifstream file(m_ShaderFilePath.GetPath());

				std::stringstream buffer;
				buffer << file.rdbuf();

				source = buffer.str();

				stream.Write_string(source);
				stream.Write_uint64(stream.GetPosition() - srcSizePosition, srcSizePosition - 8);
			}


			// VARI BOX (Variation box)
			// VARI BOX VERSION(1, 0, 0, 0)
			// MAGIC ID: 'VARI'
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// box Format Version      - 4 bytes
			// Box Size				   - 8 bytes
			// Flags				   - 4 bytes
			// ---------------------------------
			// Variation Count		   - 1 byte
			// --------------------------------- For all variations
			// Variation ID			   - 4 bytes
			// Variation Size		   - 8 bytes
			// Variation Source		   - . bytes
			// ---------------------------------


			// Write shader source box
			// ----------------------------------------------------------------------  		
			{
				// Magic number
				stream.Write_char('S');
				stream.Write_char('S');
				stream.Write_char('R');
				stream.Write_char('C');


				// Get the (version)ID of the current scene data strucuture 
				stream.Write_uint32(Version::One().GetVersionID());
				stream.Write_uint64(0); // Skip  size for now
				stream.Write_uint32(0); // Skip flags for now

				// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

				stream.Write_uint8(1); // Skip the variation count for now

				RHI_DXC_ShaderCompiler compiler = RHI_DXC_ShaderCompiler();

				RHI_ShaderCompileDescriptor compileDesc = { };
				compileDesc.EntryPoint = "main";
				compileDesc.Source     = source;
				compileDesc.Type       = m_ShaderType;
				compileDesc.Defines = 
				{
					{ "-D", "D3D12",},
				};

				RHI_ShaderCompileResult result = compiler.Compile(&compileDesc);
				result;

				// Magic number
				stream.Write_char('D');
				stream.Write_char('X');
				stream.Write_char('1');
				stream.Write_char('2');

				stream.Write_uint64(0); // Skip  size for now

				stream.Write_bytes(result.ByteCode.data(), result.ByteCode.size());
			}

			return Result::RESULT_GOOD;
		}

		Result ShaderAsset::Load_RHI_Shader(const FilePath& _filepath, RHI_Shader* _shader)
		{
			// Gather the graphics API
			RHI_GraphicsAPI api = RenderBackend::GetAPI();
			
			ByteStream stream = ByteStream(_filepath, ByteStreamState::BYTE_STREAM_STATE_READ);

			std::string boxHeader = stream.Read_string(4);
			if (boxHeader == "RASH")
			{
				stream.Skip(4);
				uint64 fileSize = stream.Read_uint64();
				stream.Skip(32);

				// end of header

			}

			return Result();
		}
	}
}