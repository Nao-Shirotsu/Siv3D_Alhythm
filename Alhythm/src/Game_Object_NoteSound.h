#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"

namespace Game{
namespace Object{

// 
class NoteSound{
public:
	NoteSound();
	~NoteSound();

	void Play( const NoteJudge judge ) const;

private:
	s3d::Sound goodfineSound;
	s3d::Sound justSound;
	s3d::Sound missSound;
};

}
}