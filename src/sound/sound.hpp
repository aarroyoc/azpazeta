/*  	Azpazeta - Sandbox strategy game
    	Copyright (C) 2013-2014  Adrián Arroyo Calle
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include <config.h>
#include "wx/thread.h"
#ifndef SOUND_HPP
#define SOUND_HPP
#ifdef AZP_AUDIO
extern "C"
{
	#include <portaudio.h>
	#include <vorbis/vorbisfile.h>
	#include <stdlib.h>
	static int Callback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,  const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
}
class AZPAudio{
	public:
		AZPAudio(const char* filename);
		~AZPAudio();
	private:
		bool CheckPortAudioError(PaError err);
};
class AudioThread : public wxThread{
	public:
		AudioThread();
	private:
		virtual wxThread::ExitCode Entry();
		const char* file;
};
#endif
#endif



