#include <config.h>
#include <cstdio>
#include "sound.hpp"
#ifdef AZP_AUDIO
extern "C"
{
	PaStream* stream;
	int current_section;
}
OggVorbis_File vf;
AZPAudio::AZPAudio(const char* file)
{
	PaError err;
	vorbis_info* vi;
	PaStreamParameters outputParameters;
	int eof=0;
	char buffer[1024];
	
	ov_fopen(file,&vf);
	vi=ov_info(&vf,-1);
	
	err=Pa_Initialize();
	if(!CheckPortAudioError(err))
		return;
	
	outputParameters.device = Pa_GetDefaultOutputDevice();
	outputParameters.channelCount = vi->channels;
	outputParameters.sampleFormat = paInt16;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	
	err=Pa_OpenStream(&stream,NULL,&outputParameters,vi->rate,256,paClipOff,NULL,NULL );
	if(!CheckPortAudioError(err))
		return;
	
	err=Pa_StartStream(stream);
	if(!CheckPortAudioError(err))
		return;
	
	fflush(stdout);
	AudioThread* audioThread=new AudioThread();
	audioThread->Create();
	audioThread->Run();
	/*while(!eof)
	{
		long ret=ov_read(&vf,buffer,sizeof(buffer),0,2,1,&current_section);
		if(ret==0)
		{
			eof=1;
		}else{
			Pa_WriteStream(stream,(char*)buffer,ret/4);
		}
		
	}*/
}
AZPAudio::~AZPAudio()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
}
bool AZPAudio::CheckPortAudioError(PaError err)
{
	if(err==paNoError)
	{
		return true;
	}else{
		//TODO: Log system
		printf("PortAudio Error: %s\n",Pa_GetErrorText(err));
		return false;
	}
}
AudioThread::AudioThread() : wxThread()
{
	
}
wxThread::ExitCode AudioThread::Entry()
{
	char buffer[1024];
	int eof=0;
	while(!eof)
	{
		long ret=ov_read(&vf,buffer,sizeof(buffer),0,2,1,&current_section);
		if(ret==0)
		{
			eof=1;
		}else{
			Pa_WriteStream(stream,(char*)buffer,ret/4);
		}
		
	}
	return 0;
}
#endif /* AZP_AUDIO */
