// Ad Maiorem Dei Gloriam!

#include <stb_image.h>
#include <string>
#include "core/log.hpp"
#include "core/texture.hpp"

bool Texture::load(const std::string& filePath, GLenum wrapModeX, GLenum wrapModeY, GLenum minFilter, GLenum magFilter)
{

	stbi_set_flip_vertically_on_load(true);
	int width, height, numColorChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numColorChannels, 0);

	if (!data)
	{
		Log::log_error("Could not find file " + filePath + ".");
		mErrorString = "Could not find file" + filePath;
		mActive = false;
		return false;
	}


	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	Log::log_debug("Successifully loaded texture of Id " + std::to_string(mId) + "(" + filePath + ").");
	
	GLenum internalFormat = (numColorChannels == 4) ? GL_RGBA : GL_RGB;
	GLenum dataFormat = (numColorChannels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeY);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	unbind();

	mActive = true;
	return true;
}

void Texture::unload() const
{
	if (mActive)
	{
		glDeleteTextures(1, &mId);
		Log::log_debug("Successifully unloaded texture of Id " + std::to_string(mId));
	}
}

Texture::~Texture()
{
	unload();
}

void Texture::setWrap(GLenum wrapX, GLenum wrapY) const
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapY);
	unbind();
}

void Texture::setFilters(GLenum minFilter, GLenum magFilter) const
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	unbind();
}

void Texture::activate(int texUnit) const
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	bind();
}