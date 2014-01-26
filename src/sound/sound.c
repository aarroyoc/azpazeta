#include <config.h>
#ifdef AZP_AUDIO
#include <portaudio.h>
#include <sndfile.h>

SF_INFO sfinfo;
PaStreamParameters out_param;
PaStream * stream;
PaError err;
SNDFILE * file;
static int
output_cb(const void * input, void * output, unsigned long frames_per_buffer,
        const PaStreamCallbackTimeInfo *time_info,
        PaStreamCallbackFlags flags, void * data)
{
    SNDFILE * filex = data;

    /* this should not actually be done inside of the stream callback
     * but in an own working thread 
     *
     * Note although I haven't tested it for stereo I think you have
     * to multiply frames_per_buffer with the channel count i.e. 2 for
     * stereo */
    sf_read_short(filex, output, frames_per_buffer*sfinfo.channels);
    return paContinue;
}

static void
end_cb(void * data)
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	sf_close(file);
	Pa_Terminate();
}

#define error_check(err) \
    do {\
        if (err) { \
            fprintf(stderr, "line %d ", __LINE__); \
            fprintf(stderr, "error number: %d\n", err); \
            fprintf(stderr, "\n\t%s\n\n", Pa_GetErrorText(err)); \
            return err; \
        } \
    } while (0)

int
AZPSound(char* filename)
{

    /*puts(filename);
    file = sf_open(filename, SFM_READ, &sfinfo);
    printf("%d frames %d samplerate %d channels\n", (int)sfinfo.frames,
            sfinfo.samplerate, sfinfo.channels);*/

    /* init portaudio */
    err = Pa_Initialize();
    error_check(err);

    /* we are using the default device */
    out_param.device = Pa_GetDefaultOutputDevice();
    if (out_param.device == paNoDevice)
    {
        fprintf(stderr, "Haven't found an audio device!\n");
        return -1;
    }

    /* stero or mono */
    out_param.channelCount = sfinfo.channels;
    out_param.sampleFormat = paInt16; //paInt16
    out_param.suggestedLatency = Pa_GetDeviceInfo(out_param.device)->defaultLowOutputLatency;
    out_param.hostApiSpecificStreamInfo = NULL; //NULL

    err = Pa_OpenStream(&stream, NULL, &out_param, sfinfo.samplerate,
            paFramesPerBufferUnspecified, paClipOff,
            output_cb, file);
    error_check(err);

    err = Pa_SetStreamFinishedCallback(stream, &end_cb);
    error_check(err);

    err = Pa_StartStream(stream);
    error_check(err);

    printf("Play for 10 seconds.\n");
    /*Pa_Sleep(10000);

    err = Pa_StopStream(stream);
    error_check(err);

    err = Pa_CloseStream(stream);
    error_check(err);

    sf_close(file);

    Pa_Terminate();*/

    return 0;
}
int AZPSoundStop()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	//sf_close(file);
	Pa_Terminate();
}
#endif /* AZP_AUDIO */
