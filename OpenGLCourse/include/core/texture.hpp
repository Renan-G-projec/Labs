// Ad Maiorem Dei Gloriam!
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glad/gl.h>

class Texture
{
public:
	Texture() = default;
	Texture(const Texture& other) = delete;
	~Texture();

	bool load(const std::string& filePath, GLenum wrapModeX = GL_REPEAT, GLenum wrapModeY = GL_REPEAT, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);
	void unload() const;

	bool loadedSuccessifully() const { return mActive; }
	const std::string& getErrorString() const { return mErrorString; }

	void setWrap(GLenum nwrapX, GLenum wrapY) const;
	void setFilters(GLenum minFiler, GLenum magFilter) const;

	void activate(int texUnit = 0) const;
	
	void bind() const { glBindTexture(GL_TEXTURE_2D, mId); }
	static void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

private:
	
	std::string mErrorString;
	GLuint mId = 0;
	bool mActive{ true };
};

#endif