#ifndef ASSET_HELPER_H
#define ASSET_HELPER_H

#include "SOIL.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class asset_helper 
{
	
public:
	
	enum _asset_status { UNLOADED, LOADED, FAIL_LOADING, FAIL_UNLOADING };
	
	enum _asset_defs { SPLASH_COMPANY, SPLASH_PRESENTS, SPLASH_GAME, BG_1, BG_2, 
							CHARACTER, BULLET, ENEMY, EXPLOSION, MENU, BOMB, 
							ENERGY, HELP, GAME_OVER }; 
	
private:

	map<_asset_defs,GLuint> _textures;
	map<_asset_defs,string> _filenames;
	
	
	/****************************************************************
	
								public
	
	****************************************************************/
	
public:
	
	static asset_helper& getInstance()
	{
		static asset_helper instance;
		return instance;
	}
	
	
	GLuint get_texture(_asset_defs asset)
	{
		// try to load texture
		_asset_status status = load_texture(asset);
		
		// texture loaded
		if(status==LOADED)
		{
			return _textures[asset];
		}
		
		// return null in any other case
		return 0;
	}
	
	
	_asset_status unload_texture(_asset_defs asset)
	{
		// filename not defined?
		if(_filenames.find(asset)==_filenames.end())
		{
			return FAIL_UNLOADING;
		}
		// texture already unloaded?
		if(_textures.find(asset)==_textures.end())
		{
			return UNLOADED;
		}
		
		// unload texture
		glDeleteTextures(1, &_textures[asset]);
		
		// n has to be 1 if erasing is correct
		int n = _textures.erase(asset);
		
		string fname = _filenames[asset];
		
		cout << "Unloading asset: " << fname.c_str() << endl << flush;
		
		return n==1 ? UNLOADED : FAIL_UNLOADING;
	}
	
	
	/****************************************************************
	
								private

	****************************************************************/
	
private:
	
	asset_helper(asset_helper const& copy);
	
	asset_helper& operator=(asset_helper const& copy);
	
	
	asset_helper() {
		
		// set filenames
		_filenames = map<_asset_defs,string>();
		_filenames.insert( pair<_asset_defs,string>(SPLASH_COMPANY,"../assets/ok52.bmp") );
		_filenames.insert( pair<_asset_defs,string>(SPLASH_PRESENTS,"../assets/presents.bmp") );
		_filenames.insert( pair<_asset_defs,string>(SPLASH_GAME,"../assets/portada.bmp") );
		_filenames.insert( pair<_asset_defs,string>(BG_1,"../assets/coc1.bmp") );
		_filenames.insert( pair<_asset_defs,string>(BG_2,"../assets/coc2.bmp") ); 
		_filenames.insert( pair<_asset_defs,string>(CHARACTER,"../assets/mio.bmp") );
		_filenames.insert( pair<_asset_defs,string>(BULLET,"../assets/disp.bmp") );
		_filenames.insert( pair<_asset_defs,string>(ENEMY,"../assets/malo.bmp") );
		_filenames.insert( pair<_asset_defs,string>(EXPLOSION,"../assets/explos.bmp") );
		_filenames.insert( pair<_asset_defs,string>(MENU,"../assets/menu2.bmp") );
		_filenames.insert( pair<_asset_defs,string>(BOMB,"../assets/gran.bmp") );
		_filenames.insert( pair<_asset_defs,string>(ENERGY,"../assets/energy.bmp") );
		_filenames.insert( pair<_asset_defs,string>(HELP,"../assets/help.bmp") );
		_filenames.insert( pair<_asset_defs,string>(GAME_OVER,"../assets/pilla1.bmp") );
		
		_textures = map<_asset_defs,GLuint>();
	}
	
	
	~asset_helper()
	{
		// delete textures
		map<_asset_defs,GLuint>::iterator it = _textures.begin();
		while(it!=_textures.end())
		{
			_textures.erase(it++);
		}
		
		// delete filenames
		_filenames.clear();
	}
	
	
	_asset_status load_texture(_asset_defs asset)
	{
		// filename not defined?
		if(_filenames.find(asset)==_filenames.end())
		{
			return FAIL_LOADING;
		}
		// texture already loaded?
		if(_textures.find(asset)!=_textures.end())
		{
			return LOADED;
		}
		
		string fname = _filenames[asset];
		
		cout << "Loading asset: " << fname.c_str() << endl << flush;
		
		// load texture
		GLuint tex2d = SOIL_load_OGL_texture
		(
			fname.c_str(),
			SOIL_LOAD_RGBA,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		
		
		// loaded? save it
		if((0!=tex2d))
		{
			_textures.insert( pair<_asset_defs,GLuint>(asset,tex2d) );
			
			return LOADED;
		}
		
		cout << "Error loading asset: " << fname.c_str() << "  Error: " << SOIL_last_result() << endl << flush;
		
		return FAIL_LOADING;
	}
	
};

#endif /* ASSET_HELPER_H */