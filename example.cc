#include <nan.h>

#include <stdio.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>


const int maxValue = 10;
int numberOfCalls = 0;

NAN_METHOD(whoAmI) {
  auto message = Nan::New<v8::String>("I'm a Node Hero!").ToLocalChecked();
  info.GetReturnValue().Set(message);
}

NAN_METHOD(getVolume)
{
  HRESULT hr;
  // -------------------------
  CoInitialize(NULL);
  IMMDeviceEnumerator *deviceEnumerator = NULL;
  hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
  IMMDevice *defaultDevice = NULL;

  hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
  deviceEnumerator->Release();
  deviceEnumerator = NULL;

  IAudioEndpointVolume *endpointVolume = NULL;
  hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
  defaultDevice->Release();
  defaultDevice = NULL;

  // -------------------------
  float currentVolume = 0;
  hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
  printf("Current volume as a scalar is: %f\n", currentVolume);
  endpointVolume->Release();
  CoUninitialize();

  info.GetReturnValue().Set(Nan::New<v8::Number>(currentVolume));
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, whoAmI);
  NAN_EXPORT(target, getVolume);
}

NODE_MODULE(node_os_calls, Initialize)
