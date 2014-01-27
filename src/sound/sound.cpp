#include <config.h>
#include "sound.hpp"
#ifdef AZP_AUDIO
AZPAudio::AZPAudio(const char* file)
{
	PaError err;
	int current_section;
	OggVorbis_File vf;
	vorbis_info* vi;
	PaStreamParameters outputParameters;
	int eof=0;
	char buffer[1024];
	
	ov_fopen(file,&vf);
	vi=ov_info(&vf,-1);
	
	Pa_Initialize();
	
	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	outputParameters.channelCount = vi->channels;
	outputParameters.sampleFormat = paInt16;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	
	Pa_OpenStream(&stream,NULL,&outputParameters,vi->rate,256,paClipOff,NULL,NULL );
	Pa_StartStream(stream);
	
	fflush(stdout);
	
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
}
AZPAudio::~AZPAudio()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
}
AudioThread::AudioThread(const char* filename) : wxThread(wxTHREAD_DETACHED)
{
	file=filename;
}
wxThread::ExitCode AudioThread::Entry()
{
	AZPAudio* audio=new AZPAudio(file);
	return (wxThread::ExitCode)0;
}
#endif /* AZP_AUDIO */
