#include "./pch.h"
#include "./graphics/gfx/material/assets/texture_asset.h"


// Core includes
#include "./core/files/byte_stream.h"


// Util includes
#include "./util/hash_util.h"


namespace Raydiance
{
	namespace Graphics
	{
		Result TextureAsset::CreateEmpty(std::shared_ptr<TextureAsset>& _asset)
		{
			_asset = std::make_unique<TextureAsset>();
			_asset->m_UUID = UUID();

			return Result::RESULT_GOOD;
		}


		Result TextureAsset::Load(const FilePath& _filepath, std::shared_ptr<TextureAsset>& _asset)
		{


			return Result::RESULT_GOOD;
		}


		Result TextureAsset::Save()
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
				stream.Write_char('T');
				stream.Write_char('X');


				// Get the (version)ID of the current scene data strucuture 
				stream.Write_uint32(TEXTURE_ASSET_ACTIVE_VERSION.GetVersionID());
				stream.Write_uint64(0); // Skip size for now


				// TODO:: implement the rest of the file header
				// Skip the rest of the header for now.
				stream.Skip(32);
			}

			return Result::RESULT_GOOD;
		}
	}
}