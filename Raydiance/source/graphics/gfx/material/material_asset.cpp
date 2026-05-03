#include "./pch.h"
#include "./graphics/gfx/material/material_asset.h"


// Core includes
#include "./core/files/byte_stream.h"


// Util includes
#include "./util/hash_util.h"


namespace Raydiance
{
	namespace Graphics
	{
		Result MaterialAsset::CreateEmpty(std::shared_ptr<MaterialAsset>& _asset)
		{
			_asset = std::make_unique<MaterialAsset>();
			_asset->m_UUID = UUID();

			return Result::RESULT_GOOD;
		}


		Result MaterialAsset::Load(const FilePath& _filepath, std::shared_ptr<MaterialAsset>& _asset)
		{
			return Result::RESULT_GOOD;
		}


		Result MaterialAsset::Save()
		{
			// Generate filepath based on UUID - hash
			FilePath filepath = FilePath("./assets/" + to_hex_mix2((uint64)m_UUID) + ".ramt");


			// File header VERSION(1, 0, 0, 0)
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// Material Format Version - 4 bytes
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


			// TODO:: Make ShaderAsset

			// VESH BOX (vertex shader box)
			// MAGIC ID: 'VESH'
			// ----------------------------------------------------------------------
			// Magic Number			   - 4 bytes
			// box Format Version      - 4 bytes
			// File Size			   - 8 bytes
			// 
			// Shader UUID			   - 8 bytes
			

			// Initialize the stream
			// -----------------------------------------------------------------------
			ByteStream  stream = ByteStream(filepath, ByteStreamState::BYTE_STREAM_STATE_WRITE);
			uint64 streamBegin = stream.GetPosition();


			// Magic number
			stream.Write_char('R');
			stream.Write_char('A');
			stream.Write_char('M');
			stream.Write_char('T');

			// Get the (version)ID of the current scene data strucuture 
			stream.Write_uint32(MATERIAL_ASSET_ACTIVE_VERSION.GetVersionID());

			return Result::RESULT_GOOD;
		}
	}
}