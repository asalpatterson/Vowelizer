//Kludged together by Asa Patterson from existing ElectroSmith examples.
//
//Two parallel state variable bandpass filters, each with different frequency
//ranges to simulate human vowel sounds. Best results are found by inputting a
//140Hz sawtooth wave.

#include "daisysp.h"
#include "daisy_pod.h"

using namespace daisysp;
using namespace daisy;

static DaisyPod pod;

void Controls();
Svf filt1;
Svf filt2;
Parameter p_formant1, p_formant2;

float formant1, formant2;

static void AudioCallback(float *in, float *out, size_t size)
{
    float sig;
    float band1, band2;
    
    formant1 = p_formant1.Process();
    formant2 = p_formant2.Process();
    
    filt1.SetFreq(formant1);
    filt2.SetFreq(formant2);
    
    for(size_t i = 0; i < size; i += 2)
    {
        sig = in[i] = in[i+1];
        
        filt1.Process(sig);
        filt2.Process(sig);
        
        band1 = filt1.Band();
        band2 = filt2.Band();
        
        // Left and Right out
        out[i] = (band1 + band2) ;
        out[i + 1] = (band1 + band2) ;

    }
}

int main(void)
{
    
    float sample_rate;
    
    // initialize pod hardware and oscillator daisysp module
    pod.Init();
    sample_rate = pod.AudioSampleRate();
    
    //Assign formants to knobs.
    //Formant 1 has range 200Hz - 1000Hz
    //Formant 2 has range 500Hz - 2500Hz
    
    p_formant1.Init(pod.knob1, 200, 1000, Parameter::LOGARITHMIC);
    p_formant2.Init(pod.knob2, 500, 2500, Parameter::LOGARITHMIC);

    // Initialize Filters, and set parameters.
    filt1.Init(sample_rate);
    filt1.SetRes(0.85);
    filt1.SetDrive(0.8);
    
    filt2.Init(sample_rate);
    filt2.SetRes(0.85);
    filt2.SetDrive(0.8);
    

    
    // start callback
    pod.StartAdc();
    pod.StartAudio(AudioCallback);

    while(1) {}
}



//Deals with analog controls 
void Controls()
{
    pod.UpdateAnalogControls();
    pod.DebounceControls();

}
